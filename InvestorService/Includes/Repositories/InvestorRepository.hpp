//
//  Created by Jeremy Fonseca on September, 2022
//

#ifndef BE6BA356_9B9F_4BCC_BD50_708C60B8D611
#define BE6BA356_9B9F_4BCC_BD50_708C60B8D611

#include <cpprest/json.h>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

namespace Server::Repositories
{
  struct InvestorRepository final
  {
    InvestorRepository()
    {
      this->m_Connection = mongocxx::client{mongocxx::uri{"mongodb+srv://fontseca:L6wmddLHjhk3SNF9@personal.l3tcooi.mongodb.net/?retryWrites=true&w=majority"}};
      this->m_Database = this->m_Connection["EcosystemOfServices"];
    }

    web::json::value FetchAllInvestors() noexcept
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

  private:
    mongocxx::client m_Connection;
    mongocxx::database m_Database;
  };
}

#endif /* BE6BA356_9B9F_4BCC_BD50_708C60B8D611 */
