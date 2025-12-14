// Created: 2025-11-03
// Filename: producer_consumer.cc
// Description: Producer-Consumer pattern demonstration
// Copyright 2025

#include "producer_consumer.hpp"  // [NOLINT]

#include <iostream>
#include <memory>
#include <thread>
#include <vector>

int main() {
  std::cout << "============================================\n"
            << "Producer-Consumer Pattern Demonstration\n"
            << "============================================\n\n";

  // Create shared buffer with capacity of 5
  auto buffer = std::make_shared<Buffer>(5);

  // Create threads
  std::vector<std::thread> threads;

  // Create 2 producer threads
  std::cout << "Starting 2 producers (3 items each)...\n\n";
  for (int i = 1; i <= 2; ++i) {
    threads.emplace_back([buffer, i]() {
      Producer producer(buffer, i, 3);
      producer.Run();
    });
  }

  // Create 2 consumer threads
  std::cout << "Starting 2 consumers (3 items each)...\n\n";
  for (int i = 1; i <= 2; ++i) {
    threads.emplace_back([buffer, i]() {
      Consumer consumer(buffer, i, 3);
      consumer.Run();
    });
  }

  // Wait for all threads to complete
  for (auto& thread : threads)
    if (thread.joinable()) thread.join();

  std::cout << "\n============================================\n"
            << "Demonstration complete\n"
            << "Final buffer size: " << buffer->size() << "\n"
            << "============================================\n";

  return 0;
}
