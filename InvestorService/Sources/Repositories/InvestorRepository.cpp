//
//  Created by Jeremy Fonseca on September, 2022
//

#include "Includes/Repositories/InvestorRepository.hpp"
#include "Includes/Models/InvestorModel.hpp"

using namespace Server::Models;

Server::Repositories::InvestorRepository::InvestorRepository()
{
  this->m_Connection = mongocxx::client{mongocxx::uri{"mongodb+srv://fontseca:L6wmddLHjhk3SNF9@personal.l3tcooi.mongodb.net/?retryWrites=true&w=majority"}};
  this->m_Database = this->m_Connection["EcosystemOfServices"];
}

web::json::value Server::Repositories::InvestorRepository::FetchAllInvestors() const noexcept
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

bool Server::Repositories::InvestorRepository::CreateInvestor(const InvestorModel &investor) const noexcept
{
  auto builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value investor_doc =
      builder << "name" << investor.Name
              << "email" << investor.Email
              << "phone" << investor.Phone << bsoncxx::builder::stream::finalize;
  this->m_Database.collection("investor").insert_one(investor_doc.view());
  return true;
}
