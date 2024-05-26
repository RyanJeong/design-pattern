# Multithreaded Data Processing with Producer-Consumer Pattern

This C++ program demonstrates multithreaded data processing using a thread pool. It generates dummy data vectors, processes them by concatenating and calculating their arithmetic mean, and gracefully terminates threads upon receiving a Ctrl+C signal.

## Producer-Consumer Pattern
The `produce_data` function acts as the producer, generating vectors of dummy data and pushing them into a shared queue (`data_queue`). It produces data at 0.5-second intervals and continues until the running flag is set to false.
The `consume_data` function acts as the consumer, which waits for data to be available in the queue. Once data is available, it reads two vectors, concatenates them, calculates their arithmetic mean, and measures the time taken for this computation.

## Thread Pool
The program creates a pool of threads (`threads`) that execute the `consume_data` function. This allows for concurrent data processing from the queue, leveraging multiple CPU cores for improved performance.

## Signal Handling
The program includes a signal handler (`signal_handler`) to handle the Ctrl+C interrupt (SIGINT). When the interrupt is received, the `running` flag is set to `false`, and all threads are notified to terminate gracefully.

## Synchronization Mechanisms
The program uses `std::mutex` and `std::condition_variable` to synchronize access to the shared queue and ensure safe communication between producer and consumer threads.
