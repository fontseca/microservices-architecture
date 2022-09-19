//
//  Created by Jeremy Fonseca on September, 2022
//

#ifndef B6DFB710_ADAA_4F66_B2FD_2DE0CC1BE1B6
#define B6DFB710_ADAA_4F66_B2FD_2DE0CC1BE1B6

#include <cpprest/json.h>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

#include "Includes/Models/UserModel.hpp"

namespace Server::Repositories
{
  struct AuthenticationRepository final
  {
    AuthenticationRepository();

    bool SignupUser(const Server::Models::UserModel &) const noexcept;
    bool LoginUser(const Server::Models::UserModel &) const noexcept;

  private:
    mongocxx::client m_Connection;
    mongocxx::database m_Database;
  };
}

#endif /* B6DFB710_ADAA_4F66_B2FD_2DE0CC1BE1B6 */
