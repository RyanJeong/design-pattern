// Created: 2025-11-03
// Filename: template_method.hpp
// Description: Template Method design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_TEMPLATE_METHOD_TEMPLATE_METHOD_HPP_
#define BEHAVIORAL_TEMPLATE_METHOD_TEMPLATE_METHOD_HPP_

#include <iostream>
#include <string>
#include <utility>

/**
 * @brief Game result
 * @note Immutable representation of game outcome
 */
struct GameResult {
  int winner_id;
  int total_turns;
  std::string game_type;

  GameResult(int winner, int turns, std::string type) noexcept
      : winner_id(winner), total_turns(turns), game_type(std::move(type)) {}
};

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
   * @return Game result
   * @side_effects Executes game flow (documented in implementations)
   * @throws None (noexcept)
   */
  GameResult Play() noexcept {
    Start();
    while (!HaveWinner()) TakeTurn();
    return End();
  }

 protected:
  /**
   * @brief Hook method - initialize game
   * @side_effects Implementation-specific
   * @throws None (noexcept)
   */
  virtual void Start() noexcept = 0;

  /**
   * @brief Hook method - check for winner
   * @return true if game has winner
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual bool HaveWinner() const noexcept = 0;

  /**
   * @brief Hook method - execute turn
   * @side_effects Updates game state
   * @throws None (noexcept)
   */
  virtual void TakeTurn() noexcept = 0;

  /**
   * @brief Hook method - end game
   * @return Game result
   * @side_effects Implementation-specific
   * @throws None (noexcept)
   */
  virtual GameResult End() noexcept {
    return GameResult(current_player_, 0, "Unknown");
  }
};

/**
 * @brief Concrete game implementation - Chess
 * @note Implements chess-specific game flow
 * @side_effects Prints game progress and updates game state
 */
class Chess : public Game {
 private:
  int turns_{0};
  static constexpr int kMaxTurns = 10;

 public:
  Chess() noexcept : Game(2) {}

  /**
   * @brief Initializes chess game
   * @side_effects Prints start message for demo feedback
   * @side_effects_reason Demonstration requirement: Template Method pattern
   *   controls high-level game algorithm; concrete implementations must
   *   provide observable behavior (e.g., logging) to demonstrate flow
   * @side_effects_what Writes to stdout for game progress visibility
   * @side_effects_impact Console I/O adds minimal overhead (one-time per game)
   * @side_effects_alternatives Inject logger; creates complexity for demo code
   * @throws None (noexcept)
   */
  void Start() noexcept override {
    std::cout << "Starting chess game with " << number_of_players_
              << " players\n";
  }

  /**
   * @brief Checks if game has winner
   * @return true when max turns reached
   * @side_effects None
   * @throws None (noexcept)
   */
  bool HaveWinner() const noexcept override { return turns_ == kMaxTurns; }

  /**
   * @brief Executes a chess turn
   * @side_effects Increments turn counter and prints turn info
   * @side_effects_reason Demonstration requirement: Makes game progress
   *   visible during demo without external logging setup
   * @side_effects_what Writes to stdout for game visibility
   * @side_effects_impact Console I/O adds minimal overhead (per turn)
   * @side_effects_alternatives Inject logger; adds complexity
   * @throws None (noexcept)
   */
  void TakeTurn() noexcept override {
    std::cout << "Turn " << turns_ << " - Player " << current_player_
              << " moves\n";
    turns_++;
    current_player_ = (current_player_ + 1) % number_of_players_;
  }

  /**
   * @brief Ends chess game
   * @return Game result with winner information
   * @side_effects Prints winner announcement (see TakeTurn rationale)
   * @throws None (noexcept)
   */
  GameResult End() noexcept override {
    std::cout << "Chess game finished. Player " << current_player_
              << " wins!\n";
    return GameResult(current_player_, turns_, "Chess");
  }
};

/**
 * @brief Concrete game implementation - Checkers
 * @note Implements checkers-specific game flow
 * @side_effects Prints game progress and updates game state
 */
class Checkers : public Game {
 private:
  int turns_{0};
  static constexpr int kMaxTurns = 15;

 public:
  Checkers() noexcept : Game(2) {}

  /**
   * @brief Initializes checkers game
   * @side_effects Prints start message for demo feedback (see Chess::Start
   * rationale)
   * @throws None (noexcept)
   */
  void Start() noexcept override {
    std::cout << "Starting checkers game with " << number_of_players_
              << " players\n";
  }

  /**
   * @brief Checks if game has winner
   * @return true when max turns reached
   * @side_effects None
   * @throws None (noexcept)
   */
  bool HaveWinner() const noexcept override { return turns_ == kMaxTurns; }

  /**
   * @brief Executes a checkers turn
   * @side_effects Increments turn counter and prints turn info (see
   * Chess::TakeTurn rationale)
   * @throws None (noexcept)
   */
  void TakeTurn() noexcept override {
    std::cout << "Turn " << turns_ << " - Player " << current_player_
              << " moves a piece\n";
    turns_++;
    current_player_ = (current_player_ + 1) % number_of_players_;
  }

  /**
   * @brief Ends checkers game
   * @return Game result with winner information
   * @side_effects Prints winner announcement (see Chess::End rationale)
   * @throws None (noexcept)
   */
  GameResult End() noexcept override {
    std::cout << "Checkers game finished. Player " << current_player_
              << " wins!\n";
    return GameResult(current_player_, turns_, "Checkers");
  }
};

#endif  // BEHAVIORAL_TEMPLATE_METHOD_TEMPLATE_METHOD_HPP_
