//
//  Created by Jeremy Fonseca on September, 2022
//

#include <iostream>
#include "Includes/Controllers/InvestorController.hpp"

int main()
{
  const std::string listener_uri{"http://localhost:5000/investor"};
  Server::Controllers::InvestorController investor_controller;

  investor_controller.SetControllerAt(listener_uri);
  investor_controller.OpenController().wait();

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

  investor_controller.ShutdownController().wait();
  std::clog
      << "Bye."
      << std::endl;
  return EXIT_SUCCESS;
}