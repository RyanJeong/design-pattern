// Created: 2025-11-03
// Filename: chain_of_responsibility.cc
// Description: Chain of Responsibility design pattern demonstration
// Copyright 2025

#include "chain_of_responsibility.hpp"

#include <iostream>

int main() {
  // Create a creature with initial attributes
  Creature goblin("Goblin", 1, 1);

  std::cout << "Initial state: " << goblin.get_name()
            << " (Attack: " << goblin.get_attack()
            << ", Defense: " << goblin.get_defense() << ")" << std::endl;

  // Build the chain: double attack twice, then increase defense
  auto double_attack_1 = std::make_shared<DoubleAttackModifier>(goblin);
  auto double_attack_2 =
      std::make_shared<DoubleAttackModifier>(goblin, double_attack_1);
  auto increase_defense =
      std::make_shared<IncreaseDefenseModifier>(goblin, double_attack_2);

  // Process the chain
  increase_defense->handle();

  std::cout << "After modifiers: " << goblin.get_name()
            << " (Attack: " << goblin.get_attack()
            << ", Defense: " << goblin.get_defense() << ")" << std::endl;

  // Demonstrate blocking chain with NoBonusesModifier
  Creature dragon("Dragon", 2, 2);
  std::cout << "\nInitial state: " << dragon.get_name()
            << " (Attack: " << dragon.get_attack()
            << ", Defense: " << dragon.get_defense() << ")" << std::endl;

  auto no_bonus = std::make_shared<NoBonusesModifier>();
  auto double_attack_blocked =
      std::make_shared<DoubleAttackModifier>(dragon, no_bonus);

  double_attack_blocked->handle();

  std::cout << "After blocked chain: " << dragon.get_name()
            << " (Attack: " << dragon.get_attack()
            << ", Defense: " << dragon.get_defense() << ")" << std::endl;

  return 0;
}
