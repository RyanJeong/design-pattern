// Created: 2025-11-03
// Filename: prototype.cc
// Description: Prototype design pattern demonstration
// Copyright 2025

#include "prototype.hpp"  // [NOLINT]

#include <iostream>
#include <memory>

int main() {
  ShapeRegistry registry;

  // Register prototypes
  registry.RegisterPrototype("circle",
                             std::make_unique<Circle>("Default Circle", 5.0));
  registry.RegisterPrototype("rectangle", std::make_unique<Rectangle>(
                                              "Default Rectangle", 10.0, 20.0));

  std::cout << "=== Creating Shapes from Prototypes ===" << std::endl;

  // Clone circle prototype
  auto circle1 = registry.CreateShape("circle");
  circle1->Display();

  auto circle2 = registry.CreateShape("circle");
  circle2->set_name("Cloned Circle 2");
  circle2->Display();

  // Clone rectangle prototype
  std::cout << std::endl;
  auto rect1 = registry.CreateShape("rectangle");
  rect1->Display();

  auto rect2 = registry.CreateShape("rectangle");
  rect2->set_name("Cloned Rectangle 2");
  rect2->Display();

  return 0;
}
