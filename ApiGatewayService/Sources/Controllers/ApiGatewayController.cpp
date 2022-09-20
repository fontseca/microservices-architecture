//
//  Created by Jeremy Fonseca on September, 2022
//

#include <sstream>

#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>

#include <bsoncxx/json.hpp>

#include <jwt/jwt.hpp>

#include "Includes/Controllers/ApiGatewayController.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;
using namespace Server::Controllers;

void ApiGatewayController::HandleGet(http_request request)
{
  Server::Core::BaseController::HandleGet(request);
}

void ApiGatewayController::HandlePost(http_request request)
{
  Server::Core::BaseController::HandlePost(request);
  const auto path = this->RequestPath(request);

  if (path.empty())
    request.reply(status_codes::NotFound);

  if (path[0] == "auth" && path.size() == 2)
  {
    if (path[1] == "signup" || path[1] == "login")
    {

      const auto request_to_auth_service = [=](pplx::task<web::json::value> task)
      {
        client::http_client auth_client{U("http://localhost:5001/" + path[1])};
        web::json::value user_json = task.get();
        return auth_client.request(web::http::methods::POST, U(""), user_json.serialize(), U("application/json"));
      };

      const auto get_auth_service_response = [=](pplx::task<http_response> task)
      {
        auto response = task.get();
        return response.extract_json();
      };

      const auto reply_auth_service_response = [=](pplx::task<web::json::value> task)
      {
        auto res = task.get();
        return request.reply(status_codes::OK, res);
      };

      request
          .extract_json()
          .then(request_to_auth_service)
          .then(get_auth_service_response)
          .then(reply_auth_service_response);
      return;
    }
  }
  request.reply(status_codes::NotFound);
  return;
}

void ApiGatewayController::HandlePut(http_request request)
{
  Server::Core::BaseController::HandlePut(request);
}

void ApiGatewayController::HandleDelete(http_request request)
{
  Server::Core::BaseController::HandleDelete(request);
}
