// Created: 2025-11-03
// Filename: memento.cc
// Description: Memento design pattern demonstration
// Copyright 2025

#include "memento.hpp"  // [NOLINT]

#include <iostream>

int main() {
  BankAccount account(100);
  BankAccountCaretaker caretaker;

  // Save initial state
  caretaker.Save(account.CreateMemento());
  std::cout << "Initial balance: " << account.GetBalance() << std::endl;

  // Perform operations
  account.Deposit(50);
  caretaker.Save(account.CreateMemento());
  std::cout << "After deposit 50: " << account.GetBalance() << std::endl;

  account.Withdraw(30);
  caretaker.Save(account.CreateMemento());
  std::cout << "After withdraw 30: " << account.GetBalance() << std::endl;

  account.Deposit(25);
  caretaker.Save(account.CreateMemento());
  std::cout << "After deposit 25: " << account.GetBalance() << std::endl;

  // Undo operations
  std::cout << "\n--- Undo Operations ---" << std::endl;

  auto memento = caretaker.Undo();
  auto result1 = account.RestoreFromMemento(memento);
  std::cout << "After undo 1: " << account.GetBalance() << " ("
            << result1.message << ")" << std::endl;

  memento = caretaker.Undo();
  auto result2 = account.RestoreFromMemento(memento);
  std::cout << "After undo 2: " << account.GetBalance() << " ("
            << result2.message << ")" << std::endl;

  // Redo operations
  std::cout << "\n--- Redo Operations ---" << std::endl;

  memento = caretaker.Redo();
  auto result3 = account.RestoreFromMemento(memento);
  std::cout << "After redo 1: " << account.GetBalance() << " ("
            << result3.message << ")" << std::endl;

  memento = caretaker.Redo();
  auto result4 = account.RestoreFromMemento(memento);
  std::cout << "After redo 2: " << account.GetBalance() << " ("
            << result4.message << ")" << std::endl;

  return 0;
}
