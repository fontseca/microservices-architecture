#ifndef C95CE902_398A_4378_BF40_B98012CB6E99
#define C95CE902_398A_4378_BF40_B98012CB6E99

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
    virtual void InitializeHandlers() = 0;

    std::vector<utility::string_t> RequestPath(const web::http::http_request &request);

  protected:
    http_listener m_Listener;
  };

}

#endif /* C95CE902_398A_4378_BF40_B98012CB6E99 */
