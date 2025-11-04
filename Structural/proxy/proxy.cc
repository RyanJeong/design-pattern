// Created: 2025-11-03
// Filename: proxy.cc
// Description: Proxy design pattern demonstration
// Copyright 2025

#include "proxy.hpp"

int main() {
  std::cout << "=== Proxy Pattern: Lazy Image Loading ===" << std::endl;

  ProxyImage image1("photo1.jpg");
  ProxyImage image2("photo2.jpg");
  ProxyImage image3("photo3.jpg");

  std::cout << "\nProxies created (no real images loaded yet)" << std::endl;

  std::cout << "\nCalling display on image1:" << std::endl;
  image1.display();

  std::cout << "\nCalling display on image1 again:" << std::endl;
  image1.display();  // No reload

  std::cout << "\nCalling display on image2:" << std::endl;
  image2.display();

  std::cout << "\nCalling display on image3:" << std::endl;
  image3.display();

  return 0;
}
