#include <cpprest/http_listener.h>

#include "Includes/Core/BaseController.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;
using namespace Server::Core;

void BaseController::SetControllerAt(const web::uri base_uri) noexcept
{
  this->m_Listener = http_listener{base_uri};
  std::clog << "Service is listening at `" << this->ControllerFullRoute() << "`" << std::endl;
  return;
}

pplx::task<void> BaseController::OpenController()
{
  this->InitializeHandlers();
  return this->m_Listener.open();
}

pplx::task<void> BaseController::ShutdownController()
{
  return this->m_Listener.close();
}

web::uri BaseController::ControllerRoute()
{
  return this->m_Listener.uri();
}

std::string BaseController::ControllerFullRoute()
{
  std::stringstream ss;
  ss << this->ControllerRoute().scheme()
     << "://"
     << this->ControllerRoute().host()
     << ":"
     << this->ControllerRoute().port();
  return ss.str();
}

void BaseController::HandleGet(web::http::http_request request)
{
  std::clog
      << "GET `"
      << this->ControllerFullRoute()
      << request.request_uri().to_string()
      << "`"
      << std::endl;
  return;
}

void BaseController::HandlePost(web::http::http_request request)
{
  std::clog
      << "POST `"
      << this->ControllerFullRoute()
      << request.request_uri().to_string()
      << "`"
      << std::endl;
}

void BaseController::HandleDelete(web::http::http_request request) {}

void BaseController::InitializeHandlers() {}

std::vector<utility::string_t> BaseController::RequestPath(const web::http::http_request &request)
{
  auto relative_path = web::uri::decode(request.relative_uri().path());
  return web::uri::split_path(relative_path);
}
