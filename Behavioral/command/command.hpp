// Created: 2025-11-03
// Filename: command.hpp
// Description: Command design pattern demonstration
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
  void Deposit(int amount) noexcept { balance_ += amount; }

  /**
   * @brief Withdraws money from account
   * @param amount Amount to withdraw
   * @return true if withdrawal successful, false otherwise
   * @side_effects May modify balance
   * @throws None (noexcept)
   */
  bool Withdraw(int amount) noexcept {
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
  int GetBalance() const noexcept { return balance_; }
};

/**
 * @brief Execution result of a command
 * @note Indicates success or failure of command execution
 */
struct ExecutionResult {
  bool success;
  const char* message;

  constexpr ExecutionResult(bool success_val,
                            const char* message_val = "") noexcept
      : success(success_val), message(message_val) {}
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
   * @return Result of execution
   * @side_effects Depends on concrete implementation
   * @throws None (noexcept)
   */
  virtual ExecutionResult Execute() noexcept = 0;

  /**
   * @brief Undoes the command
   * @return Result of undo operation
   * @side_effects Depends on concrete implementation
   * @throws None (noexcept)
   */
  virtual ExecutionResult Undo() noexcept = 0;
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
   * @return Result indicating success
   * @side_effects Increases account balance
   * @throws None (noexcept)
   */
  ExecutionResult Execute() noexcept override {
    account_.Deposit(amount_);
    return ExecutionResult(true, "Deposit successful");
  }

  /**
   * @brief Undoes deposit
   * @return Result of undo operation
   * @side_effects Decreases account balance
   * @throws None (noexcept)
   */
  ExecutionResult Undo() noexcept override {
    bool success = account_.Withdraw(amount_);
    return ExecutionResult(
        success, success ? "Undo deposit successful"
                         : "Undo deposit failed (insufficient funds)");
  }
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
   * @return Result indicating success or failure
   * @side_effects May decrease account balance
   * @throws None (noexcept)
   */
  ExecutionResult Execute() noexcept override {
    executed_ = account_.Withdraw(amount_);
    return ExecutionResult(executed_,
                           executed_ ? "Withdrawal successful"
                                     : "Withdrawal failed (overdraft limit)");
  }

  /**
   * @brief Undoes withdrawal
   * @return Result of undo operation
   * @side_effects Increases account balance if withdrawal was successful
   * @throws None (noexcept)
   */
  ExecutionResult Undo() noexcept override {
    if (executed_) {
      account_.Deposit(amount_);
      return ExecutionResult(true, "Undo withdrawal successful");
    }
    return ExecutionResult(true, "Nothing to undo");
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
   * @return Result of command execution
   * @side_effects Executes command and clears redo stack
   * @throws None (noexcept)
   */
  ExecutionResult Execute(std::shared_ptr<Command> command) noexcept {
    ExecutionResult result = command->Execute();
    if (result.success) {
      history_.push_back(command);
      redo_stack_.clear();  // Clear redo stack when new command executed
    }
    return result;
  }

  /**
   * @brief Undoes the last command
   * @return Result of undo operation
   * @side_effects May undo last command and affect receiver state
   * @throws None (noexcept)
   */
  ExecutionResult Undo() noexcept {
    if (!history_.empty()) {
      auto command = history_.back();
      history_.pop_back();
      ExecutionResult result = command->Undo();
      if (result.success) redo_stack_.push_back(command);
      return result;
    }
    return ExecutionResult(false, "Nothing to undo");
  }

  /**
   * @brief Redoes the last undone command
   * @return Result of redo operation
   * @side_effects May redo last command and affect receiver state
   * @throws None (noexcept)
   */
  ExecutionResult Redo() noexcept {
    if (!redo_stack_.empty()) {
      auto command = redo_stack_.back();
      redo_stack_.pop_back();
      ExecutionResult result = command->Execute();
      if (result.success) history_.push_back(command);
      return result;
    }
    return ExecutionResult(false, "Nothing to redo");
  }
};

#endif  // BEHAVIORAL_COMMAND_COMMAND_HPP_
