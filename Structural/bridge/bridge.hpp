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
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void render_circle(int x, int y, int radius) const noexcept = 0;

  /**
   * @brief Renders a rectangle
   * @param x X coordinate
   * @param y Y coordinate
   * @param width Rectangle width
   * @param height Rectangle height
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void render_rectangle(int x, int y, int width,
                                int height) const noexcept = 0;
};

/**
 * @brief Concrete Implementer - Vector renderer
 * @note Vector rendering implementation
 * @side_effects None (after construction)
 */
class VectorRenderer : public Renderer {
 public:
  void render_circle(int x, int y, int radius) const noexcept override {
    std::cout << "Rendering circle in vector: center(" << x << "," << y
              << "), radius=" << radius << std::endl;
  }

  void render_rectangle(int x, int y, int width,
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
  void render_circle(int x, int y, int radius) const noexcept override {
    std::cout << "Rendering circle in raster: center(" << x << "," << y
              << "), radius=" << radius << std::endl;
  }

  void render_rectangle(int x, int y, int width,
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
  virtual void draw() const noexcept = 0;

  /**
   * @brief Changes renderer
   * @param renderer New renderer
   * @side_effects Updates renderer
   * @throws None (noexcept)
   */
  void set_renderer(std::shared_ptr<Renderer> renderer) noexcept {
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

  void draw() const noexcept override {
    renderer_->render_circle(x_, y_, radius_);
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

  void draw() const noexcept override {
    renderer_->render_rectangle(x_, y_, width_, height_);
  }
};

#endif  // STRUCTURAL_BRIDGE_BRIDGE_HPP_
