// Created: 2025-11-03
// Filename: builder.hpp
// Description: Builder design pattern implementation
// Copyright 2025

#ifndef CREATIONAL_BUILDER_BUILDER_HPP_
#define CREATIONAL_BUILDER_BUILDER_HPP_

#include <iostream>
#include <memory>
#include <string>

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
  explicit Computer(const std::string& cpu, const std::string& ram,
                    const std::string& storage, const std::string& gpu) noexcept
      : cpu_(cpu), ram_(ram), storage_(storage), gpu_(gpu) {}

  /**
   * @brief Displays computer configuration
   * @side_effects Prints to console
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
  virtual ComputerBuilder& set_cpu(const std::string& cpu) noexcept {
    cpu_ = cpu;
    return *this;
  }

  /**
   * @brief Sets RAM
   * @param ram RAM specification
   * @side_effects Updates builder state
   * @throws None (noexcept)
   */
  virtual ComputerBuilder& set_ram(const std::string& ram) noexcept {
    ram_ = ram;
    return *this;
  }

  /**
   * @brief Sets Storage
   * @param storage Storage specification
   * @side_effects Updates builder state
   * @throws None (noexcept)
   */
  virtual ComputerBuilder& set_storage(const std::string& storage) noexcept {
    storage_ = storage;
    return *this;
  }

  /**
   * @brief Sets GPU
   * @param gpu GPU specification
   * @side_effects Updates builder state
   * @throws None (noexcept)
   */
  virtual ComputerBuilder& set_gpu(const std::string& gpu) noexcept {
    gpu_ = gpu;
    return *this;
  }

  /**
   * @brief Builds the Computer
   * @return Built Computer instance
   * @side_effects Creates new Computer
   * @throws None (noexcept)
   */
  virtual Computer build() noexcept {
    return Computer(cpu_, ram_, storage_, gpu_);
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
