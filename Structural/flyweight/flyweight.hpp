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
  CharacterFont(const std::string& font, int size) noexcept
      : font_(font), size_(size) {}

  /**
   * @brief Displays character with font
   * @param character Character to display
   * @param x X coordinate
   * @param y Y coordinate
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  void display(char character, int x, int y) const noexcept {
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
   * @side_effects Creates new font if not exists
   * @throws None (noexcept)
   */
  std::shared_ptr<CharacterFont> get_font(const std::string& font,
                                          int size) noexcept {
    std::string key = font + "_" + std::to_string(size);
    if (fonts_.find(key) == fonts_.end()) {
      fonts_[key] = std::make_shared<CharacterFont>(font, size);
      std::cout << "Creating new font: " << key << std::endl;
    } else {
      std::cout << "Reusing font: " << key << std::endl;
    }
    return fonts_[key];
  }

  /**
   * @brief Gets number of cached fonts
   * @return Number of fonts
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_font_count() const noexcept { return fonts_.size(); }
};

#endif  // STRUCTURAL_FLYWEIGHT_FLYWEIGHT_HPP_
