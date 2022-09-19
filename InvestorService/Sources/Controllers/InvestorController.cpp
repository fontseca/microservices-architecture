//
//  Created by Jeremy Fonseca on September, 2022
//

#include <sstream>

#include <cpprest/http_listener.h>
#include <bsoncxx/json.hpp>

#include "Includes/Controllers/InvestorController.hpp"
#include "Includes/Repositories/InvestorRepository.hpp"
#include "Includes/Models/InvestorModel.hpp"

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

  const auto then_lambda = [request](pplx::task<web::json::value> task)
  {
    try
    {
      const web::json::value json_value = task.get();
      Server::Models::InvestorModel investor;
      InvestorRepository investor_repository{};

      investor.Name = json_value.as_object().at(U("name")).as_string();
      investor.Email = json_value.as_object().at(U("email")).as_string();
      investor.Phone = json_value.as_object().at(U("phone")).as_string();

      if (investor_repository.CreateInvestor(investor))
        request.reply(status_codes::Created, "Investor created.");
      else
        request.reply(status_codes::InternalError);
    }
    catch (std::exception &ex)
    {
      std::cerr << ex.what() << std::endl;
      request.reply(status_codes::BadRequest, ex.what());
    }
  };

  request
      .extract_json()
      .then(then_lambda);

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