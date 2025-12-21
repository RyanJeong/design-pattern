// Created: 2025-11-03
// Filename: builder.hpp
// Description: Builder design pattern implementation
// Copyright 2025

#ifndef CREATIONAL_BUILDER_BUILDER_HPP_
#define CREATIONAL_BUILDER_BUILDER_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <utility>

/**
 * @brief Product - the complex object being built
 * @note Created by Builder
 * @side_effects None (after construction)
 */
class Computer {
 private:
  std::string cpu_;
  std::string ram_;
  std::string storage_;
  std::string gpu_;

 public:
  // Accept parameters by value to allow callers to move strings in and
  // avoid unnecessary copies. Move into members.
  explicit Computer(std::string cpu, std::string ram, std::string storage,
                    std::string gpu) noexcept
      : cpu_(std::move(cpu)),
        ram_(std::move(ram)),
        storage_(std::move(storage)),
        gpu_(std::move(gpu)) {}

  /**
   * @brief Displays computer configuration
   * @side_effects Prints configuration to console for demo feedback
   * @side_effects_reason Demonstration requirement: Builder pattern creates
   *   complex objects step-by-step. Console output shows final configuration
   *   without requiring test assertion infrastructure
   * @side_effects_what Writes to stdout for configuration visibility
   * @side_effects_impact Console I/O adds minimal overhead (one-time per build)
   * @side_effects_alternatives Use structured return value; hides output during
   * demo
   * @throws None (noexcept)
   */
  void display() const noexcept {
    std::cout << "Computer Configuration:\n";
    std::cout << "  CPU: " << cpu_ << "\n";
    std::cout << "  RAM: " << ram_ << "\n";
    std::cout << "  Storage: " << storage_ << "\n";
    std::cout << "  GPU: " << gpu_ << "\n";
  }
};

/**
 * @brief Abstract Builder interface
 * @note Base class for concrete builders
 * @side_effects None (abstract)
 */
class ComputerBuilder {
 protected:
  std::string cpu_;
  std::string ram_;
  std::string storage_;
  std::string gpu_;

 public:
  virtual ~ComputerBuilder() = default;

  /**
   * @brief Sets CPU
   * @param cpu CPU specification
   * @side_effects Updates builder state
   * @throws None (noexcept)
   */
  virtual ComputerBuilder& set_cpu(std::string cpu) noexcept {
    cpu_ = std::move(cpu);
    return *this;
  }

  /**
   * @brief Sets RAM
   * @param ram RAM specification
   * @side_effects Updates builder state
   * @throws None (noexcept)
   */
  virtual ComputerBuilder& set_ram(std::string ram) noexcept {
    ram_ = std::move(ram);
    return *this;
  }

  /**
   * @brief Sets Storage
   * @param storage Storage specification
   * @side_effects Updates builder state
   * @throws None (noexcept)
   */
  virtual ComputerBuilder& set_storage(std::string storage) noexcept {
    storage_ = std::move(storage);
    return *this;
  }

  /**
   * @brief Sets GPU
   * @param gpu GPU specification
   * @side_effects Updates builder state
   * @throws None (noexcept)
   */
  virtual ComputerBuilder& set_gpu(std::string gpu) noexcept {
    gpu_ = std::move(gpu);
    return *this;
  }

  /**
   * @brief Builds the Computer
   * @return Built Computer instance
   * @side_effects Creates new Computer
   * @throws None (noexcept)
   */
  virtual Computer Build() noexcept {
    // Move builder strings into the constructed Computer to avoid copies.
    return Computer(std::move(cpu_), std::move(ram_), std::move(storage_),
                    std::move(gpu_));
  }
};

/**
 * @brief Concrete Builder for gaming computers
 * @note Builds gaming-optimized computers
 * @side_effects Modifies builder state
 */
class GamingComputerBuilder : public ComputerBuilder {
 public:
  /**
   * @brief Sets gaming-optimized defaults
   * @side_effects Updates builder state with gaming specs
   * @throws None (noexcept)
   */
  GamingComputerBuilder() noexcept {
    cpu_ = "Intel Core i9";
    ram_ = "32GB DDR4";
    storage_ = "1TB NVMe SSD";
    gpu_ = "RTX 3080";
  }
};

/**
 * @brief Concrete Builder for workstations
 * @note Builds workstation computers
 * @side_effects Modifies builder state
 */
class WorkstationBuilder : public ComputerBuilder {
 public:
  /**
   * @brief Sets workstation-optimized defaults
   * @side_effects Updates builder state with workstation specs
   * @throws None (noexcept)
   */
  WorkstationBuilder() noexcept {
    cpu_ = "Intel Xeon";
    ram_ = "64GB DDR4";
    storage_ = "2TB NVMe SSD";
    gpu_ = "RTX A6000";
  }
};

#endif  // CREATIONAL_BUILDER_BUILDER_HPP_
