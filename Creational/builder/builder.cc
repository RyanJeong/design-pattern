// Created: 2025-11-03
// Filename: builder.cc
// Description: Builder design pattern demonstration
// Copyright 2025

#include "builder.hpp"

#include <iostream>

int main() {
  // Build gaming computer
  GamingComputerBuilder gaming_builder;
  Computer gaming_pc = gaming_builder.set_cpu("Intel Core i9-12900K")
                           .set_ram("32GB DDR5")
                           .set_storage("2TB NVMe SSD")
                           .set_gpu("RTX 4090")
                           .Build();

  std::cout << "=== Gaming PC ===" << std::endl;
  gaming_pc.display();

  // Build workstation computer
  std::cout << "\n=== Workstation ===" << std::endl;
  WorkstationBuilder workstation_builder;
  Computer workstation = workstation_builder.Build();
  workstation.display();

  // Build custom computer
  std::cout << "\n=== Custom PC ===" << std::endl;
  ComputerBuilder custom_builder;
  Computer custom_pc = custom_builder.set_cpu("AMD Ryzen 7")
                           .set_ram("16GB DDR4")
                           .set_storage("512GB SSD")
                           .set_gpu("RTX 3060")
                           .Build();
  custom_pc.display();

  return 0;
}
