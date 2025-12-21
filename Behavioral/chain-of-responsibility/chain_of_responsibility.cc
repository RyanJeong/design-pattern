// Created: 2025-11-03
// Filename: chain_of_responsibility.cc
// Description: Chain of Responsibility design pattern demonstration
// Copyright 2025

#include "chain_of_responsibility.hpp"

#include <iostream>

int main() {
  // Create a creature with initial attributes
  Creature goblin("Goblin", 1, 1);

  std::cout << "Initial state: " << goblin.GetName()
            << " (Attack: " << goblin.GetAttack()
            << ", Defense: " << goblin.GetDefense() << ")" << std::endl;

  // Build the chain: double attack twice, then increase defense
  auto double_attack_1 = std::make_shared<DoubleAttackModifier>();
  auto double_attack_2 =
      std::make_shared<DoubleAttackModifier>(double_attack_1);
  auto increase_defense =
      std::make_shared<IncreaseDefenseModifier>(double_attack_2);

  // Process the chain - returns modified creature
  Creature modified_goblin = increase_defense->Handle(goblin);

  std::cout << "After modifiers: " << modified_goblin.GetName()
            << " (Attack: " << modified_goblin.GetAttack()
            << ", Defense: " << modified_goblin.GetDefense() << ")"
            << std::endl;

  // Demonstrate blocking chain with NoBonusesModifier
  Creature dragon("Dragon", 2, 2);
  std::cout << "\nInitial state: " << dragon.GetName()
            << " (Attack: " << dragon.GetAttack()
            << ", Defense: " << dragon.GetDefense() << ")" << std::endl;

  auto no_bonus = std::make_shared<NoBonusesModifier>();
  auto double_attack_blocked = std::make_shared<DoubleAttackModifier>(no_bonus);

  Creature blocked_dragon = double_attack_blocked->Handle(dragon);

  std::cout << "After blocked chain: " << blocked_dragon.GetName()
            << " (Attack: " << blocked_dragon.GetAttack()
            << ", Defense: " << blocked_dragon.GetDefense() << ")" << std::endl;

  return 0;
}
