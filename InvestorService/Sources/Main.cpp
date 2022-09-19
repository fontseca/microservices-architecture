#include <iostream>

#include "Includes/Controllers/InvestorController.hpp"

int main()
{
  const std::string listener_uri{"http://localhost:5000/investor"};
  Server::Controllers::InvestorController investor_controller;

  investor_controller.SetControllerAt(listener_uri);
  investor_controller.OpenController().wait();

  for (;;)
    ;

  investor_controller.ShutdownController().wait();
  return 0;
}