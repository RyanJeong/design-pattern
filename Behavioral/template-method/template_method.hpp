// Created: 2025-11-03
// Filename: template_method.hpp
// Description: Template Method design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_TEMPLATE_METHOD_TEMPLATE_METHOD_HPP_
#define BEHAVIORAL_TEMPLATE_METHOD_TEMPLATE_METHOD_HPP_

#include <iostream>
#include <string>

/**
 * @brief Abstract class defining algorithm template
 * @note Base class with template method and hooks
 * @side_effects None (abstract)
 */
class Game {
 protected:
  int number_of_players_;
  int current_player_{0};

 public:
  explicit Game(int number_of_players) noexcept
      : number_of_players_(number_of_players) {}

  virtual ~Game() = default;

  /**
   * @brief Template method - defines algorithm structure
   * @side_effects Executes game flow
   * @throws None (noexcept)
   */
  void play() noexcept {
    start();
    while (!have_winner()) { take_turn(); }
    end();
  }

 protected:
  /**
   * @brief Hook method - initialize game
   * @side_effects None (abstract)
   * @throws None (noexcept)
   */
  virtual void start() noexcept = 0;

  /**
   * @brief Hook method - check for winner
   * @return true if game has winner
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual bool have_winner() const noexcept = 0;

  /**
   * @brief Hook method - execute turn
   * @side_effects Updates game state
   * @throws None (noexcept)
   */
  virtual void take_turn() noexcept = 0;

  /**
   * @brief Hook method - end game
   * @side_effects Prints winner
   * @throws None (noexcept)
   */
  virtual void end() noexcept { std::cout << "Game finished\n"; }
};

/**
 * @brief Concrete game implementation - Chess
 * @note Implements chess-specific game flow
 * @side_effects Prints game progress
 */
class Chess : public Game {
 private:
  int turns_{0};
  static constexpr int kMaxTurns = 10;

 public:
  Chess() noexcept : Game(2) {}

  /**
   * @brief Initializes chess game
   * @side_effects Prints start message
   * @throws None (noexcept)
   */
  void start() noexcept override {
    std::cout << "Starting chess game with " << number_of_players_
              << " players\n";
  }

  /**
   * @brief Checks if game has winner
   * @return true when max turns reached
   * @side_effects None
   * @throws None (noexcept)
   */
  bool have_winner() const noexcept override { return turns_ == kMaxTurns; }

  /**
   * @brief Executes a chess turn
   * @side_effects Increments turn counter
   * @throws None (noexcept)
   */
  void take_turn() noexcept override {
    std::cout << "Turn " << turns_ << " - Player " << current_player_
              << " moves\n";
    turns_++;
    current_player_ = (current_player_ + 1) % number_of_players_;
  }

  /**
   * @brief Ends chess game
   * @side_effects Prints winner announcement
   * @throws None (noexcept)
   */
  void end() noexcept override {
    std::cout << "Chess game finished. Player " << current_player_
              << " wins!\n";
  }
};

/**
 * @brief Concrete game implementation - Checkers
 * @note Implements checkers-specific game flow
 * @side_effects Prints game progress
 */
class Checkers : public Game {
 private:
  int turns_{0};
  static constexpr int kMaxTurns = 15;

 public:
  Checkers() noexcept : Game(2) {}

  /**
   * @brief Initializes checkers game
   * @side_effects Prints start message
   * @throws None (noexcept)
   */
  void start() noexcept override {
    std::cout << "Starting checkers game with " << number_of_players_
              << " players\n";
  }

  /**
   * @brief Checks if game has winner
   * @return true when max turns reached
   * @side_effects None
   * @throws None (noexcept)
   */
  bool have_winner() const noexcept override { return turns_ == kMaxTurns; }

  /**
   * @brief Executes a checkers turn
   * @side_effects Increments turn counter
   * @throws None (noexcept)
   */
  void take_turn() noexcept override {
    std::cout << "Turn " << turns_ << " - Player " << current_player_
              << " moves a piece\n";
    turns_++;
    current_player_ = (current_player_ + 1) % number_of_players_;
  }

  /**
   * @brief Ends checkers game
   * @side_effects Prints winner announcement
   * @throws None (noexcept)
   */
  void end() noexcept override {
    std::cout << "Checkers game finished. Player " << current_player_
              << " wins!\n";
  }
};

#endif  // BEHAVIORAL_TEMPLATE_METHOD_TEMPLATE_METHOD_HPP_
