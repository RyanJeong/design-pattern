// Created: 2025-11-03
// Filename: threadpool.cc
// Description: ThreadPool pattern demonstration
// Copyright 2025

#include "threadpool.hpp"

int main() {
  std::cout << "============================================\n"
            << "ThreadPool Pattern Demonstration\n"
            << "============================================\n\n";

  // Create thread pool with 4 workers
  {
    ThreadPool pool(4);

    std::cout << "\nEnqueuing 12 tasks...\n\n";

    // Enqueue tasks
    for (int i = 1; i <= 12; ++i) {
      Task task(i);
      pool.enqueue([task]() { task.execute(); });
    }

    std::cout << "\nPending tasks: " << pool.pending_tasks() << "\n";
    std::cout << "Worker threads: " << pool.worker_count() << "\n\n";

    std::cout << "Waiting for all tasks to complete...\n\n";

    // Wait for all tasks to complete
    while (pool.pending_tasks() > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Give threads time to process remaining tasks
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::cout << "\n============================================\n"
            << "Demonstration complete\n"
            << "ThreadPool has been destroyed\n"
            << "============================================\n";

  return 0;
}
