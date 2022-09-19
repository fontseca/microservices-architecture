//
//  Created by Jeremy Fonseca on September, 2022
//

#include <cpprest/http_listener.h>
#include "Includes/Controllers/InvestorController.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;
using namespace Server::Controllers;

void InvestorController::HandleGet(http_request request)
{
  Server::Core::BaseController::HandleGet(request);
  const auto path = this->RequestPath(request);
  if (!path.empty())
  {
    if (path[0] == "all" && path.size() == 1)
    {
      auto response = web::json::value::object();
      response["version"] = web::json::value::string("0.1.1");
      response["status"] = web::json::value::string("ready!");
      request.reply(status_codes::OK, response);
    }
  }
  request.reply(status_codes::NotFound);
  return;
}

void InvestorController::HandlePost(http_request request)
{
  Server::Core::BaseController::HandlePost(request);
  const auto path = this->RequestPath(request);
  if (!path.empty())
  {
    if (path[0] == "create" && path.size() == 1)
    {
      this->CreateInvestor();
      request.reply(status_codes::Created, "Investor created");
    }
  }
  request.reply(status_codes::NotFound);
  return;
}

void InvestorController::HandleDelete(http_request request)
{
}

void InvestorController::CreateInvestor()
{
  std::cout << "Creating investor...\n";
  return;
}