//
//  Created by Jeremy Fonseca on September, 2022
//

#ifndef A6F9711E_76CF_4062_95E7_D52DC53B46AD
#define A6F9711E_76CF_4062_95E7_D52DC53B46AD

#include <cpprest/http_listener.h>

#include "Includes/Core/BaseController.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;

namespace Server::Controllers
{
  struct AuthenticationController : public Server::Core::BaseController
  {
    void HandleGet(http_request request) override;
    void HandlePost(http_request request) override;
    void HandleDelete(http_request request) override;
    void HandlePut(http_request request) override;

  private:
    void InitializeHandlers() override
    {
      this->m_Listener.support(methods::GET, std::bind(&Server::Core::BaseController::HandleGet, this, std::placeholders::_1));
      this->m_Listener.support(methods::POST, std::bind(&Server::Core::BaseController::HandlePost, this, std::placeholders::_1));
      this->m_Listener.support(methods::DEL, std::bind(&Server::Core::BaseController::HandleDelete, this, std::placeholders::_1));
      this->m_Listener.support(methods::PUT, std::bind(&Server::Core::BaseController::HandlePut, this, std::placeholders::_1));
      return;
    }
  };
}

#endif /* A6F9711E_76CF_4062_95E7_D52DC53B46AD */
