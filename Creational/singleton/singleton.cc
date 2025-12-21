// Created: 2025-11-03
// Filename: singleton.cc
// Description: Singleton design pattern demonstration
// Copyright 2025

#include "singleton.hpp"

#include <iostream>

int main() {
  // Get the singleton instance
  Logger& logger1 = Logger::instance();
  logger1.Log("First message");
  logger1.Log("Second message");

  // Get the same instance again
  Logger& logger2 = Logger::instance();
  logger2.Log("Third message");

  std::cout << "\nTotal logs: " << logger2.log_count() << std::endl;

  // Verify it's the same instance
  std::cout << "logger1 address: " << &logger1 << std::endl;
  std::cout << "logger2 address: " << &logger2 << std::endl;

  return 0;
}
