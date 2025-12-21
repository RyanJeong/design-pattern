// Created: 2025-11-03
// Filename: command.cc
// Description: Command design pattern demonstration
// Copyright 2025

#include "command.hpp"  // [NOLINT]

#include <iostream>

int main() {
  BankAccount account(100);
  CommandInvoker invoker;

  std::cout << "Initial balance: " << account.GetBalance() << std::endl;

  // Execute commands
  auto result1 = invoker.Execute(std::make_shared<DepositCommand>(account, 50));
  std::cout << "After deposit 50: " << account.GetBalance() << " ("
            << result1.message << ")" << std::endl;

  auto result2 =
      invoker.Execute(std::make_shared<WithdrawCommand>(account, 30));
  std::cout << "After withdraw 30: " << account.GetBalance() << " ("
            << result2.message << ")" << std::endl;

  auto result3 = invoker.Execute(std::make_shared<DepositCommand>(account, 25));
  std::cout << "After deposit 25: " << account.GetBalance() << " ("
            << result3.message << ")" << std::endl;

  // Undo operations
  std::cout << "\n--- Undoing operations ---" << std::endl;
  auto undo1 = invoker.Undo();
  std::cout << "After undo 1: " << account.GetBalance() << " (" << undo1.message
            << ")" << std::endl;

  auto undo2 = invoker.Undo();
  std::cout << "After undo 2: " << account.GetBalance() << " (" << undo2.message
            << ")" << std::endl;

  auto undo3 = invoker.Undo();
  std::cout << "After undo 3: " << account.GetBalance() << " (" << undo3.message
            << ")" << std::endl;

  // Redo operations
  std::cout << "\n--- Redoing operations ---" << std::endl;
  auto redo1 = invoker.Redo();
  std::cout << "After redo 1: " << account.GetBalance() << " (" << redo1.message
            << ")" << std::endl;

  auto redo2 = invoker.Redo();
  std::cout << "After redo 2: " << account.GetBalance() << " (" << redo2.message
            << ")" << std::endl;

  // Failed withdraw
  std::cout << "\n--- Failed withdraw (overdraft limit) ---" << std::endl;
  auto failed =
      invoker.Execute(std::make_shared<WithdrawCommand>(account, 1000));
  std::cout << "After failed withdraw: " << account.GetBalance() << " ("
            << failed.message << ")" << std::endl;

  auto undo_failed = invoker.Undo();
  std::cout << "After undo failed withdraw: " << account.GetBalance() << " ("
            << undo_failed.message << ")" << std::endl;

  return 0;
}
