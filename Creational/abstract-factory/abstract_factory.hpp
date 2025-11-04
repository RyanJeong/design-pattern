// Created: 2025-11-03
// Filename: abstract_factory.hpp
// Description: Abstract Factory design pattern implementation
// Copyright 2025

#ifndef CREATIONAL_ABSTRACT_FACTORY_ABSTRACT_FACTORY_HPP_
#define CREATIONAL_ABSTRACT_FACTORY_ABSTRACT_FACTORY_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Abstract Product A - button interface
 * @note Defines interface for buttons
 * @side_effects None (abstract)
 */
class Button {
 public:
  virtual ~Button() = default;

  /**
   * @brief Renders button
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void render() const noexcept = 0;
};

/**
 * @brief Concrete Product A - Windows button
 * @note Windows-specific button implementation
 * @side_effects None (after construction)
 */
class WindowsButton : public Button {
 public:
  void render() const noexcept override {
    std::cout << "Rendering Windows button..." << std::endl;
  }
};

/**
 * @brief Concrete Product A - macOS button
 * @note macOS-specific button implementation
 * @side_effects None (after construction)
 */
class MacButton : public Button {
 public:
  void render() const noexcept override {
    std::cout << "Rendering macOS button..." << std::endl;
  }
};

/**
 * @brief Abstract Product B - checkbox interface
 * @note Defines interface for checkboxes
 * @side_effects None (abstract)
 */
class Checkbox {
 public:
  virtual ~Checkbox() = default;

  /**
   * @brief Renders checkbox
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void render() const noexcept = 0;
};

/**
 * @brief Concrete Product B - Windows checkbox
 * @note Windows-specific checkbox implementation
 * @side_effects None (after construction)
 */
class WindowsCheckbox : public Checkbox {
 public:
  void render() const noexcept override {
    std::cout << "Rendering Windows checkbox..." << std::endl;
  }
};

/**
 * @brief Concrete Product B - macOS checkbox
 * @note macOS-specific checkbox implementation
 * @side_effects None (after construction)
 */
class MacCheckbox : public Checkbox {
 public:
  void render() const noexcept override {
    std::cout << "Rendering macOS checkbox..." << std::endl;
  }
};

/**
 * @brief Abstract Factory - creates UI components
 * @note Base class for concrete factories
 * @side_effects None (abstract)
 */
class UIFactory {
 public:
  virtual ~UIFactory() = default;

  /**
   * @brief Creates button
   * @return Unique pointer to created Button
   * @side_effects Creates new Button
   * @throws None (noexcept)
   */
  virtual std::unique_ptr<Button> create_button() const noexcept = 0;

  /**
   * @brief Creates checkbox
   * @return Unique pointer to created Checkbox
   * @side_effects Creates new Checkbox
   * @throws None (noexcept)
   */
  virtual std::unique_ptr<Checkbox> create_checkbox() const noexcept = 0;
};

/**
 * @brief Concrete Factory - creates Windows UI components
 * @note Factory for Windows-specific components
 * @side_effects None (after construction)
 */
class WindowsFactory : public UIFactory {
 public:
  std::unique_ptr<Button> create_button() const noexcept override {
    return std::make_unique<WindowsButton>();
  }

  std::unique_ptr<Checkbox> create_checkbox() const noexcept override {
    return std::make_unique<WindowsCheckbox>();
  }
};

/**
 * @brief Concrete Factory - creates macOS UI components
 * @note Factory for macOS-specific components
 * @side_effects None (after construction)
 */
class MacFactory : public UIFactory {
 public:
  std::unique_ptr<Button> create_button() const noexcept override {
    return std::make_unique<MacButton>();
  }

  std::unique_ptr<Checkbox> create_checkbox() const noexcept override {
    return std::make_unique<MacCheckbox>();
  }
};

/**
 * @brief Application using UI factory
 * @note Works with any UI factory implementation
 * @side_effects Stores factory reference
 */
class Application {
 private:
  std::unique_ptr<Button> button_;
  std::unique_ptr<Checkbox> checkbox_;

 public:
  explicit Application(const UIFactory& factory) noexcept
      : button_(factory.create_button()),
        checkbox_(factory.create_checkbox()) {}

  /**
   * @brief Renders all UI components
   * @side_effects Renders button and checkbox
   * @throws None (noexcept)
   */
  void render() const noexcept {
    button_->render();
    checkbox_->render();
  }
};

#endif  // CREATIONAL_ABSTRACT_FACTORY_ABSTRACT_FACTORY_HPP_
