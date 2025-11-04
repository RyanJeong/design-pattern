// Created: 2025-11-03
// Filename: template_method.cc
// Description: Template Method design pattern demonstration
// Copyright 2025

#include "template_method.hpp"

int main() {
  std::cout << "=== Playing Chess ===" << std::endl;
  Chess chess;
  chess.play();

  std::cout << "\n=== Playing Checkers ===" << std::endl;
  Checkers checkers;
  checkers.play();

  return 0;
}
