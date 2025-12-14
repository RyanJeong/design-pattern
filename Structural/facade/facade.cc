// Created: 2025-11-03
// Filename: facade.cc
// Description: Facade design pattern demonstration
// Copyright 2025

#include "facade.hpp"  // [NOLINT]

#include <iostream>

int main() {
  std::cout << "=== Computer Facade ===" << std::endl;

  ComputerFacade computer;
  computer.Start();

  std::cout << std::endl;

  computer.Shutdown();

  return 0;
}
