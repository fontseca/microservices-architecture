//
//  Created by Jeremy Fonseca on September, 2022
//

#ifndef D2CAA7CE_4ACC_464F_AE77_498361A94320
#define D2CAA7CE_4ACC_464F_AE77_498361A94320

#include <cpprest/http_listener.h>

#include "Includes/Core/BaseController.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;

namespace Server::Controllers
{
  struct InvestorController : public Server::Core::BaseController
  {
    void HandleGet(http_request request) override;
    void HandlePost(http_request request) override;
    void HandleDelete(http_request request) override;
    void HandlePut(http_request request) override;

  private:
    void CreateInvestor(const http_request &request);
    void ModifyInvestor(const http_request &request, const int32_t id);
    void DeleteInvestor(const http_request &request, const int32_t id);

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

#endif /* D2CAA7CE_4ACC_464F_AE77_498361A94320 */
