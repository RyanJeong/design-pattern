# Producer-Consumer Pattern

## Overview

The Producer-Consumer pattern is a concurrency design pattern that coordinates work between multiple threads using a shared buffer. Producers add items to the buffer, and consumers remove items. This pattern is essential for:

- **Decoupling**: Producers and consumers operate independently
- **Rate Matching**: Buffer absorbs differences in production and consumption rates
- **Thread Safety**: Synchronized access prevents race conditions
- **Backpressure**: Producers wait if buffer is full, consumers wait if empty

## Structure

```text
+-------------+         +-----------+         +-------------+
| Producer 1  |-------->|           |-------->| Consumer 1  |
| (Thread)    |         | Buffer    |         | (Thread)    |
+-------------+         | (Queue)   |         +-------------+
                        | (Mutex)   |
+-------------+         | (CondVar) |         +-------------+
| Producer 2  |-------->|           |-------->| Consumer 2  |
| (Thread)    |         |           |         | (Thread)    |
+-------------+         +-----------+         +-------------+
```

## Key Components

### Buffer Class

- **Thread-safe queue**: Protects access with mutex
- **Condition variables**:
  - `not_empty_`: Notifies consumers when items available
  - `not_full_`: Notifies producers when space available
- **Max capacity**: Prevents unbounded memory growth

### Producer Class

- Generates items at regular intervals
- Pushes items to shared buffer
- Blocks if buffer is full

### Consumer Class

- Retrieves items from buffer
- Processes items (simulated with delays)
- Blocks if buffer is empty

## Use Cases

1. **Task Processing**: Worker threads consuming tasks from a queue
2. **Data Pipeline**: Processing stages in sequence
3. **Rate Limiting**: Buffering fast producers with slow consumers
4. **Distributed Systems**: Message queues between services

## Advantages

- Decouples producer and consumer logic
- Handles rate mismatches gracefully
- Thread-safe with condition variables
- Prevents deadlocks with proper synchronization
- Scalable to multiple producers/consumers

## Disadvantages

- Requires careful synchronization management (potential for deadlocks if misimplemented)
- Memory overhead for buffer capacity
- Complexity in error handling

## Synchronization Primitives Used

- **std::mutex**: Protects critical sections
- **std::condition_variable**: Coordinates thread wake-ups
- **std::unique_lock**: RAII wrapper for mutex locking
- **std::lock_guard**: RAII wrapper for simple locking

## C++14 Features

- `std::make_shared`: Creates managed shared pointer
- `std::unique_lock`: With condition variable support
- Lambda functions: Thread execution
- `std::this_thread::sleep_for`: Timing control
- Take-by-value + move: Producer/Consumer constructors accept the buffer as a
  `std::shared_ptr<Buffer>` by value and move it into the member (e.g. `buffer_(std::move(buffer))`)
  - Benefit: avoids one transient `shared_ptr` copy at construction (fewer atomic refcount ops) and clarifies ownership intent while preserving shared ownership semantics
