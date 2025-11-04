// Created: 2025-11-03
// Filename: producer_consumer.hpp
// Description: Producer-Consumer concurrency pattern implementation
// Copyright 2025

#pragma once

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

/**
 * @brief Item type for producer-consumer queue
 * @note Simple data type for demonstration
 * @side_effects None (data class)
 */
struct Item {
  int id;
  std::string data;

  Item(int id, const std::string& data) noexcept : id(id), data(data) {}
};

/**
 * @brief Thread-safe buffer for producer-consumer pattern
 * @note Synchronizes access between multiple producers and consumers
 * @thread_safety Fully thread-safe (mutex + condition variables)
 */
class Buffer {
 private:
  std::queue<Item> queue_;
  mutable std::mutex mutex_;
  std::condition_variable not_empty_;
  std::condition_variable not_full_;
  size_t max_size_;

 public:
  /**
   * @brief Constructs buffer with max size
   * @param max_size Maximum buffer capacity
   * @side_effects Initializes synchronization primitives
   * @throws None (noexcept)
   */
  explicit Buffer(size_t max_size) noexcept : max_size_(max_size) {}

  /**
   * @brief Produces (adds) item to buffer
   * @param item Item to produce
   * @side_effects Adds item to queue, notifies consumers
   * @throws None (noexcept)
   */
  void Produce(const Item& item) noexcept {
    std::unique_lock<std::mutex> lock(mutex_);

    // Wait if buffer is full
    not_full_.wait(lock, [this]() { return queue_.size() < max_size_; });

    queue_.push(item);
    std::cout << "[Producer] Produced: " << item.data << " (ID: " << item.id
              << "), Queue size: " << queue_.size() << std::endl;

    not_empty_.notify_one();
  }

  /**
   * @brief Consumes (removes) item from buffer
   * @return Consumed item
   * @side_effects Removes item from queue, notifies producers
   * @throws None (noexcept)
   */
  Item Consume() noexcept {
    std::unique_lock<std::mutex> lock(mutex_);

    // Wait if buffer is empty
    not_empty_.wait(lock, [this]() { return !queue_.empty(); });

    Item item = queue_.front();
    queue_.pop();
    std::cout << "[Consumer] Consumed: " << item.data << " (ID: " << item.id
              << "), Queue size: " << queue_.size() << std::endl;

    not_full_.notify_one();
    return item;
  }

  /**
   * @brief Gets current buffer size
   * @return Number of items in buffer
   * @side_effects None
   * @throws None (noexcept)
   */
  size_t size() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

  /**
   * @brief Checks if buffer is empty
   * @return True if buffer is empty
   * @side_effects None
   * @throws None (noexcept)
   */
  bool empty() const noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
  }
};

/**
 * @brief Producer thread worker
 * @note Produces items at regular intervals
 * @side_effects Pushes items to shared buffer
 */
class Producer {
 private:
  std::shared_ptr<Buffer> buffer_;
  int id_;
  int item_count_;

 public:
  /**
   * @brief Constructs producer
   * @param buffer Shared buffer reference
   * @param id Producer identifier
   * @param item_count Number of items to produce
   * @side_effects None
   * @throws None (noexcept)
   */
  // Take `buffer` by-value and move into the member to avoid an extra
  // copy of the `std::shared_ptr` during construction. This keeps the
  // call-site simple (pass by value) while ensuring only one copy of the
  // owning handle is retained by the `Producer` instance.
  Producer(std::shared_ptr<Buffer> buffer, int id, int item_count) noexcept
    : buffer_(std::move(buffer)), id_(id), item_count_(item_count) {}

  /**
   * @brief Runs producer thread
   * @side_effects Produces items to buffer
   * @throws None (noexcept)
   */
  void Run() noexcept {
    for (int i = 0; i < item_count_; ++i) {
      std::cout << "[Producer " << id_ << "] Producing item..." << std::endl;

      std::string data =
          "Item_P" + std::to_string(id_) + "_" + std::to_string(i);
      Item item(id_ * 100 + i, data);
      buffer_->Produce(item);

      // Simulate production delay.
      // We choose a relatively short delay (100 ms) for the producer to
      // simulate a source that produces items at a steady, moderate rate.
      // Keeping producer faster than consumer is useful in examples/demos
      // to create pressure on the buffer (so you can observe waiting,
      // blocking, and condition-variable notifications). This value is
      // arbitrary for illustration and can be tuned to demonstrate
      // different behaviors (e.g., no backpressure vs. buffer growth).
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
};

/**
 * @brief Consumer thread worker
 * @note Consumes items from buffer
 * @side_effects Pops items from shared buffer
 */
class Consumer {
 private:
  std::shared_ptr<Buffer> buffer_;
  int id_;
  int item_count_;

 public:
  /**
   * @brief Constructs consumer
   * @param buffer Shared buffer reference
   * @param id Consumer identifier
   * @param item_count Number of items to consume
   * @side_effects None
   * @throws None (noexcept)
   */
  // Take `buffer` by-value and move into the member to avoid an extra
  // copy of the `std::shared_ptr` during construction. The lambda that
  // captures the shared_ptr will have already made one copy; moving the
  // parameter into the member avoids a second copy at this point.
  Consumer(std::shared_ptr<Buffer> buffer, int id, int item_count) noexcept
    : buffer_(std::move(buffer)), id_(id), item_count_(item_count) {}

  /**
   * @brief Runs consumer thread
   * @side_effects Consumes items from buffer
   * @throws None (noexcept)
   */
  void Run() noexcept {
    for (int i = 0; i < item_count_; ++i) {
      std::cout << "[Consumer " << id_ << "] Attempting to consume item..." << std::endl;

      Item item = buffer_->Consume();

      // Simulate consumption delay.
      // The consumer intentionally uses a slightly longer delay (150 ms)
      // than the producer. Making the consumer slower models a realistic
      // processing step that takes more time than producing an item
      // (e.g., I/O or CPU-heavy work). This intentional difference
      // demonstrates how the buffer absorbs rate mismatches and how
      // consumers/producers synchronize via condition variables when
      // the buffer becomes empty or full (i.e., backpressure).
      std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
  }
};
