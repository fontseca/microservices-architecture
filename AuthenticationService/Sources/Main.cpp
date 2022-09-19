//
//  Created by Jeremy Fonseca on September, 2022
//

#include <iostream>
#include "Includes/Controllers/AuthenticationController.hpp"

int main()
{
  const std::string listener_uri{"http://localhost:5001/auth"};
  Server::Controllers::AuthenticationController auth_controller{};

  auth_controller.SetControllerAt(listener_uri);
  auth_controller.OpenController().wait();

  std::clog
      << "Type q to quit service."
      << std::endl;

  for (;;)
  {
    int8_t q;
    std::cin >> q;
    if (q == 'q')
      break;
  }

  auth_controller.ShutdownController().wait();
  std::clog
      << "Bye."
      << std::endl;
  return EXIT_SUCCESS;
}