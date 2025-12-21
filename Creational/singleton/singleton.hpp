// Created: 2025-11-03
// Filename: singleton.hpp
// Description: Singleton design pattern implementation
// Copyright 2025

#ifndef CREATIONAL_SINGLETON_SINGLETON_HPP_
#define CREATIONAL_SINGLETON_SINGLETON_HPP_

#include <iostream>
#include <string>

/**
 * @brief Singleton class - ensures only one instance exists
 * @note Thread-safe using static initialization
 * @thread_safety Thread-safe (static initialization)
 */
class Logger {
 private:
  int log_count_;

  /**
   * @brief Private constructor
   * @side_effects Initializes log count
   * @throws None (noexcept)
   */
  Logger() noexcept : log_count_(0) {
    std::cout << "Logger instance created\n";
  }

 public:
  /**
   * @brief Deleted copy constructor
   */
  Logger(const Logger&) = delete;

  /**
   * @brief Deleted assignment operator
   */
  Logger& operator=(const Logger&) = delete;

  /**
   * @brief Gets the singleton instance
   * @return Reference to the singleton Logger
   * @side_effects None
   * @throws None (noexcept)
   */
  static Logger& instance() noexcept {
    static Logger instance;
    return instance;
  }

  /**
   * @brief Logs a message
   * @param message Message to log
   * @side_effects Increments log count and prints message to console
   * @side_effects_reason Demonstration requirement: Singleton pattern ensures
   *   a single globally accessible instance. Logging to console demonstrates
   *   persistence of state across multiple GetInstance() calls
   * @side_effects_what Increments counter and writes to stdout
   * @side_effects_impact Console I/O adds minimal latency (per log call)
   * @side_effects_alternatives Inject logger factory; adds complexity for demo
   * @throws None (noexcept)
   */
  void Log(const std::string& message) noexcept {
    log_count_++;
    std::cout << "[Log " << log_count_ << "] " << message << "\n";
  }

  /**
   * @brief Gets the number of logged messages
   * @return Total log count
   * @side_effects None
   * @throws None (noexcept)
   */
  int log_count() const noexcept { return log_count_; }
};

#endif  // CREATIONAL_SINGLETON_SINGLETON_HPP_
