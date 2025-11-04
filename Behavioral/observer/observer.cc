// Created: 2025-11-03
// Filename: observer.cc
// Description: Observer design pattern demonstration
// Copyright 2025

#include "observer.hpp"

int main() {
  Person person("Alice", 14);

  auto console_observer = std::make_shared<ConsoleObserver>("Console");
  auto logging_observer = std::make_shared<LoggingObserver>();

  person.subscribe(console_observer);
  person.subscribe(logging_observer);

  std::cout << "Setting age to 15..." << std::endl;
  person.set_age(15);

  std::cout << "\nSetting age to 16..." << std::endl;
  person.set_age(16);

  std::cout << "\nLogging observer entries:" << std::endl;
  for (const auto& entry : logging_observer->get_log()) {
    std::cout << "  - " << entry << std::endl;
  }

  return 0;
}
