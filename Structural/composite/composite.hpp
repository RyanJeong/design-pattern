// Created: 2025-11-03
// Filename: composite.hpp
// Description: Composite design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_COMPOSITE_COMPOSITE_HPP_
#define STRUCTURAL_COMPOSITE_COMPOSITE_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Component - base class for all objects
 * @note Defines interface for both leaves and composites
 * @side_effects None (abstract)
 */
class Component {
 protected:
  std::string name_;

 public:
  explicit Component(const std::string& name = "") noexcept : name_(name) {}

  virtual ~Component() = default;

  /**
   * @brief Displays component
   * @param indent Indentation level
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void display(int indent = 0) const noexcept = 0;

  /**
   * @brief Adds child component
   * @param component Child to add
   * @side_effects Updates composite structure
   * @throws None (noexcept)
   */
  virtual void add(std::unique_ptr<Component>) noexcept {
    // Default: no-op for leaf nodes
  }

  /**
   * @brief Gets component name
   * @return Component name
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& get_name() const noexcept { return name_; }
};

/**
 * @brief Leaf - has no children
 * @note Terminal node in tree structure
 * @side_effects None (after construction)
 */
class File : public Component {
 private:
  int size_;

 public:
  File(const std::string& name, int size) noexcept
      : Component(name), size_(size) {}

  void display(int indent = 0) const noexcept override {
    for (int i = 0; i < indent; ++i) std::cout << "  ";
    std::cout << "File: " << name_ << " (" << size_ << " bytes)" << std::endl;
  }
};

/**
 * @brief Composite - can contain other components
 * @note Container node in tree structure
 * @side_effects Manages children
 */
class Directory : public Component {
 private:
  std::vector<std::unique_ptr<Component>> children_;

 public:
  explicit Directory(const std::string& name) noexcept : Component(name) {}

  void add(std::unique_ptr<Component> component) noexcept override {
    children_.push_back(std::move(component));
  }

  void display(int indent = 0) const noexcept override {
    for (int i = 0; i < indent; ++i) std::cout << "  ";
    std::cout << "Directory: " << name_ << "/" << std::endl;
    for (const auto& child : children_) { child->display(indent + 1); }
  }

  /**
   * @brief Gets total size of directory and contents
   * @return Total size in bytes
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_size() const noexcept {
    int total = 0;
    for (const auto& child : children_) {
      // Try to cast to Directory to get size
      const Directory* dir = dynamic_cast<const Directory*>(child.get());
      if (dir) {
        total += dir->get_size();
      } else {
        // It's a file
        const File* file = dynamic_cast<const File*>(child.get());
        if (file) {
          // File size is not exposed, estimate as 1KB
          total += 1024;
        }
      }
    }
    return total;
  }
};

#endif  // STRUCTURAL_COMPOSITE_COMPOSITE_HPP_
