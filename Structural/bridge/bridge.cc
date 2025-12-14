// Created: 2025-11-03
// Filename: bridge.cc
// Description: Bridge design pattern demonstration
// Copyright 2025

#include "bridge.hpp"  // [NOLINT]

#include <iostream>
#include <memory>

int main() {
  std::cout << "=== Vector Renderer ===" << std::endl;
  auto vector_renderer = std::make_shared<VectorRenderer>();
  Circle circle1(vector_renderer, 10, 20, 5);
  circle1.Draw();

  Rectangle rect1(vector_renderer, 0, 0, 100, 50);
  rect1.Draw();

  std::cout << "\n=== Raster Renderer ===" << std::endl;
  auto raster_renderer = std::make_shared<RasterRenderer>();
  Circle circle2(raster_renderer, 30, 40, 8);
  circle2.Draw();

  Rectangle rect2(raster_renderer, 10, 10, 200, 150);
  rect2.Draw();

  std::cout << "\n=== Runtime Renderer Switch ===" << std::endl;
  Circle circle3(vector_renderer, 50, 60, 3);
  circle3.Draw();
  circle3.SetRenderer(raster_renderer);
  circle3.Draw();

  return 0;
}
