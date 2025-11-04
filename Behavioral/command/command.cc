// Created: 2025-11-03
// Filename: command.cc
// Description: Command design pattern demonstration
// Copyright 2025

#include "command.hpp"

#include <iostream>

int main() {
  BankAccount account(100);
  CommandInvoker invoker;

  std::cout << "Initial balance: " << account.get_balance() << std::endl;

  // Execute commands
  invoker.execute(std::make_shared<DepositCommand>(account, 50));
  std::cout << "After deposit 50: " << account.get_balance() << std::endl;

  invoker.execute(std::make_shared<WithdrawCommand>(account, 30));
  std::cout << "After withdraw 30: " << account.get_balance() << std::endl;

  invoker.execute(std::make_shared<DepositCommand>(account, 25));
  std::cout << "After deposit 25: " << account.get_balance() << std::endl;

  // Undo operations
  std::cout << "\n--- Undoing operations ---" << std::endl;
  invoker.undo();
  std::cout << "After undo 1: " << account.get_balance() << std::endl;

  invoker.undo();
  std::cout << "After undo 2: " << account.get_balance() << std::endl;

  invoker.undo();
  std::cout << "After undo 3: " << account.get_balance() << std::endl;

  // Redo operations
  std::cout << "\n--- Redoing operations ---" << std::endl;
  invoker.redo();
  std::cout << "After redo 1: " << account.get_balance() << std::endl;

  invoker.redo();
  std::cout << "After redo 2: " << account.get_balance() << std::endl;

  // Failed withdraw
  std::cout << "\n--- Failed withdraw (overdraft limit) ---" << std::endl;
  invoker.execute(std::make_shared<WithdrawCommand>(account, 1000));
  std::cout << "After failed withdraw: " << account.get_balance() << std::endl;

  invoker.undo();
  std::cout << "After undo failed withdraw: " << account.get_balance()
            << std::endl;

  return 0;
}
