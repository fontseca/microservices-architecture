//
//  Created by Jeremy Fonseca on September, 2022
//

#include <sstream>

#include <cpprest/http_listener.h>
#include <bsoncxx/json.hpp>
#include <jwt/jwt.hpp>

#include "Includes/Controllers/AuthenticationController.hpp"
#include "Includes/Models/UserModel.hpp"
#include "Includes/Repositories/AuthenticationRepository.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;
using namespace Server::Controllers;

void AuthenticationController::HandleGet(http_request request)
{
  Server::Core::BaseController::HandleGet(request);
}

void AuthenticationController::HandlePost(http_request request)
{
  Server::Core::BaseController::HandlePost(request);
  const auto path = this->RequestPath(request);

  if (path.empty() || path.size() != 1)
    request.reply(status_codes::NotFound);

  // Sign up.
  if (path[0] == "signup")
  {
    const auto sign_up_lambda = [=](pplx::task<web::json::value> task)
    {
      try
      {
        const web::json::value json_value = task.get();
        Server::Models::UserModel user{};
        const Server::Repositories::AuthenticationRepository auth_repository{};

        user.Email = json_value.as_object().at(U("email")).as_string();
        user.Password = json_value.as_object().at(U("password")).as_string();

        if (auth_repository.SignupUser(user))
          request.reply(status_codes::OK, web::json::value::string("Singed up"));
        else
          request.reply(status_codes::InternalError, web::json::value::string("Something went wrong. Try using a different URL or ID."));
      }
      catch (const std::exception &ex)
      {
        std::cerr << ex.what();
      }
    };

    request
        .extract_json()
        .then(sign_up_lambda);
    return;
  }

  // Log in.
  if (path[0] == "login")
  {

    const auto login_lambda = [=](pplx::task<web::json::value> task)
    {
      try
      {
        const web::json::value json_value = task.get();
        Server::Models::UserModel user{};
        const Server::Repositories::AuthenticationRepository auth_repository{};

        user.Email = json_value.as_object().at(U("email")).as_string();
        user.Password = json_value.as_object().at(U("password")).as_string();

        if (auth_repository.LoginUser(user))
        {
          using namespace jwt::params;
          auto response = web::json::value::object();
          jwt::jwt_object obj{algorithm("HS256"), secret("my secret is..."), payload({{"email", user.Email}})};
          obj.add_claim("iss", "arun.muralidharan")
              .add_claim("exp", std::chrono::system_clock::now() + std::chrono::seconds{30});
          response[U("Authentication")] = web::json::value::string("Bearer " + obj.signature());
          request.reply(status_codes::OK, response);
        }
        else
          request.reply(status_codes::InternalError, web::json::value::string("Something went wrong. Try using a different URL or ID."));
      }
      catch (const std::exception &ex)
      {
        std::cerr << ex.what() << std::endl;
        request.reply(status_codes::BadRequest, web::json::value::string(ex.what()));
      }
    };

    request
        .extract_json()
        .then(login_lambda);
  }

  return;
}

void AuthenticationController::HandlePut(http_request request)
{
  Server::Core::BaseController::HandlePut(request);
}

void AuthenticationController::HandleDelete(http_request request)
{
  Server::Core::BaseController::HandleDelete(request);
}
