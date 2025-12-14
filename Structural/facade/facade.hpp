// Created: 2025-11-03
// Filename: facade.hpp
// Description: Facade design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_FACADE_FACADE_HPP_
#define STRUCTURAL_FACADE_FACADE_HPP_

#include <iostream>
#include <string>

/**
 * @brief Subsystem 1 - CPU
 * @note Complex subsystem component
 * @side_effects None (after construction)
 */
class CPU {
 public:
  /**
   * @brief Freezes CPU
   * @side_effects Prints to console for demo feedback
   * @side_effects_reason Demonstration requirement: Facade simplifies complex
   *   subsystem interactions. Console output shows internal operations
   *   coordinated by the facade
   * @side_effects_what Writes to stdout for operation visibility
   * @side_effects_impact Console I/O adds minimal overhead (per operation)
   * @side_effects_alternatives Inject logger; adds complexity for demo
   * @throws None (noexcept)
   */
  void Freeze() const noexcept { std::cout << "Freezing CPU..." << std::endl; }

  /**
   * @brief Jumps to location
   * @param location Memory location
   * @side_effects Prints to console (see Freeze rationale)
   * @throws None (noexcept)
   */
  void Jump(int location) const noexcept {
    std::cout << "Jumping to location: " << location << std::endl;
  }

  /**
   * @brief Executes from location
   * @param location Memory location
   * @side_effects Prints to console (see Freeze rationale)
   * @throws None (noexcept)
   */
  void Execute(int location) const noexcept {
    std::cout << "Executing from location: " << location << std::endl;
  }
};

/**
 * @brief Subsystem 2 - Memory
 * @note Complex subsystem component
 * @side_effects None (after construction)
 */
class Memory {
 public:
  /**
   * @brief Loads program
   * @param data Program data
   * @side_effects Prints to console (see CPU::Freeze rationale)
   * @throws None (noexcept)
   */
  void Load(const std::string& data) const noexcept {
    std::cout << "Loading program: " << data << std::endl;
  }
};

/**
 * @brief Subsystem 3 - Hard Drive
 * @note Complex subsystem component
 * @side_effects None (after construction)
 */
class HardDrive {
 public:
  /**
   * @brief Reads file
   * @param file Filename
   * @return File content
   * @side_effects Prints to console (see CPU::Freeze rationale)
   * @throws None (noexcept)
   */
  std::string Read(const std::string& file) const noexcept {
    std::cout << "Reading file: " << file << std::endl;
    return "Program code from " + file;
  }
};

/**
 * @brief Facade - provides simplified interface
 * @note Simplifies complex subsystem interaction
 * @side_effects Coordinates subsystem operations
 */
class ComputerFacade {
 private:
  CPU cpu_;
  Memory memory_;
  HardDrive hard_drive_;

 public:
  /**
   * @brief Starts the computer
   * @side_effects Coordinates CPU, Memory, HardDrive
   * @throws None (noexcept)
   */
  void Start() const noexcept {
    std::cout << "Computer starting..." << std::endl;
    hard_drive_.Read("boot.bin");
    auto data = hard_drive_.Read("os.bin");
    memory_.Load(data);
    cpu_.Freeze();
    cpu_.Jump(0);
    cpu_.Execute(0);
    std::cout << "Computer ready." << std::endl;
  }

  /**
   * @brief Shuts down the computer
   * @side_effects Coordinates shutdown
   * @throws None (noexcept)
   */
  void Shutdown() const noexcept {
    std::cout << "Computer shutting down..." << std::endl;
    cpu_.Freeze();
    std::cout << "Computer off." << std::endl;
  }
};

#endif  // STRUCTURAL_FACADE_FACADE_HPP_
