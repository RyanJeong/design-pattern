// Created: 2025-11-03
// Filename: prototype.hpp
// Description: Prototype design pattern implementation
// Copyright 2025

#ifndef CREATIONAL_PROTOTYPE_PROTOTYPE_HPP_
#define CREATIONAL_PROTOTYPE_PROTOTYPE_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

/**
 * @brief Shape base class with clone capability
 * @note Defines prototype interface
 * @side_effects None (abstract)
 */
class Shape {
 protected:
  std::string name_;

 public:
  // Take name by value to allow callers to move a temporary or existing
  // string into the shape, avoiding an extra allocation/copy.
  explicit Shape(std::string name = "") noexcept : name_(std::move(name)) {}

  virtual ~Shape() = default;

  /**
   * @brief Clones the shape
   * @return Unique pointer to cloned Shape
   * @side_effects Creates new Shape instance
   * @throws None (noexcept)
   */
  virtual std::unique_ptr<Shape> Clone() const noexcept = 0;

  /**
   * @brief Gets shape name
   * @return Shape name
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& name() const noexcept { return name_; }

  /**
   * @brief Sets shape name
   * @param name New name
   * @side_effects Updates name
   * @throws None (noexcept)
   */
  // Accept by value and move into member to enable move semantics.
  void set_name(std::string name) noexcept { name_ = std::move(name); }

  /**
   * @brief Displays shape info
   * @side_effects Prints to console for demo feedback
   * @side_effects_reason Demonstration requirement: Prototype pattern shows
   *   how objects are cloned. Console output displays cloned objects and
   *   verifies successful cloning without requiring test infrastructure
   * @side_effects_what Writes to stdout for clone verification
   * @side_effects_impact Console I/O adds minimal overhead (one-time per
   * display)
   * @side_effects_alternatives Use structured output; hides visibility during
   * demo
   * @throws None (noexcept)
   */
  virtual void Display() const noexcept = 0;
};

/**
 * @brief Circle shape
 * @note Concrete shape with radius
 * @side_effects None (after construction)
 */
class Circle : public Shape {
 private:
  double radius_;

 public:
  // Accept name by-value and move into base class to enable move semantics
  explicit Circle(std::string name = "", double radius = 0.0) noexcept
      : Shape(std::move(name)), radius_(radius) {}

  std::unique_ptr<Shape> Clone() const noexcept override {
    return std::make_unique<Circle>(*this);
  }

  void Display() const noexcept override {
    std::cout << "Circle: " << name_ << " (radius: " << radius_ << ")"
              << std::endl;
  }

  /**
   * @brief Sets circle radius
   * @param radius New radius
   * @side_effects Updates radius
   * @throws None (noexcept)
   */
  void set_radius(double radius) noexcept { radius_ = radius; }

  /**
   * @brief Gets circle radius
   * @return Circle radius
   * @side_effects None
   * @throws None (noexcept)
   */
  double radius() const noexcept { return radius_; }
};

/**
 * @brief Rectangle shape
 * @note Concrete shape with width and height
 * @side_effects None (after construction)
 */
class Rectangle : public Shape {
 private:
  double width_;
  double height_;

 public:
  // Accept name by-value and move into base class to enable move semantics
  explicit Rectangle(std::string name = "", double width = 0.0,
                     double height = 0.0) noexcept
      : Shape(std::move(name)), width_(width), height_(height) {}

  std::unique_ptr<Shape> Clone() const noexcept override {
    return std::make_unique<Rectangle>(*this);
  }

  void Display() const noexcept override {
    std::cout << "Rectangle: " << name_ << " (" << width_ << " x " << height_
              << ")" << std::endl;
  }

  /**
   * @brief Sets rectangle dimensions
   * @param width New width
   * @param height New height
   * @side_effects Updates dimensions
   * @throws None (noexcept)
   */
  void set_dimensions(double width, double height) noexcept {
    width_ = width;
    height_ = height;
  }
};

/**
 * @brief Shape registry/prototype holder
 * @note Stores prototypes for cloning
 * @side_effects Manages shape prototypes
 */
class ShapeRegistry {
 private:
  std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes_;

 public:
  /**
   * @brief Registers a shape prototype
   * @param key Prototype key
   * @param shape Shape to register
   * @side_effects Stores prototype
   * @throws None (noexcept)
   */
  // Accept key by-value and emplace using move to avoid an extra copy of
  // the key string when inserting into the map.
  void RegisterPrototype(std::string key,
                         std::unique_ptr<Shape> shape) noexcept {
    prototypes_.emplace(std::move(key), std::move(shape));
  }

  /**
   * @brief Creates a clone of registered prototype
   * @param key Prototype key
   * @return Cloned shape
   * @side_effects Creates new Shape
   * @throws std::out_of_range if key not found
   */
  std::unique_ptr<Shape> CreateShape(const std::string& key) const {
    return prototypes_.at(key)->Clone();
  }
};

#endif  // CREATIONAL_PROTOTYPE_PROTOTYPE_HPP_
