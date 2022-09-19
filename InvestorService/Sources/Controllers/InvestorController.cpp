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
      this->CreateInvestor(request);
      return;
    }
  }
  request.reply(status_codes::NotFound);
  return;
}

void InvestorController::HandlePut(http_request request)
{
  Server::Core::BaseController::HandlePut(request);
  const auto path = this->RequestPath(request);
  if (!path.empty())
  {
    if (path[0] == "modify" && path.size() == 2)
    {
      if (!path[1].empty())
      {
        try
        {
          const int32_t id = atoi(path[1].c_str());
          this->ModifyInvestor(request, id);
          return;
        }
        catch (const std::exception &e)
        {
          std::cerr << e.what() << '\n';
        }
        return;
      }
    }
  }
  request.reply(status_codes::NotFound);
}

void InvestorController::HandleDelete(http_request request)
{
}

// METHODS

void InvestorController::CreateInvestor(const http_request &request)
{
  const auto then_lambda = [request](pplx::task<web::json::value> task)
  {
    try
    {
      auto const json_value = task.get();
      request.reply(status_codes::Created);
      return;
    }
    catch (std::exception &ex)
    {
      std::cerr << ex.what();
    }
  };

  request
      .extract_json()
      .then(then_lambda);
  return;
}

void InvestorController::ModifyInvestor(const http_request &request, const int32_t id)
{
  request.reply(status_codes::Created, "Modified: " + std::to_string(id));
  return;
}