// Created: 2025-11-03
// Filename: flyweight.hpp
// Description: Flyweight design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_FLYWEIGHT_FLYWEIGHT_HPP_
#define STRUCTURAL_FLYWEIGHT_FLYWEIGHT_HPP_

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

/**
 * @brief Flyweight - shared object with intrinsic state
 * @note Stores common state shared across many objects
 * @side_effects None (after construction)
 */
class CharacterFont {
 private:
  std::string font_;
  int size_;

 public:
  // Accept font by-value and move into member to enable move semantics so
  // callers can pass temporaries or std::move'd strings without extra copies.
  CharacterFont(std::string font, int size) noexcept
      : font_(std::move(font)), size_(size) {}

  /**
   * @brief Displays character with font
   * @param character Character to display
   * @param x X coordinate
   * @param y Y coordinate
   * @side_effects Prints to console for demo feedback
   * @side_effects_reason Demonstration requirement: Flyweight pattern reuses
   *   objects to minimize memory. Console output shows which shared objects
   *   are being used across many instances
   * @side_effects_what Writes to stdout for character display
   * @side_effects_impact Console I/O adds minimal overhead (per character)
   * @side_effects_alternatives Buffer output; hides reuse visibility
   * @throws None (noexcept)
   */
  void Display(char character, int x, int y) const noexcept {
    std::cout << "Char '" << character << "' at (" << x << "," << y
              << ") - Font: " << font_ << ", Size: " << size_ << std::endl;
  }
};

/**
 * @brief Flyweight Factory - creates and caches flyweights
 * @note Manages shared flyweight instances
 * @side_effects Stores created flyweights
 */
class CharacterFontFactory {
 private:
  std::map<std::string, std::shared_ptr<CharacterFont>> fonts_;

 public:
  /**
   * @brief Gets or creates font
   * @param font Font name
   * @param size Font size
   * @return Shared font instance
   * @side_effects Creates new font if not exists, prints creation/reuse info
   * @side_effects_reason Demonstration requirement: Flyweight pattern caches
   *   and reuses objects. Console output shows cache hits/misses to
   *   demonstrate the optimization benefit
   * @side_effects_what Writes to stdout for cache behavior visibility
   * @side_effects_impact Console I/O adds minimal overhead (per font access)
   * @side_effects_alternatives Silent caching; hides pattern benefit from demo
   * @throws None (noexcept)
   */
  // Accept font by-value and move into new CharacterFont when creating it.
  std::shared_ptr<CharacterFont> GetFont(std::string font, int size) noexcept {
    std::string key = font + "_" + std::to_string(size);
    auto it = fonts_.find(key);
    if (it == fonts_.end()) {
      auto ptr = std::make_shared<CharacterFont>(std::move(font), size);
      auto res = fonts_.emplace(std::move(key), std::move(ptr));
      std::cout << "Creating new font: " << res.first->first << std::endl;
      return res.first->second;
    } else {
      std::cout << "Reusing font: " << it->first << std::endl;
      return it->second;
    }
  }

  /**
   * @brief Gets number of cached fonts
   * @return Number of fonts
   * @side_effects None
   * @throws None (noexcept)
   */
  int GetFontCount() const noexcept { return fonts_.size(); }
};

#endif  // STRUCTURAL_FLYWEIGHT_FLYWEIGHT_HPP_
