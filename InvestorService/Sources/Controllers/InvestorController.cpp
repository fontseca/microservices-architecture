//
//  Created by Jeremy Fonseca on September, 2022
//

#include <sstream>

#include <cpprest/http_listener.h>
#include <bsoncxx/json.hpp>

#include "Includes/Controllers/InvestorController.hpp"
#include "Includes/Repositories/InvestorRepository.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;
using namespace Server::Controllers;
using namespace Server::Repositories;

void InvestorController::HandleGet(http_request request)
{
  Server::Core::BaseController::HandleGet(request);
  InvestorRepository investor_repository{};
  const auto path = this->RequestPath(request);
  if (!path.empty())
    if (path[0] == "all" && path.size() == 1)
      request.reply(status_codes::OK, investor_repository.FetchAllInvestors());
  request.reply(status_codes::NotFound);
  return;
}

void InvestorController::HandlePost(http_request request)
{
  Server::Core::BaseController::HandlePost(request);
  const auto path = this->RequestPath(request);

  if (path.size() > 0)
  {
    request.reply(status_codes::NotFound);
    return;
  }

  this->CreateInvestor(request);
  return;
}

void InvestorController::HandlePut(http_request request)
{
  Server::Core::BaseController::HandlePut(request);
  const auto path = this->RequestPath(request);

  if (path.empty() || path.size() > 1)
  {
    request.reply(status_codes::NotFound);
    return;
  }

  const int32_t id = atoi(path[0].c_str());
  this->ModifyInvestor(request, id);

  return;
}

void InvestorController::HandleDelete(http_request request)
{
  Server::Core::BaseController::HandleDelete(request);
  const auto path = this->RequestPath(request);

  if (path.empty() || path.size() > 1)
  {
    request.reply(status_codes::NotFound);
    return;
  }

  const int32_t id = atoi(path[0].c_str());
  this->DeleteInvestor(request, id);

  return;
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

void InvestorController::DeleteInvestor(const http_request &request, const int32_t id)
{
  request.reply(status_codes::Created, "Deleted: " + std::to_string(id));
  return;
}