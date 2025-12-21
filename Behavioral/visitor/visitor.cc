// Created: 2025-11-03
// Filename: visitor.cc
// Description: Visitor design pattern demonstration
// Copyright 2025

#include "visitor.hpp"  // [NOLINT]

#include <iostream>
#include <memory>
#include <string>

int main() {
  // Build expression: (3 + 5) - 2
  auto three = std::make_shared<Literal>(3);
  auto five = std::make_shared<Literal>(5);
  auto two = std::make_shared<Literal>(2);

  auto add = std::make_shared<BinaryOp>(three, five, BinaryOp::ADD);
  auto sub = std::make_shared<BinaryOp>(add, two, BinaryOp::SUBTRACT);

  // Print the expression
  PrintVisitor printer;
  std::string expr = sub->Accept(printer);
  std::cout << "Expression: " << expr << std::endl;

  // Evaluate the expression
  EvalVisitor evaluator;
  std::string result = evaluator.Evaluate(sub);
  std::cout << "Result: " << result << std::endl;

  // Build another expression: 10 + (2 - 1)
  auto ten = std::make_shared<Literal>(10);
  auto one = std::make_shared<Literal>(1);

  auto inner_sub = std::make_shared<BinaryOp>(two, one, BinaryOp::SUBTRACT);
  auto outer_add = std::make_shared<BinaryOp>(ten, inner_sub, BinaryOp::ADD);

  // Print and evaluate
  PrintVisitor printer2;
  std::string expr2 = outer_add->Accept(printer2);
  std::cout << "\nExpression: " << expr2 << std::endl;

  EvalVisitor evaluator2;
  std::string result2 = evaluator2.Evaluate(outer_add);
  std::cout << "Result: " << result2 << std::endl;

  return 0;
}
