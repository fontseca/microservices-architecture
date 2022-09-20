//
//  Created by Jeremy Fonseca on September, 2022
//

#ifndef D52C24A4_12DE_4876_B7F1_20BE5DC8F3A5
#define D52C24A4_12DE_4876_B7F1_20BE5DC8F3A5

#include <cpprest/http_listener.h>
#include <jwt/jwt.hpp>

using namespace web::http;
using namespace web::http::experimental::listener;

namespace Server::Helpers
{
  bool HasAuthorization(const http_request &request)
  {
    using namespace jwt::params;

    if (!request.headers().has(header_names::authorization))
    {
      request.reply(status_codes::Unauthorized, "Wait! You must log in to proceed.");
      return false;
    }

    auto headers = request.headers();
    auto full_token = headers[header_names::authorization];

    // Split token
    std::stringstream ss(full_token);
    std::string word;
    std::vector<std::string> chunks{};

    while (!ss.eof())
    {
      std::getline(ss, word, ' ');
      chunks.push_back(word);
    }

    try
    {
      auto dec_obj = jwt::decode(chunks[1], algorithms({"HS256"}), secret("my secret is..."), verify(true));
    }
    catch (const jwt::TokenExpiredError &e)
    {
      request.reply(status_codes::Unauthorized, "Token expired. Log in again.");
    }
    catch (const jwt::SignatureFormatError &e)
    {
      request.reply(status_codes::InternalError, e.what());
    }
    catch (const jwt::DecodeError &e)
    {
      request.reply(status_codes::InternalError, e.what());
    }
    catch (const jwt::VerificationError &e)
    {
      request.reply(status_codes::InternalError, e.what());
    }
    catch (...)
    {
      std::cerr << "Caught unknown exception\n";
    }

    return true;
  }
}

#endif /* D52C24A4_12DE_4876_B7F1_20BE5DC8F3A5 */
