// Created: 2025-11-03
// Filename: factory_method.cc
// Description: Factory Method design pattern demonstration
// Copyright 2025

#include "factory_method.hpp"

int main() {
  std::cout << "=== PDF Application ===" << std::endl;
  PdfApplication pdf_app;
  pdf_app.new_document();

  std::cout << "\n=== Word Application ===" << std::endl;
  WordApplication word_app;
  word_app.new_document();

  std::cout << "\n=== Text Application ===" << std::endl;
  TextApplication text_app;
  text_app.new_document();

  return 0;
}
