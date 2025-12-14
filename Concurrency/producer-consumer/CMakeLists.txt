cmake_minimum_required(VERSION 3.10)
project(ProducerConsumer)

# C++ standard configuration
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Create executable
add_executable(ProducerConsumer producer_consumer.cc)

# Compiler-specific options
if(MSVC)
  target_compile_options(ProducerConsumer PRIVATE /W4 /WX /permissive- /std:c++14)
else()
  # GCC and Clang
  target_compile_options(ProducerConsumer PRIVATE
    -Wall -Wextra -pedantic -Werror
    -Wformat=2 -Wshadow -Wunused-parameter
    -Wlogical-op -Wshift-overflow=2
    -Wpacked -Wstrict-overflow=4
    -Wuninitialized -Wfloat-equal -Wwrite-strings
    -Wfloat-conversion
  )

  # Additional GCC-specific warnings
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ProducerConsumer PRIVATE
      -Wtrampolines -Wduplicated-branches -Wduplicated-cond
      -Wlogical-op -Wuseless-cast
    )
  endif()

  # Clang-specific warnings
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(ProducerConsumer PRIVATE
      -Wthread-safety
    )
  endif()
endif()

# Sanitizers for debug builds
if(CMAKE_BUILD_TYPE MATCHES Debug)
  if(NOT MSVC)
    target_compile_options(ProducerConsumer PRIVATE
      -fsanitize=address,undefined,thread
    )
    target_link_options(ProducerConsumer PRIVATE
      -fsanitize=address,undefined,thread
    )
  endif()
endif()

# Link pthread
target_link_libraries(ProducerConsumer PRIVATE pthread)
