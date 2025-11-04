// Created: 2025-11-03
// Filename: prototype.cc
// Description: Prototype design pattern demonstration
// Copyright 2025

#include "prototype.hpp"

int main() {
  ShapeRegistry registry;

  // Register prototypes
  registry.register_prototype("circle",
                              std::make_unique<Circle>("Default Circle", 5.0));
  registry.register_prototype(
      "rectangle",
      std::make_unique<Rectangle>("Default Rectangle", 10.0, 20.0));

  std::cout << "=== Creating Shapes from Prototypes ===" << std::endl;

  // Clone circle prototype
  auto circle1 = registry.create_shape("circle");
  circle1->display();

  auto circle2 = registry.create_shape("circle");
  circle2->set_name("Cloned Circle 2");
  circle2->display();

  // Clone rectangle prototype
  std::cout << std::endl;
  auto rect1 = registry.create_shape("rectangle");
  rect1->display();

  auto rect2 = registry.create_shape("rectangle");
  rect2->set_name("Cloned Rectangle 2");
  rect2->display();

  return 0;
}
