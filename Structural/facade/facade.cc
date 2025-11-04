// Created: 2025-11-03
// Filename: facade.cc
// Description: Facade design pattern demonstration
// Copyright 2025

#include "facade.hpp"

int main() {
  std::cout << "=== Computer Facade ===" << std::endl;

  ComputerFacade computer;
  computer.start();

  std::cout << std::endl;

  computer.shutdown();

  return 0;
}
