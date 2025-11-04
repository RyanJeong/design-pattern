// Created: 2025-11-03
// Filename: interpreter.cc
// Description: Interpreter design pattern demonstration
// Copyright 2025

#include "interpreter.hpp"

int main() {
  // Build expression tree: ((5 + 3) * 2) - 4
  // = (8 * 2) - 4
  // = 16 - 4
  // = 12

  auto five = std::make_shared<Number>(5);
  auto three = std::make_shared<Number>(3);
  auto two = std::make_shared<Number>(2);
  auto four = std::make_shared<Number>(4);

  auto add_expr = std::make_shared<Add>(five, three);
  auto mul_expr = std::make_shared<Multiply>(add_expr, two);
  auto sub_expr = std::make_shared<Subtract>(mul_expr, four);

  std::cout << "Expression: ((5 + 3) * 2) - 4 = " << sub_expr->evaluate()
            << std::endl;

  // Another expression: 10 - (3 * 2)
  // = 10 - 6
  // = 4

  auto ten = std::make_shared<Number>(10);
  auto mul_expr2 = std::make_shared<Multiply>(three, two);
  auto sub_expr2 = std::make_shared<Subtract>(ten, mul_expr2);

  std::cout << "Expression: 10 - (3 * 2) = " << sub_expr2->evaluate()
            << std::endl;

  return 0;
}
