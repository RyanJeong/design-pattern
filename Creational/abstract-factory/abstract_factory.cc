// Created: 2025-11-03
// Filename: abstract_factory.cc
// Description: Abstract Factory design pattern demonstration
// Copyright 2025

#include "abstract_factory.hpp"  // [NOLINT]

#include <iostream>

int main() {
  std::cout << "=== Windows UI ===" << std::endl;
  WindowsFactory windows_factory;
  Application windows_app(windows_factory);
  windows_app.Render();

  std::cout << "\n=== macOS UI ===" << std::endl;
  MacFactory mac_factory;
  Application mac_app(mac_factory);
  mac_app.Render();

  return 0;
}
