//
//  Created by Jeremy Fonseca on September, 2022
//

#include "Includes/Repositories/InvestorRepository.hpp"
#include "Includes/Models/InvestorModel.hpp"

using namespace Server::Repositories;
using namespace Server::Models;
using namespace bsoncxx::builder::basic;

InvestorRepository::InvestorRepository()
{
  this->m_Connection = mongocxx::client{mongocxx::uri{"mongodb+srv://fontseca:L6wmddLHjhk3SNF9@personal.l3tcooi.mongodb.net/?retryWrites=true&w=majority"}};
  this->m_Database = this->m_Connection["EcosystemOfServices"];
}

web::json::value InvestorRepository::FetchAllInvestors() const noexcept
{
  web::json::value response = web::json::value::array();
  for (uint32_t i = 0; const auto &doc : this->m_Database.collection("investor").find({}))
  {
    web::json::value o = web::json::value::object();
    o = web::json::value::parse(bsoncxx::to_json(doc));
    response[i++] = o;
  }
  return response;
}

bool InvestorRepository::CreateInvestor(const InvestorModel &investor) const noexcept
{
  auto builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value investor_doc =
      builder << "name" << investor.Name
              << "email" << investor.Email
              << "phone" << investor.Phone << bsoncxx::builder::stream::finalize;
  this->m_Database.collection("investor").insert_one(investor_doc.view());
  return true;
}

bool InvestorRepository::ModifyInvestor(const std::string id, const InvestorModel &new_investor) const noexcept
{
  try
  {

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::oid doc_id(id);

    bsoncxx::document::value update_doc =
        builder << "$set" << bsoncxx::builder::stream::open_document
                << "name" << new_investor.Name
                << "phone" << new_investor.Phone
                << "email" << new_investor.Email
                << bsoncxx::builder::stream::close_document
                << bsoncxx::builder::stream::finalize;

    auto maybe = this->m_Database.collection("investor").update_one(make_document(kvp("_id", doc_id)), update_doc.view());

    // Find one:
    // auto maybe_result = this->m_Database.collection("investor").find_one(make_document(kvp("_id", doc_id)));
    // if (maybe_result)
    // {
    //   std::cout << bsoncxx::to_json(maybe_result.value().view());
    // }

    if (maybe)
      return maybe->modified_count() == 1;
    return false;
  }
  catch (const std::exception &ex)
  {
    std::cerr << ex.what() << std::endl;
  }
  return false;
}

bool InvestorRepository::DeleteInvestor(const std::string id) const noexcept
{
  try
  {
    bsoncxx::oid doc_id(id);
    auto maybe = this->m_Database.collection("investor").delete_one(make_document(kvp("_id", doc_id)));
    if (maybe)
      return maybe->deleted_count() == 1;
    return false;
  }
  catch (const std::exception &ex)
  {
    std::cerr << ex.what() << std::endl;
  }
  return false;
}