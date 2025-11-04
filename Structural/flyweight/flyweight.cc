// Created: 2025-11-03
// Filename: flyweight.cc
// Description: Flyweight design pattern demonstration
// Copyright 2025

#include "flyweight.hpp"

int main() {
  std::cout << "=== Flyweight Pattern: Font Sharing ===" << std::endl;

  CharacterFontFactory factory;

  auto arial_12 = factory.get_font("Arial", 12);
  auto arial_12_2 = factory.get_font("Arial", 12);  // Reused
  auto times_14 = factory.get_font("Times", 14);
  auto arial_14 = factory.get_font("Arial", 14);

  std::cout << "\nDisplaying characters:" << std::endl;
  arial_12->display('H', 10, 10);
  arial_12->display('e', 20, 10);
  times_14->display('l', 30, 10);
  arial_14->display('l', 40, 10);
  arial_12->display('o', 50, 10);

  std::cout << "\nTotal unique fonts cached: " << factory.get_font_count()
            << std::endl;

  return 0;
}
