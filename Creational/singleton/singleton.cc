// Created: 2025-11-03
// Filename: singleton.cc
// Description: Singleton design pattern demonstration
// Copyright 2025

#include "singleton.hpp"

int main() {
  // Get the singleton instance
  Logger& logger1 = Logger::get_instance();
  logger1.log("First message");
  logger1.log("Second message");

  // Get the same instance again
  Logger& logger2 = Logger::get_instance();
  logger2.log("Third message");

  std::cout << "\nTotal logs: " << logger2.get_log_count() << std::endl;

  // Verify it's the same instance
  std::cout << "logger1 address: " << &logger1 << std::endl;
  std::cout << "logger2 address: " << &logger2 << std::endl;

  return 0;
}
