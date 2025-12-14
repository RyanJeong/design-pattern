// Created: 2025-11-03
// Filename: decorator.hpp
// Description: Decorator design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_DECORATOR_DECORATOR_HPP_
#define STRUCTURAL_DECORATOR_DECORATOR_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <utility>

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
  virtual std::string GetDescription() const noexcept = 0;

  /**
   * @brief Gets cost
   * @return Component cost
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual double GetCost() const noexcept = 0;
};

/**
 * @brief Concrete Component - base coffee
 * @note Simple concrete component
 * @side_effects None (after construction)
 */
class SimpleCoffee : public Component {
 public:
  std::string GetDescription() const noexcept override {
    return "Simple Coffee";
  }

  double GetCost() const noexcept override { return 2.0; }
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

  std::string GetDescription() const noexcept override {
    return component_->GetDescription();
  }

  double GetCost() const noexcept override { return component_->GetCost(); }
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

  std::string GetDescription() const noexcept override {
    return component_->GetDescription() + ", Milk";
  }

  double GetCost() const noexcept override {
    return component_->GetCost() + 0.5;
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

  std::string GetDescription() const noexcept override {
    return component_->GetDescription() + ", Sugar";
  }

  double GetCost() const noexcept override {
    return component_->GetCost() + 0.25;
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

  std::string GetDescription() const noexcept override {
    return component_->GetDescription() + ", Chocolate";
  }

  double GetCost() const noexcept override {
    return component_->GetCost() + 0.75;
  }
};

#endif  // STRUCTURAL_DECORATOR_DECORATOR_HPP_
