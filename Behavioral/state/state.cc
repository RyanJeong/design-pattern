// Created: 2025-11-03
// Filename: state.cc
// Description: State design pattern demonstration
// Copyright 2025

#include "state.hpp"

LightSwitch::LightSwitch() noexcept : state_(std::make_shared<OffState>()) {}

void OnState::off(LightSwitch* context) noexcept {
  std::cout << "Switching light off...\n";
  context->set_state(std::make_shared<OffState>());
}

void OffState::on(LightSwitch* context) noexcept {
  std::cout << "Switching light on...\n";
  context->set_state(std::make_shared<OnState>());
}

int main() {
  LightSwitch light_switch;

  light_switch.on();   // Switching light on... Light turned on
  light_switch.off();  // Switching light off... Light turned off
  light_switch.off();  // Light is already off
  light_switch.on();   // Switching light on... Light turned on
  light_switch.on();   // Light is already on

  return 0;
}
