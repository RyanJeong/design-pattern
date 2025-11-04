// Created: 2025-11-03
// Filename: memento.cc
// Description: Memento design pattern demonstration
// Copyright 2025

#include "memento.hpp"

#include <iostream>

int main() {
  BankAccount account(100);
  BankAccountCaretaker caretaker;

  // Save initial state
  caretaker.save(account.create_memento());
  std::cout << "Initial balance: " << account.get_balance() << std::endl;

  // Perform operations
  account.deposit(50);
  caretaker.save(account.create_memento());
  std::cout << "After deposit 50: " << account.get_balance() << std::endl;

  account.withdraw(30);
  caretaker.save(account.create_memento());
  std::cout << "After withdraw 30: " << account.get_balance() << std::endl;

  account.deposit(25);
  caretaker.save(account.create_memento());
  std::cout << "After deposit 25: " << account.get_balance() << std::endl;

  // Undo operations
  std::cout << "\n--- Undo Operations ---" << std::endl;

  auto memento = caretaker.undo();
  account.restore_from_memento(memento);
  std::cout << "After undo 1: " << account.get_balance() << std::endl;

  memento = caretaker.undo();
  account.restore_from_memento(memento);
  std::cout << "After undo 2: " << account.get_balance() << std::endl;

  // Redo operations
  std::cout << "\n--- Redo Operations ---" << std::endl;

  memento = caretaker.redo();
  account.restore_from_memento(memento);
  std::cout << "After redo 1: " << account.get_balance() << std::endl;

  memento = caretaker.redo();
  account.restore_from_memento(memento);
  std::cout << "After redo 2: " << account.get_balance() << std::endl;

  return 0;
}
