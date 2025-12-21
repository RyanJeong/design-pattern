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
   * @return New state after transition
   * @side_effects Prints status message for demo clarity
   * @side_effects_reason Demonstration requirement: State pattern is often
   *   implemented for stateful systems where user feedback (via logging or
   *   UI updates) is necessary. Console output here is unavoidable for demo.
   * @side_effects_what Writes to stdout for demo feedback
   * @side_effects_impact Console I/O adds latency only in demo context
   * @side_effects_alternatives Pure function impossible without losing demo
   * clarity
   * @throws None (noexcept)
   */
  virtual std::shared_ptr<State> On(LightSwitch*) const noexcept {
    std::cout << "Light is already on\n";
    return nullptr;  // No state change
  }

  /**
   * @brief Handles off transition
   * @param context Light switch context
   * @return New state after transition
   * @side_effects Prints status message for demo clarity
   * @side_effects_reason Demonstration requirement: State pattern is often
   *   implemented for stateful systems where user feedback (via logging or
   *   UI updates) is necessary. Console output here is unavoidable for demo.
   * @side_effects_what Writes to stdout for demo feedback
   * @side_effects_impact Console I/O adds latency only in demo context
   * @side_effects_alternatives Pure function impossible without losing demo
   * clarity
   * @throws None (noexcept)
   */
  virtual std::shared_ptr<State> Off(LightSwitch*) const noexcept {
    std::cout << "Light is already off\n";
    return nullptr;  // No state change
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
   * @return Reference to this switch
   * @side_effects Changes internal state
   * @throws None (noexcept)
   */
  LightSwitch& SetState(std::shared_ptr<State> state) noexcept {
    state_ = state;
    return *this;
  }

  /**
   * @brief Turns light on
   * @return Result of state transition
   * @side_effects May trigger state change
   * @throws None (noexcept)
   */
  std::shared_ptr<State> On() noexcept {
    auto new_state = state_->On(this);
    if (new_state) state_ = new_state;
    return state_;
  }

  /**
   * @brief Turns light off
   * @return Result of state transition
   * @side_effects May trigger state change
   * @throws None (noexcept)
   */
  std::shared_ptr<State> Off() noexcept {
    auto new_state = state_->Off(this);
    if (new_state) state_ = new_state;
    return state_;
  }
};

/**
 * @brief On state
 * @note Represents light being on
 * @side_effects None (immutable)
 */
class OnState : public State {
 public:
  /**
   * @brief Constructs on state with demo feedback
   * @side_effects Prints state change message for demo clarity
   * @side_effects_reason Demonstration requirement: Makes state transitions
   *   visible during demo execution without requiring external logging setup
   * @side_effects_what Writes to stdout for demo visibility
   * @side_effects_impact Console I/O adds minimal latency (one-time at
   * construction)
   * @side_effects_alternatives Could inject logger; adds complexity for demo
   * use case
   * @throws None (noexcept)
   */
  OnState() noexcept { std::cout << "Light turned on\n"; }

  /**
   * @brief Handles off transition from on state
   * @param context Light switch context
   * @return New OffState
   * @side_effects Prints transition message for demo clarity (see constructor
   * rationale)
   * @throws None (noexcept)
   */
  std::shared_ptr<State> Off(LightSwitch*) const noexcept override;
};

/**
 * @brief Off state
 * @note Represents light being off
 * @side_effects None (immutable)
 */
class OffState : public State {
 public:
  /**
   * @brief Constructs off state with demo feedback
   * @side_effects Prints state change message for demo clarity
   * @side_effects_reason Demonstration requirement: Makes state transitions
   *   visible during demo execution without requiring external logging setup
   * @side_effects_what Writes to stdout for demo visibility
   * @side_effects_impact Console I/O adds minimal latency (one-time at
   * construction)
   * @side_effects_alternatives Could inject logger; adds complexity for demo
   * use case
   * @throws None (noexcept)
   */
  OffState() noexcept { std::cout << "Light turned off\n"; }

  /**
   * @brief Handles on transition from off state
   * @param context Light switch context
   * @return New OnState
   * @side_effects Prints transition message for demo clarity (see constructor
   * rationale)
   * @throws None (noexcept)
   */
  std::shared_ptr<State> On(LightSwitch*) const noexcept override;
};

#endif  // BEHAVIORAL_STATE_STATE_HPP_
