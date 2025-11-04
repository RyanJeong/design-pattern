// Created: 2025-11-03
// Filename: decorator.cc
// Description: Decorator design pattern demonstration
// Copyright 2025

#include "decorator.hpp"

int main() {
  std::cout << "=== Coffee Ordering ===" << std::endl;

  // Simple coffee
  auto coffee1 = std::make_unique<SimpleCoffee>();
  std::cout << coffee1->get_description() << " - $" << coffee1->get_cost()
            << std::endl;

  // Coffee with milk
  auto coffee2 =
      std::make_unique<MilkDecorator>(std::make_unique<SimpleCoffee>());
  std::cout << coffee2->get_description() << " - $" << coffee2->get_cost()
            << std::endl;

  // Coffee with milk and sugar
  auto coffee3 = std::make_unique<SugarDecorator>(
      std::make_unique<MilkDecorator>(std::make_unique<SimpleCoffee>()));
  std::cout << coffee3->get_description() << " - $" << coffee3->get_cost()
            << std::endl;

  // Coffee with milk, sugar, and chocolate
  auto coffee4 =
      std::make_unique<ChocolateDecorator>(std::make_unique<SugarDecorator>(
          std::make_unique<MilkDecorator>(std::make_unique<SimpleCoffee>())));
  std::cout << coffee4->get_description() << " - $" << coffee4->get_cost()
            << std::endl;

  return 0;
}
