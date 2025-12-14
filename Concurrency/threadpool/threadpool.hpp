// Created: 2025-11-03
// Filename: threadpool.hpp
// Description: ThreadPool concurrency pattern implementation
// Copyright 2025

#ifndef CONCURRENCY_THREADPOOL_THREADPOOL_HPP_
#define CONCURRENCY_THREADPOOL_THREADPOOL_HPP_

#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

/**
 * @brief Thread pool for managing worker threads
 * @note Reuses threads to execute queued tasks
 * @thread_safety Fully thread-safe
 */
class ThreadPool {
 private:
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> tasks_;
  mutable std::mutex mutex_;
  std::condition_variable condition_;
  bool stop_;

  /**
   * @brief Worker function for threads
   * @side_effects Executes tasks from queue
   * @throws None (noexcept)
   */
  void WorkerLoop() noexcept {
    while (true) {
      std::unique_lock<std::mutex> lock(mutex_);

      // Wait for task or stop signal
      condition_.wait(lock, [this]() { return !tasks_.empty() || stop_; });

      // Exit if stopped and no tasks remaining
      if (stop_ && tasks_.empty()) break;

      // Get and execute task
      if (!tasks_.empty()) {
        auto task = std::move(tasks_.front());
        tasks_.pop();
        lock.unlock();  // Release lock before executing task

        task();
      }
    }
  }

 public:
  /**
   * @brief Constructs thread pool with specified size
   * @param num_threads Number of worker threads
   * @side_effects Creates worker threads
   * @throws None (noexcept)
   */
  explicit ThreadPool(size_t num_threads) noexcept : stop_(false) {
    for (size_t i = 0; i < num_threads; ++i)
      workers_.emplace_back([this]() { WorkerLoop(); });

    std::cout << "ThreadPool created with " << num_threads << " workers\n";
  }

  /**
   * @brief Destructs thread pool
   * @side_effects Stops workers and waits for completion
   * @throws None (noexcept)
   */
  ~ThreadPool() noexcept {
    {
      std::unique_lock<std::mutex> lock(mutex_);
      stop_ = true;
    }
    condition_.notify_all();

    for (std::thread& worker : workers_)
      if (worker.joinable()) worker.join();
  }

  /**
   * @brief Enqueues a task for execution
   * @param function Task function to execute
   * @side_effects Adds task to queue, notifies worker
   * @throws None (noexcept)
   */
  template <typename F>
  void Enqueue(F function) noexcept {
    {
      std::unique_lock<std::mutex> lock(mutex_);

      if (stop_) {
        std::cerr << "Cannot enqueue task: ThreadPool is stopped\n";
        return;
      }

      tasks_.emplace(function);
    }
    condition_.notify_one();
  }

  /**
   * @brief Gets number of pending tasks
   * @return Task count in queue
   * @side_effects None
   * @throws None (noexcept)
   */
  size_t pending_tasks() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    return tasks_.size();
  }

  /**
   * @brief Gets number of worker threads
   * @return Worker thread count
   * @side_effects None
   * @throws None (noexcept)
   */
  size_t worker_count() const noexcept { return workers_.size(); }
};

/**
 * @brief Simulated task for demonstration
 * @note Represents work to be done by thread pool
 * @side_effects Prints to console for demo feedback
 */
class Task {
 private:
  int id_;

 public:
  /**
   * @brief Constructs task
   * @param id Task identifier
   * @side_effects None
   * @throws None (noexcept)
   */
  explicit Task(int id) noexcept : id_(id) {}

  /**
   * @brief Executes task
   * @side_effects Prints execution info, sleeps for simulation, and prints
   * completion
   * @side_effects_reason Demonstration requirement: ThreadPool pattern
   *   manages concurrent task execution. Console output shows task
   *   scheduling and execution across threads without external monitoring
   * @side_effects_what Writes to stdout for task execution visibility
   * @side_effects_impact Console I/O adds minor overhead per task
   * @side_effects_alternatives External monitoring service; adds complexity
   * @throws None (noexcept)
   */
  void Execute() const noexcept {
    std::cout << "[Task " << id_ << "] Started on thread "
              << std::this_thread::get_id() << "\n";

    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "[Task " << id_ << "] Completed\n";
  }
};

#endif  // CONCURRENCY_THREADPOOL_THREADPOOL_HPP_
