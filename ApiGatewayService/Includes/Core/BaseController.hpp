//
//  Created by Jeremy Fonseca on September, 2022
//

#ifndef CA51EB2F_D7C5_42CC_8303_F930379D21BD
#define CA51EB2F_D7C5_42CC_8303_F930379D21BD

#include <cpprest/http_client.h>

using namespace web::http::experimental::listener;

namespace Server::Core
{
  struct BaseController
  {

    void SetControllerAt(const web::uri base_uri) noexcept;
    pplx::task<void> OpenController();
    pplx::task<void> ShutdownController();
    web::uri ControllerRoute();
    std::string ControllerFullRoute();

    virtual void HandleGet(web::http::http_request request) = 0;
    virtual void HandlePost(web::http::http_request request) = 0;
    virtual void HandleDelete(web::http::http_request request) = 0;
    virtual void HandlePut(web::http::http_request request) = 0;
    virtual void InitializeHandlers() = 0;

    std::vector<utility::string_t> RequestPath(const web::http::http_request &request);

  protected:
    http_listener m_Listener;
  };

}

#endif /* CA51EB2F_D7C5_42CC_8303_F930379D21BD */
