//
//  Created by Jeremy Fonseca on September, 2022
//

#include <iostream>
#include "Includes/Controllers/ApiGatewayController.hpp"

int main()
{
  const std::string listener_uri{"http://localhost:6000"};
  Server::Controllers::ApiGatewayController api_gateway_controller{};

  api_gateway_controller.SetControllerAt(listener_uri);
  api_gateway_controller.OpenController().wait();

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

  api_gateway_controller.ShutdownController().wait();
  std::clog
      << "Bye."
      << std::endl;
  return EXIT_SUCCESS;
}