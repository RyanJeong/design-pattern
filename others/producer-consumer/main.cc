#include <atomic>
#include <chrono>
#include <condition_variable>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>

std::queue<std::vector<float>> data_queue;
std::mutex queue_mutex;
std::condition_variable data_condition;
std::atomic<bool> running(true);
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(-1.0, 1.0);

// Ctrl+C signal handler
void signal_handler(int signum) {
  running = false;
  data_condition.notify_all();
}

// Data producer function
void produce_data(int n) {
  auto start_time = std::chrono::steady_clock::now();
  while (running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 0.5 seconds
    for (int i = 0; i < n && running; ++i) {
      std::vector<float> data(11025);
      for (auto& val : data) val = dis(gen);

      {
        std::lock_guard<std::mutex> lock(queue_mutex);
        data_queue.push(data);
      }

      data_condition.notify_one();
    }
    auto current_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = current_time - start_time;
    std::cout << "Data produced at: " << std::fixed << std::setprecision(2)
              << elapsed_seconds.count() << " seconds" << std::endl;
  }
}

// Data consumer function
void consume_data(int thread_id) {
  while (running) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    data_condition.wait(lock, [] { return !data_queue.empty() || !running; });

    if (!data_queue.empty()) {
      std::vector<float> data = data_queue.front();
      data_queue.pop();
      lock.unlock();

      auto start_time = std::chrono::steady_clock::now();
      std::vector<float> combined_data(22050);
      std::copy(data.begin(), data.end(), combined_data.begin());
      std::copy(data.begin(), data.end(), combined_data.begin() + 11025);
      float sum = 0;
      int idx = 0;
      for (const auto& val : combined_data) {
        sum += val;
        ++idx;
      }
      float average = sum / combined_data.size();
      auto end_time = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsed_seconds = end_time - start_time;

      std::cout << "Thread " << thread_id << " calculated average: " << average
                << "(" << idx << ") in " << std::fixed << std::setprecision(2)
                << elapsed_seconds.count() << " seconds" << std::endl;
    } else {
      lock.unlock();
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <number of data sets>" << std::endl;
    return 1;
  }

  int n = std::atoi(argv[1]);
  if (n <= 0) {
    std::cerr << "The number of data sets must be a positive integer."
              << std::endl;
    return 1;
  }

  std::srand(std::time(nullptr));

  // Set up signal handler
  std::signal(SIGINT, signal_handler);

  // Create thread pool
  const int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;

  // Start data producer thread
  std::thread producer(produce_data, n);

  // Start data consumer threads
  for (int i = 0; i < num_threads; ++i) threads.emplace_back(consume_data, i);

  // Wait for all threads to finish
  producer.join();
  for (auto& thread : threads) thread.join();

  return 0;
}
