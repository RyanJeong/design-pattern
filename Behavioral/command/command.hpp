// Created: 2025-11-03
// Filename: command.hpp
// Description: Command design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_COMMAND_COMMAND_HPP_
#define BEHAVIORAL_COMMAND_COMMAND_HPP_

#include <memory>
#include <vector>

/**
 * @brief Receiver - the object that performs actual work
 * @note Mutable for demonstration purposes
 * @thread_safety Not thread-safe
 */
class BankAccount {
 private:
  int balance_;
  static constexpr int kOverdraftLimit = -500;

 public:
  explicit BankAccount(int initial_balance) noexcept
      : balance_(initial_balance) {}

  /**
   * @brief Deposits money into account
   * @param amount Amount to deposit
   * @side_effects Modifies balance
   * @throws None (noexcept)
   */
  void deposit(int amount) noexcept { balance_ += amount; }

  /**
   * @brief Withdraws money from account
   * @param amount Amount to withdraw
   * @return true if withdrawal successful, false otherwise
   * @side_effects May modify balance
   * @throws None (noexcept)
   */
  bool withdraw(int amount) noexcept {
    if (balance_ - amount >= kOverdraftLimit) {
      balance_ -= amount;
      return true;
    }
    return false;
  }

  /**
   * @brief Gets current balance
   * @return Current balance
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_balance() const noexcept { return balance_; }
};

/**
 * @brief Abstract command interface
 * @note Base class for all commands
 * @side_effects None (abstract)
 */
class Command {
 public:
  virtual ~Command() = default;

  /**
   * @brief Executes the command
   * @side_effects Depends on concrete implementation
   * @throws None (noexcept)
   */
  virtual void execute() noexcept = 0;

  /**
   * @brief Undoes the command
   * @side_effects Depends on concrete implementation
   * @throws None (noexcept)
   */
  virtual void undo() noexcept = 0;
};

/**
 * @brief Concrete command for deposit operation
 * @note Encapsulates a deposit request as an object
 * @side_effects Modifies receiver on execute/undo
 */
class DepositCommand : public Command {
 private:
  BankAccount& account_;
  int amount_;

 public:
  explicit DepositCommand(BankAccount& account, int amount) noexcept
      : account_(account), amount_(amount) {}

  /**
   * @brief Executes deposit
   * @side_effects Increases account balance
   * @throws None (noexcept)
   */
  void execute() noexcept override { account_.deposit(amount_); }

  /**
   * @brief Undoes deposit
   * @side_effects Decreases account balance
   * @throws None (noexcept)
   */
  void undo() noexcept override { account_.withdraw(amount_); }
};

/**
 * @brief Concrete command for withdrawal operation
 * @note Encapsulates a withdrawal request as an object
 * @side_effects Modifies receiver on execute/undo
 */
class WithdrawCommand : public Command {
 private:
  BankAccount& account_;
  int amount_;
  bool executed_{false};

 public:
  explicit WithdrawCommand(BankAccount& account, int amount) noexcept
      : account_(account), amount_(amount) {}

  /**
   * @brief Executes withdrawal
   * @side_effects May decrease account balance
   * @throws None (noexcept)
   */
  void execute() noexcept override { executed_ = account_.withdraw(amount_); }

  /**
   * @brief Undoes withdrawal
   * @side_effects Increases account balance if withdrawal was successful
   * @throws None (noexcept)
   */
  void undo() noexcept override {
    if (executed_) { account_.deposit(amount_); }
  }
};

/**
 * @brief Invoker - executes commands and maintains history
 * @note Manages command execution and undo/redo
 * @thread_safety Not thread-safe
 */
class CommandInvoker {
 private:
  std::vector<std::shared_ptr<Command>> history_;
  std::vector<std::shared_ptr<Command>> redo_stack_;

 public:
  /**
   * @brief Executes a command and adds to history
   * @param command Command to execute
   * @side_effects Executes command and clears redo stack
   * @throws None (noexcept)
   */
  void execute(std::shared_ptr<Command> command) noexcept {
    command->execute();
    history_.push_back(command);
    redo_stack_.clear();  // Clear redo stack when new command executed
  }

  /**
   * @brief Undoes the last command
   * @return true if undo was successful, false otherwise
   * @side_effects May undo last command and affect receiver state
   * @throws None (noexcept)
   */
  bool undo() noexcept {
    if (!history_.empty()) {
      auto command = history_.back();
      history_.pop_back();
      command->undo();
      redo_stack_.push_back(command);
      return true;
    }
    return false;
  }

  /**
   * @brief Redoes the last undone command
   * @return true if redo was successful, false otherwise
   * @side_effects May redo last command and affect receiver state
   * @throws None (noexcept)
   */
  bool redo() noexcept {
    if (!redo_stack_.empty()) {
      auto command = redo_stack_.back();
      redo_stack_.pop_back();
      command->execute();
      history_.push_back(command);
      return true;
    }
    return false;
  }
};

#endif  // BEHAVIORAL_COMMAND_COMMAND_HPP_
