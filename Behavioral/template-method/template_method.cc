// Created: 2025-11-03
// Filename: template_method.cc
// Description: Template Method design pattern demonstration
// Copyright 2025

#include "template_method.hpp"  // [NOLINT]

#include <iostream>

int main() {
  std::cout << "=== Playing Chess ===" << std::endl;
  Chess chess;
  GameResult chess_result = chess.Play();
  std::cout << "Winner: Player " << chess_result.winner_id
            << " (Total turns: " << chess_result.total_turns << ")"
            << std::endl;

  std::cout << "\n=== Playing Checkers ===" << std::endl;
  Checkers checkers;
  GameResult checkers_result = checkers.Play();
  std::cout << "Winner: Player " << checkers_result.winner_id
            << " (Total turns: " << checkers_result.total_turns << ")"
            << std::endl;

  return 0;
}
