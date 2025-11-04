// Created: 2025-11-03
// Filename: chain_of_responsibility.hpp
// Description: Chain of Responsibility design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_HPP_
#define BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Abstract handler in the chain
 * @note Base class for all handlers in the chain
 * @side_effects None
 */
class Modifier {
 protected:
  std::shared_ptr<Modifier> next_;

 public:
  explicit Modifier(std::shared_ptr<Modifier> next = nullptr) : next_(next) {}

  virtual ~Modifier() = default;

  /**
   * @brief Processes the request and passes to next handler
   * @side_effects May modify the creature's attributes
   * @throws None (noexcept)
   */
  virtual void handle() noexcept = 0;
};

/**
 * @brief Represents a creature with attributes
 * @note Mutable for demonstration purposes
 * @thread_safety Not thread-safe
 */
class Creature {
 private:
  std::string name_;
  int attack_;
  int defense_;

 public:
  explicit Creature(const std::string& name, int attack, int defense) noexcept
      : name_(name), attack_(attack), defense_(defense) {}

  /**
   * @brief Gets creature name
   * @return Creature name
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& get_name() const noexcept { return name_; }

  /**
   * @brief Gets creature attack value
   * @return Attack value
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_attack() const noexcept { return attack_; }

  /**
   * @brief Sets creature attack value
   * @param attack New attack value
   * @side_effects Modifies internal attack value
   * @throws None (noexcept)
   */
  void set_attack(int attack) noexcept { attack_ = attack; }

  /**
   * @brief Gets creature defense value
   * @return Defense value
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_defense() const noexcept { return defense_; }

  /**
   * @brief Sets creature defense value
   * @param defense New defense value
   * @side_effects Modifies internal defense value
   * @throws None (noexcept)
   */
  void set_defense(int defense) noexcept { defense_ = defense; }
};

/**
 * @brief Modifier that doubles attack
 * @note Processes creature and passes to next handler
 * @side_effects Modifies creature's attack attribute
 */
class DoubleAttackModifier : public Modifier {
 private:
  Creature& creature_;

 public:
  explicit DoubleAttackModifier(Creature& creature,
                                std::shared_ptr<Modifier> next = nullptr)
      : Modifier(next), creature_(creature) {}

  /**
   * @brief Doubles attack and passes to next handler
   * @side_effects Doubles creature's attack value
   * @throws None (noexcept)
   */
  void handle() noexcept override {
    creature_.set_attack(creature_.get_attack() * 2);
    if (next_) { next_->handle(); }
  }
};

/**
 * @brief Modifier that increases defense based on attack
 * @note Only increases if attack <= 2
 * @side_effects May modify creature's defense attribute
 */
class IncreaseDefenseModifier : public Modifier {
 private:
  Creature& creature_;

 public:
  explicit IncreaseDefenseModifier(Creature& creature,
                                   std::shared_ptr<Modifier> next = nullptr)
      : Modifier(next), creature_(creature) {}

  /**
   * @brief Increases defense and passes to next handler
   * @side_effects May increase creature's defense value
   * @throws None (noexcept)
   */
  void handle() noexcept override {
    if (creature_.get_attack() <= 2) {
      creature_.set_defense(creature_.get_defense() + 1);
    }
    if (next_) { next_->handle(); }
  }
};

/**
 * @brief Modifier that prevents other modifications
 * @note Blocks the entire chain
 * @side_effects Terminates the chain processing
 */
class NoBonusesModifier : public Modifier {
 public:
  explicit NoBonusesModifier(std::shared_ptr<Modifier> next = nullptr)
      : Modifier(next) {}

  /**
   * @brief Terminates chain processing
   * @side_effects Prevents further processing
   * @throws None (noexcept)
   */
  void handle() noexcept override {
    // Do nothing - terminates the chain
  }
};

#endif  // BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_HPP_
