//
//  Created by Jeremy Fonseca on September, 2022
//

#ifndef BE6BA356_9B9F_4BCC_BD50_708C60B8D611
#define BE6BA356_9B9F_4BCC_BD50_708C60B8D611

#include <cpprest/json.h>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

#include "Includes/Models/InvestorModel.hpp"

namespace Server::Repositories
{
  struct InvestorRepository final
  {
    InvestorRepository();
    web::json::value FetchAllInvestors() const noexcept;
    bool CreateInvestor(const Server::Models::InvestorModel &) const noexcept;
    bool ModifyInvestor(const std::string, const Server::Models::InvestorModel &) const noexcept;

  private:
    mongocxx::client m_Connection;
    mongocxx::database m_Database;
  };
}

#endif /* BE6BA356_9B9F_4BCC_BD50_708C60B8D611 */
