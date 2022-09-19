//
//  Created by Jeremy Fonseca on September, 2022
//

#include "Includes/Repositories/InvestorRepository.hpp"

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