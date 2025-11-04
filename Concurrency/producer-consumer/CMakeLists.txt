cmake_minimum_required(VERSION 3.10)
project(ProducerConsumer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -pthread")

add_executable(ProducerConsumer producer_consumer.cc)
target_link_libraries(ProducerConsumer pthread)
