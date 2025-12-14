// Created: 2025-11-03
// Filename: bridge.hpp
// Description: Bridge design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_BRIDGE_BRIDGE_HPP_
#define STRUCTURAL_BRIDGE_BRIDGE_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Implementer - abstraction for platform-specific implementation
 * @note Defines implementation interface
 * @side_effects None (abstract)
 */
class Renderer {
 public:
  virtual ~Renderer() = default;

  /**
   * @brief Renders a circle
   * @param x X coordinate
   * @param y Y coordinate
   * @param radius Circle radius
   * @side_effects Prints to console for demo feedback
   * @side_effects_reason Demonstration requirement: Bridge pattern separates
   *   abstraction from implementation. Console output shows which renderer
   *   implementation is being used for each shape
   * @side_effects_what Writes to stdout for renderer selection visibility
   * @side_effects_impact Console I/O adds minimal overhead (per render)
   * @side_effects_alternatives Inject logger; adds complexity for demo
   * @throws None (noexcept)
   */
  virtual void RenderCircle(int x, int y, int radius) const noexcept = 0;

  /**
   * @brief Renders a rectangle
   * @param x X coordinate
   * @param y Y coordinate
   * @param width Rectangle width
   * @param height Rectangle height
   * @side_effects Prints to console (see RenderCircle rationale)
   * @throws None (noexcept)
   */
  virtual void RenderRectangle(int x, int y, int width,
                               int height) const noexcept = 0;
};

/**
 * @brief Concrete Implementer - Vector renderer
 * @note Vector rendering implementation
 * @side_effects None (after construction)
 */
class VectorRenderer : public Renderer {
 public:
  void RenderCircle(int x, int y, int radius) const noexcept override {
    std::cout << "Rendering circle in vector: center(" << x << "," << y
              << "), radius=" << radius << std::endl;
  }

  void RenderRectangle(int x, int y, int width,
                       int height) const noexcept override {
    std::cout << "Rendering rectangle in vector: pos(" << x << "," << y
              << "), size=" << width << "x" << height << std::endl;
  }
};

/**
 * @brief Concrete Implementer - Raster renderer
 * @note Raster rendering implementation
 * @side_effects None (after construction)
 */
class RasterRenderer : public Renderer {
 public:
  void RenderCircle(int x, int y, int radius) const noexcept override {
    std::cout << "Rendering circle in raster: center(" << x << "," << y
              << "), radius=" << radius << std::endl;
  }

  void RenderRectangle(int x, int y, int width,
                       int height) const noexcept override {
    std::cout << "Rendering rectangle in raster: pos(" << x << "," << y
              << "), size=" << width << "x" << height << std::endl;
  }
};

/**
 * @brief Abstraction - shape interface
 * @note Defines high-level shape interface
 * @side_effects Stores renderer
 */
class Shape {
 protected:
  std::shared_ptr<Renderer> renderer_;

 public:
  explicit Shape(std::shared_ptr<Renderer> renderer) noexcept
      : renderer_(renderer) {}

  virtual ~Shape() = default;

  /**
   * @brief Draws the shape
   * @side_effects Delegates to renderer
   * @throws None (noexcept)
   */
  virtual void Draw() const noexcept = 0;

  /**
   * @brief Changes renderer
   * @param renderer New renderer
   * @side_effects Updates renderer
   * @throws None (noexcept)
   */
  void SetRenderer(std::shared_ptr<Renderer> renderer) noexcept {
    renderer_ = renderer;
  }
};

/**
 * @brief Concrete Abstraction - circle shape
 * @note Circle implementation using renderer
 * @side_effects None (after construction)
 */
class Circle : public Shape {
 private:
  int x_;
  int y_;
  int radius_;

 public:
  Circle(std::shared_ptr<Renderer> renderer, int x, int y, int radius) noexcept
      : Shape(renderer), x_(x), y_(y), radius_(radius) {}

  void Draw() const noexcept override {
    renderer_->RenderCircle(x_, y_, radius_);
  }
};

/**
 * @brief Concrete Abstraction - rectangle shape
 * @note Rectangle implementation using renderer
 * @side_effects None (after construction)
 */
class Rectangle : public Shape {
 private:
  int x_;
  int y_;
  int width_;
  int height_;

 public:
  Rectangle(std::shared_ptr<Renderer> renderer, int x, int y, int width,
            int height) noexcept
      : Shape(renderer), x_(x), y_(y), width_(width), height_(height) {}

  void Draw() const noexcept override {
    renderer_->RenderRectangle(x_, y_, width_, height_);
  }
};

#endif  // STRUCTURAL_BRIDGE_BRIDGE_HPP_
