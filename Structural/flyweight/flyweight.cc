// Created: 2025-11-03
// Filename: flyweight.cc
// Description: Flyweight design pattern demonstration
// Copyright 2025

#include "flyweight.hpp"  // [NOLINT]

#include <iostream>

int main() {
  std::cout << "=== Flyweight Pattern: Font Sharing ===" << std::endl;

  CharacterFontFactory factory;

  auto arial_12 = factory.GetFont("Arial", 12);
  auto arial_12_2 = factory.GetFont("Arial", 12);  // Reused
  auto times_14 = factory.GetFont("Times", 14);
  auto arial_14 = factory.GetFont("Arial", 14);

  std::cout << "\nDisplaying characters:" << std::endl;
  arial_12->Display('H', 10, 10);
  arial_12->Display('e', 20, 10);
  times_14->Display('l', 30, 10);
  arial_14->Display('l', 40, 10);
  arial_12->Display('o', 50, 10);

  std::cout << "\nTotal unique fonts cached: " << factory.GetFontCount()
            << std::endl;

  return 0;
}
