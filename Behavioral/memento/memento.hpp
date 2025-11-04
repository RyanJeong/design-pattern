// Created: 2025-11-03
// Filename: memento.hpp
// Description: Memento design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_MEMENTO_MEMENTO_HPP_
#define BEHAVIORAL_MEMENTO_MEMENTO_HPP_

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Memento - stores snapshot of object state
 * @note Immutable representation of state
 * @side_effects None
 */
class BankAccountMemento {
 private:
  int balance_;

 public:
  explicit BankAccountMemento(int balance) noexcept : balance_(balance) {}

  friend class BankAccount;
  friend class BankAccountCaretaker;

 public:
  /**
   * @brief Gets the stored balance
   * @return Stored balance value
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_balance() const noexcept { return balance_; }
};

/**
 * @brief Originator - creates mementos and restores from them
 * @note Mutable object that can save/restore state
 * @thread_safety Not thread-safe
 */
class BankAccount {
 private:
  int balance_;

 public:
  explicit BankAccount(int initial_balance) noexcept
      : balance_(initial_balance) {}

  /**
   * @brief Gets current balance
   * @return Current balance
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_balance() const noexcept { return balance_; }

  /**
   * @brief Deposits money
   * @param amount Amount to deposit
   * @side_effects Increases balance
   * @throws None (noexcept)
   */
  void deposit(int amount) noexcept { balance_ += amount; }

  /**
   * @brief Withdraws money
   * @param amount Amount to withdraw
   * @return true if successful, false otherwise
   * @side_effects May decrease balance
   * @throws None (noexcept)
   */
  bool withdraw(int amount) noexcept {
    if (balance_ >= amount) {
      balance_ -= amount;
      return true;
    }
    return false;
  }

  /**
   * @brief Creates a memento of current state
   * @return Memento capturing current balance
   * @side_effects None
   * @throws None (noexcept)
   */
  std::shared_ptr<BankAccountMemento> create_memento() const noexcept {
    return std::make_shared<BankAccountMemento>(balance_);
  }

  /**
   * @brief Restores state from memento
   * @param memento Memento to restore from
   * @side_effects Restores balance to saved value
   * @throws None (noexcept)
   */
  void restore_from_memento(
      const std::shared_ptr<BankAccountMemento>& memento) noexcept {
    if (memento) { balance_ = memento->get_balance(); }
  }
};

/**
 * @brief Caretaker - manages mementos and undo/redo
 * @note Stores history of mementos
 * @thread_safety Not thread-safe
 */
class BankAccountCaretaker {
 private:
  std::vector<std::shared_ptr<BankAccountMemento>> history_;
  int current_index_{-1};

 public:
  /**
   * @brief Saves a memento to history
   * @param memento Memento to save
   * @side_effects Adds memento and clears redo stack
   * @throws None (noexcept)
   */
  void save(const std::shared_ptr<BankAccountMemento>& memento) noexcept {
    // Remove any redo history
    if (current_index_ < static_cast<int>(history_.size()) - 1) {
      history_.erase(history_.begin() + current_index_ + 1, history_.end());
    }
    history_.push_back(memento);
    current_index_++;
  }

  /**
   * @brief Undoes to previous state
   * @return Memento to restore, nullptr if at beginning
   * @side_effects Moves back in history
   * @throws None (noexcept)
   */
  std::shared_ptr<BankAccountMemento> undo() noexcept {
    if (current_index_ > 0) {
      current_index_--;
      return history_[current_index_];
    }
    return nullptr;
  }

  /**
   * @brief Redoes to next state
   * @return Memento to restore, nullptr if at end
   * @side_effects Moves forward in history
   * @throws None (noexcept)
   */
  std::shared_ptr<BankAccountMemento> redo() noexcept {
    if (current_index_ < static_cast<int>(history_.size()) - 1) {
      current_index_++;
      return history_[current_index_];
    }
    return nullptr;
  }
};

#endif  // BEHAVIORAL_MEMENTO_MEMENTO_HPP_
