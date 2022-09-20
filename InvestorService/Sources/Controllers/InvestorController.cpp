//
//  Created by Jeremy Fonseca on September, 2022
//

#include <sstream>

#include <cpprest/http_listener.h>
#include <bsoncxx/json.hpp>

#include "Includes/Controllers/InvestorController.hpp"
#include "Includes/Repositories/InvestorRepository.hpp"
#include "Includes/Models/InvestorModel.hpp"
#include "Includes/Helpers/Authorization.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;
using namespace Server::Controllers;
using namespace Server::Repositories;

void InvestorController::HandleGet(http_request request)
{
  if (!Server::Helpers::HasAuthorization(request))
    return;

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
  if (!Server::Helpers::HasAuthorization(request))
    return;
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
        request.reply(status_codes::Created, web::json::value::string("Investor created."));
      else
        request.reply(status_codes::InternalError);
    }
    catch (std::exception &ex)
    {
      std::cerr << ex.what() << std::endl;
      request.reply(status_codes::BadRequest, web::json::value::string(ex.what()));
    }
  };

  request
      .extract_json()
      .then(then_lambda);

  return;
}

void InvestorController::HandlePut(http_request request)
{
  if (!Server::Helpers::HasAuthorization(request))
    return;
  Server::Core::BaseController::HandlePut(request);
  const auto path = this->RequestPath(request);

  if (path.empty() || path.size() > 1)
  {
    request.reply(status_codes::NotFound);
    return;
  }

  const auto then_lambda = [=](pplx::task<web::json::value> task)
  {
    try
    {
      const web::json::value json_value = task.get();
      Server::Models::InvestorModel investor;
      InvestorRepository investor_repository{};

      investor.Name = json_value.as_object().at(U("name")).as_string();
      investor.Email = json_value.as_object().at(U("email")).as_string();
      investor.Phone = json_value.as_object().at(U("phone")).as_string();

      if (investor_repository.ModifyInvestor(path[0], investor))
        request.reply(status_codes::NoContent, web::json::value::string("Investor updated."));
      else
        request.reply(status_codes::InternalError, web::json::value::string("Something went wrong. Try using a different URL or ID."));
    }
    catch (std::exception &ex)
    {
      std::cerr << ex.what() << std::endl;
      request.reply(status_codes::BadRequest, web::json::value::string(ex.what()));
    }
  };

  request
      .extract_json()
      .then(then_lambda);

  return;
}

void InvestorController::HandleDelete(http_request request)
{
  if (!Server::Helpers::HasAuthorization(request))
    return;
  Server::Core::BaseController::HandleDelete(request);
  const auto path = this->RequestPath(request);
  InvestorRepository investor_repository{};

  if (path.empty() || path.size() > 1)
  {
    request.reply(status_codes::NotFound);
    return;
  }

  if (investor_repository.DeleteInvestor(path[0]))
    request.reply(status_codes::Created, web::json::value::string("Deleted: " + (path[0])));
  else
    request.reply(status_codes::InternalError, web::json::value::string("Something went wrong. Try using a different URL or ID."));
  return;
}
