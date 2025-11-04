// Created: 2025-11-03
// Filename: decorator.hpp
// Description: Decorator design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_DECORATOR_DECORATOR_HPP_
#define STRUCTURAL_DECORATOR_DECORATOR_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Component - interface for objects that can have responsibilities added
 * @note Base interface for component and decorators
 * @side_effects None (abstract)
 */
class Component {
 public:
  virtual ~Component() = default;

  /**
   * @brief Gets description
   * @return Component description
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual std::string get_description() const noexcept = 0;

  /**
   * @brief Gets cost
   * @return Component cost
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual double get_cost() const noexcept = 0;
};

/**
 * @brief Concrete Component - base coffee
 * @note Simple concrete component
 * @side_effects None (after construction)
 */
class SimpleCoffee : public Component {
 public:
  std::string get_description() const noexcept override {
    return "Simple Coffee";
  }

  double get_cost() const noexcept override { return 2.0; }
};

/**
 * @brief Decorator - base class for decorators
 * @note Wraps component and adds responsibilities
 * @side_effects Stores wrapped component
 */
class CoffeeDecorator : public Component {
 protected:
  std::unique_ptr<Component> component_;

 public:
  explicit CoffeeDecorator(std::unique_ptr<Component> component) noexcept
      : component_(std::move(component)) {}

  std::string get_description() const noexcept override {
    return component_->get_description();
  }

  double get_cost() const noexcept override { return component_->get_cost(); }
};

/**
 * @brief Concrete Decorator - milk
 * @note Adds milk to coffee
 * @side_effects None (after construction)
 */
class MilkDecorator : public CoffeeDecorator {
 public:
  explicit MilkDecorator(std::unique_ptr<Component> component) noexcept
      : CoffeeDecorator(std::move(component)) {}

  std::string get_description() const noexcept override {
    return component_->get_description() + ", Milk";
  }

  double get_cost() const noexcept override {
    return component_->get_cost() + 0.5;
  }
};

/**
 * @brief Concrete Decorator - sugar
 * @note Adds sugar to coffee
 * @side_effects None (after construction)
 */
class SugarDecorator : public CoffeeDecorator {
 public:
  explicit SugarDecorator(std::unique_ptr<Component> component) noexcept
      : CoffeeDecorator(std::move(component)) {}

  std::string get_description() const noexcept override {
    return component_->get_description() + ", Sugar";
  }

  double get_cost() const noexcept override {
    return component_->get_cost() + 0.25;
  }
};

/**
 * @brief Concrete Decorator - chocolate
 * @note Adds chocolate to coffee
 * @side_effects None (after construction)
 */
class ChocolateDecorator : public CoffeeDecorator {
 public:
  explicit ChocolateDecorator(std::unique_ptr<Component> component) noexcept
      : CoffeeDecorator(std::move(component)) {}

  std::string get_description() const noexcept override {
    return component_->get_description() + ", Chocolate";
  }

  double get_cost() const noexcept override {
    return component_->get_cost() + 0.75;
  }
};

#endif  // STRUCTURAL_DECORATOR_DECORATOR_HPP_
