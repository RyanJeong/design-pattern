// Created: 2025-11-03
// Filename: mediator.cc
// Description: Mediator design pattern demonstration
// Copyright 2025

#include "mediator.hpp"

int main() {
  auto chat_room = std::make_shared<ChatRoom>();

  auto alice = std::make_unique<User>(chat_room.get(), "Alice");
  auto bob = std::make_unique<User>(chat_room.get(), "Bob");
  auto charlie = std::make_unique<User>(chat_room.get(), "Charlie");

  chat_room->register_user(alice.get());
  chat_room->register_user(bob.get());
  chat_room->register_user(charlie.get());

  std::cout << "Alice sends a message:" << std::endl;
  alice->send("Hello everyone!");

  std::cout << "\nBob sends a message:" << std::endl;
  bob->send("Hi Alice!");

  std::cout << "\nCharlie sends a message:" << std::endl;
  charlie->send("Great to see you all!");

  return 0;
}
