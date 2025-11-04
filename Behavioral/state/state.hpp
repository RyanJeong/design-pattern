// Created: 2025-11-03
// Filename: state.hpp
// Description: State design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_STATE_STATE_HPP_
#define BEHAVIORAL_STATE_STATE_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Forward declaration
 */
class LightSwitch;

/**
 * @brief Abstract state interface
 * @note Base class for all states
 * @side_effects None (abstract)
 */
class State {
 public:
  virtual ~State() = default;

  /**
   * @brief Handles on transition
   * @param context Light switch context
   * @side_effects May change state
   * @throws None (noexcept)
   */
  virtual void on(LightSwitch*) noexcept {
    std::cout << "Light is already on\n";
  }

  /**
   * @brief Handles off transition
   * @param context Light switch context
   * @side_effects May change state
   * @throws None (noexcept)
   */
  virtual void off(LightSwitch*) noexcept {
    std::cout << "Light is already off\n";
  }
};

/**
 * @brief Context class - light switch
 * @note Maintains current state
 * @thread_safety Not thread-safe
 */
class LightSwitch {
 private:
  std::shared_ptr<State> state_;

 public:
  LightSwitch() noexcept;

  /**
   * @brief Sets current state
   * @param state New state
   * @side_effects Changes internal state
   * @throws None (noexcept)
   */
  void set_state(std::shared_ptr<State> state) noexcept { state_ = state; }

  /**
   * @brief Turns light on
   * @side_effects May trigger state change
   * @throws None (noexcept)
   */
  void on() noexcept { state_->on(this); }

  /**
   * @brief Turns light off
   * @side_effects May trigger state change
   * @throws None (noexcept)
   */
  void off() noexcept { state_->off(this); }
};

/**
 * @brief On state
 * @note Represents light being on
 * @side_effects May trigger state transitions
 */
class OnState : public State {
 public:
  OnState() noexcept { std::cout << "Light turned on\n"; }

  /**
   * @brief Handles off transition from on state
   * @param context Light switch context
   * @side_effects Transitions to OffState
   * @throws None (noexcept)
   */
  void off(LightSwitch* context) noexcept override;
};

/**
 * @brief Off state
 * @note Represents light being off
 * @side_effects May trigger state transitions
 */
class OffState : public State {
 public:
  OffState() noexcept { std::cout << "Light turned off\n"; }

  /**
   * @brief Handles on transition from off state
   * @param context Light switch context
   * @side_effects Transitions to OnState
   * @throws None (noexcept)
   */
  void on(LightSwitch* context) noexcept override;
};

#endif  // BEHAVIORAL_STATE_STATE_HPP_
