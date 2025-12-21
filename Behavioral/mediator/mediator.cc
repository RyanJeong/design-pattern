// Created: 2025-11-03
// Filename: mediator.cc
// Description: Mediator design pattern demonstration
// Copyright 2025

#include "mediator.hpp"  // [NOLINT]


int main() {
  auto chat_room = std::make_shared<ChatRoom>();

  auto alice = std::make_unique<User>(chat_room.get(), "Alice");
  auto bob = std::make_unique<User>(chat_room.get(), "Bob");
  auto charlie = std::make_unique<User>(chat_room.get(), "Charlie");

  chat_room->RegisterUser(alice.get());
  chat_room->RegisterUser(bob.get());
  chat_room->RegisterUser(charlie.get());

  std::cout << "Alice sends a message:" << std::endl;
  auto msg1 = alice->Send("Hello everyone!");
  std::cout << "[Timestamp: " << msg1.timestamp << "]" << std::endl;

  std::cout << "\nBob sends a message:" << std::endl;
  auto msg2 = bob->Send("Hi Alice!");
  std::cout << "[Timestamp: " << msg2.timestamp << "]" << std::endl;

  std::cout << "\nCharlie sends a message:" << std::endl;
  auto msg3 = charlie->Send("Great to see you all!");
  std::cout << "[Timestamp: " << msg3.timestamp << "]" << std::endl;

  return 0;
}
