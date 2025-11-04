// Created: 2025-11-03
// Filename: strategy.cc
// Description: Strategy design pattern demonstration
// Copyright 2025

#include "strategy.hpp"

#include <iostream>

int main() {
  TextProcessor processor;

  // Use Markdown strategy
  processor.set_strategy(std::make_shared<MarkdownListStrategy>());
  processor.append_list({"alpha", "beta", "gamma"});
  std::cout << "Markdown format:\n" << processor.str();

  // Clear and use HTML strategy
  processor.clear();
  processor.set_strategy(std::make_shared<HtmlListStrategy>());
  processor.append_list({"one", "two", "three"});
  std::cout << "\nHTML format:\n" << processor.str();

  return 0;
}
