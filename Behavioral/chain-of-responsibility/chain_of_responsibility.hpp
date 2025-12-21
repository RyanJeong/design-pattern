// Created: 2025-11-03
// Filename: chain_of_responsibility.hpp
// Description: Chain of Responsibility design pattern demonstration
// Copyright 2025

#ifndef BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_HPP_
#define BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_HPP_

#include <iostream>
#include <memory>
#include <string>

// Forward declaration - Creature is defined later
class Creature;

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
   * @brief Processes the request and returns modified creature
   * @param creature Creature to process
   * @return Modified creature after processing chain
   * @side_effects None (returns new state)
   * @throws None (noexcept)
   */
  virtual Creature Handle(Creature creature) const noexcept = 0;
};

/**
 * @brief Represents a creature with attributes
 * @note Immutable value object
 * @thread_safety Thread-safe (const object)
 */
class Creature {
 private:
  std::string name_;
  int attack_;
  int defense_;

 public:
  // Accept name by value to enable move semantics when callers pass
  // temporaries or std::move'd strings.
  explicit Creature(std::string name, int attack, int defense) noexcept
      : name_(std::move(name)), attack_(attack), defense_(defense) {}

  /**
   * @brief Gets creature name
   * @return Creature name
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& GetName() const noexcept { return name_; }

  /**
   * @brief Gets creature attack value
   * @return Attack value
   * @side_effects None
   * @throws None (noexcept)
   */
  int GetAttack() const noexcept { return attack_; }

  /**
   * @brief Returns creature with modified attack value
   * @param attack New attack value
   * @return New creature with updated attack
   * @side_effects None (returns new object)
   * @throws None (noexcept)
   */
  Creature WithAttack(int attack) const noexcept {
    return Creature(name_, attack, defense_);
  }

  /**
   * @brief Gets creature defense value
   * @return Defense value
   * @side_effects None
   * @throws None (noexcept)
   */
  int GetDefense() const noexcept { return defense_; }

  /**
   * @brief Returns creature with modified defense value
   * @param defense New defense value
   * @return New creature with updated defense
   * @side_effects None (returns new object)
   * @throws None (noexcept)
   */
  Creature WithDefense(int defense) const noexcept {
    return Creature(name_, attack_, defense);
  }
};

/**
 * @brief Modifier that doubles attack
 * @note Processes creature and passes to next handler
 * @side_effects None (returns modified creature)
 */
class DoubleAttackModifier : public Modifier {
 public:
  explicit DoubleAttackModifier(std::shared_ptr<Modifier> next = nullptr)
      : Modifier(next) {}

  /**
   * @brief Doubles attack and passes to next handler
   * @param creature Creature to process
   * @return Creature with doubled attack
   * @side_effects None (returns new object)
   * @throws None (noexcept)
   */
  Creature Handle(Creature creature) const noexcept override {
    Creature modified = creature.WithAttack(creature.GetAttack() * 2);
    if (next_) { return next_->Handle(modified); }
    return modified;
  }
};

/**
 * @brief Modifier that increases defense based on attack
 * @note Only increases if attack <= 2
 * @side_effects None (returns modified creature)
 */
class IncreaseDefenseModifier : public Modifier {
 public:
  explicit IncreaseDefenseModifier(std::shared_ptr<Modifier> next = nullptr)
      : Modifier(next) {}

  /**
   * @brief Increases defense and passes to next handler
   * @param creature Creature to process
   * @return Creature with possibly increased defense
   * @side_effects None (returns new object)
   * @throws None (noexcept)
   */
  Creature Handle(Creature creature) const noexcept override {
    Creature modified = creature;
    if (creature.GetAttack() <= 2) {
      modified = creature.WithDefense(creature.GetDefense() + 1);
    }
    if (next_) { return next_->Handle(modified); }
    return modified;
  }
};

/**
 * @brief Modifier that prevents other modifications
 * @note Blocks the entire chain
 * @side_effects None (returns creature unchanged)
 */
class NoBonusesModifier : public Modifier {
 public:
  explicit NoBonusesModifier(std::shared_ptr<Modifier> next = nullptr)
      : Modifier(next) {}

  /**
   * @brief Terminates chain processing
   * @param creature Creature to process
   * @return Unmodified creature
   * @side_effects None (blocks chain, returns unchanged)
   * @throws None (noexcept)
   */
  Creature Handle(Creature creature) const noexcept override {
    // Do not process further - terminates the chain
    return creature;
  }
};

#endif  // BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_HPP_
