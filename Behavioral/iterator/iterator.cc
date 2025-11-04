// Created: 2025-11-03
// Filename: iterator.cc
// Description: Iterator design pattern demonstration
// Copyright 2025

#include "iterator.hpp"

#include <iostream>
#include <string>

int main() {
  VectorCollection<std::string> collection;
  collection.add_item("First");
  collection.add_item("Second");
  collection.add_item("Third");
  collection.add_item("Fourth");

  auto iterator = collection.create_iterator();

  std::cout << "Iterating through collection:" << std::endl;
  while (iterator->has_next()) {
    std::cout << "  - " << iterator->next() << std::endl;
  }

  // Demonstrate with numbers
  VectorCollection<int> numbers;
  numbers.add_item(10);
  numbers.add_item(20);
  numbers.add_item(30);

  auto num_iterator = numbers.create_iterator();

  std::cout << "\nIterating through numbers:" << std::endl;
  while (num_iterator->has_next()) {
    std::cout << "  - " << num_iterator->next() << std::endl;
  }

  return 0;
}
