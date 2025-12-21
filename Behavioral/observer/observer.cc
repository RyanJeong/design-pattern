// Created: 2025-11-03
// Filename: observer.cc
// Description: Observer design pattern demonstration
// Copyright 2025

#include "observer.hpp"  // [NOLINT]

#include <iostream>
#include <memory>

int main() {
  Person person("Alice", 14);

  auto console_observer = std::make_shared<ConsoleObserver>("Console");
  auto logging_observer = std::make_shared<LoggingObserver>();

  // Subscribe to person using immutable pattern
  Person subscribed =
      person.Subscribe(console_observer).Subscribe(logging_observer);

  std::cout << "Setting age to 15..." << std::endl;
  Person person_15 = subscribed.WithAge(15);

  std::cout << "\nSetting age to 16..." << std::endl;
  Person person_16 = person_15.WithAge(16);

  std::cout << "\nLogging observer entries:" << std::endl;
  for (const auto& entry : logging_observer->GetLog())
    std::cout << "  - " << entry << std::endl;

  return 0;
}
