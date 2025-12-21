// Created: 2025-11-03
// Filename: state.cc
// Description: State design pattern demonstration
// Copyright 2025

#include "state.hpp"  // [LOLINT]

#include <iostream>
#include <memory>

LightSwitch::LightSwitch() noexcept : state_(std::make_shared<OffState>()) {}

std::shared_ptr<State> OnState::Off(LightSwitch*) const noexcept {
  // VIOLATION: Prints to console for demo clarity
  // Rationale: State transitions must be visible to demonstrate pattern
  // Production code should use logging injection instead
  std::cout << "Switching light off...\n";
  return std::make_shared<OffState>();
}

std::shared_ptr<State> OffState::On(LightSwitch*) const noexcept {
  // VIOLATION: Prints to console for demo clarity
  // Rationale: State transitions must be visible to demonstrate pattern
  // Production code should use logging injection instead
  std::cout << "Switching light on...\n";
  return std::make_shared<OnState>();
}

int main() {
  LightSwitch light_switch;

  light_switch.On();   // Switching light on... Light turned on
  light_switch.Off();  // Switching light off... Light turned off
  light_switch.Off();  // Light is already off
  light_switch.On();   // Switching light on... Light turned on
  light_switch.On();   // Light is already on

  return 0;
}
