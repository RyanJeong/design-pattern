// Created: 2025-11-03
// Filename: strategy.cc
// Description: Strategy design pattern demonstration
// Copyright 2025

#include "strategy.hpp"  // [NOLINT]

#include <iostream>

int main() {
  // Use Markdown strategy
  TextProcessor md_processor;
  auto md_result =
      md_processor.WithStrategy(std::make_shared<MarkdownListStrategy>())
          .AppendList({"alpha", "beta", "gamma"});
  std::cout << "Markdown format:\n" << md_result.str();

  // Use HTML strategy with different processor
  TextProcessor html_processor;
  auto html_result =
      html_processor.WithStrategy(std::make_shared<HtmlListStrategy>())
          .AppendList({"one", "two", "three"});
  std::cout << "\nHTML format:\n" << html_result.str();

  return 0;
}
