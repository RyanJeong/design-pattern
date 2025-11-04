// Created: 2025-11-03
// Filename: composite.cc
// Description: Composite design pattern demonstration
// Copyright 2025

#include "composite.hpp"

int main() {
  std::cout << "=== File System Hierarchy ===" << std::endl;

  auto root = std::make_unique<Directory>("root");

  auto home = std::make_unique<Directory>("home");
  home->add(std::make_unique<File>("document.txt", 2048));
  home->add(std::make_unique<File>("image.jpg", 4096));

  auto documents = std::make_unique<Directory>("Documents");
  documents->add(std::make_unique<File>("resume.pdf", 3072));
  documents->add(std::make_unique<File>("letter.docx", 1536));

  home->add(std::move(documents));

  root->add(std::move(home));

  auto usr = std::make_unique<Directory>("usr");
  auto bin = std::make_unique<Directory>("bin");
  bin->add(std::make_unique<File>("gcc", 8192));
  bin->add(std::make_unique<File>("make", 4096));
  usr->add(std::move(bin));

  root->add(std::move(usr));

  root->display();

  return 0;
}
