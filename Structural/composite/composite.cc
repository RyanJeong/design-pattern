// Created: 2025-11-03
// Filename: composite.cc
// Description: Composite design pattern demonstration
// Copyright 2025

#include "composite.hpp"  // [NOLINT]

#include <iostream>
#include <memory>
#include <utility>

int main() {
  std::cout << "=== File System Hierarchy ===" << std::endl;

  auto root = std::make_unique<Directory>("root");

  auto home = std::make_unique<Directory>("home");
  home->Add(std::make_unique<File>("document.txt", 2048));
  home->Add(std::make_unique<File>("image.jpg", 4096));

  auto documents = std::make_unique<Directory>("Documents");
  documents->Add(std::make_unique<File>("resume.pdf", 3072));
  documents->Add(std::make_unique<File>("letter.docx", 1536));

  home->Add(std::move(documents));

  root->Add(std::move(home));

  auto usr = std::make_unique<Directory>("usr");
  auto bin = std::make_unique<Directory>("bin");
  bin->Add(std::make_unique<File>("gcc", 8192));
  bin->Add(std::make_unique<File>("make", 4096));
  usr->Add(std::move(bin));

  root->Add(std::move(usr));

  root->Display();

  return 0;
}
