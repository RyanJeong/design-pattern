// Created: 2025-11-03
// Filename: iterator.cc
// Description: Iterator design pattern demonstration
// Copyright 2025

#include "iterator.hpp"  // [NOLINT]

#include <iostream>
#include <string>

int main() {
  VectorCollection<std::string> collection;
  collection.AddItem("First");
  collection.AddItem("Second");
  collection.AddItem("Third");
  collection.AddItem("Fourth");

  auto iterator = collection.CreateIterator();

  std::cout << "Iterating through collection:" << std::endl;
  while (iterator->HasNext()) {
    auto state = iterator->Next();
    std::cout << "  - " << state.current_value << std::endl;
  }

  // Demonstrate with numbers
  VectorCollection<int> numbers;
  numbers.AddItem(10);
  numbers.AddItem(20);
  numbers.AddItem(30);

  auto num_iterator = numbers.CreateIterator();

  std::cout << "\nIterating through numbers:" << std::endl;
  while (num_iterator->HasNext()) {
    auto state = num_iterator->Next();
    std::cout << "  - " << state.current_value << std::endl;
  }

  return 0;
}
