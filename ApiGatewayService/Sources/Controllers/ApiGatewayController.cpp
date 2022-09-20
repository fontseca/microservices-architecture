//
//  Created by Jeremy Fonseca on September, 2022
//

#include <sstream>

#include <cpprest/http_listener.h>
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
}

void ApiGatewayController::HandlePut(http_request request)
{
  Server::Core::BaseController::HandlePut(request);
}

void ApiGatewayController::HandleDelete(http_request request)
{
  Server::Core::BaseController::HandleDelete(request);
}
