// Created: 2025-11-03
// Filename: proxy.hpp
// Description: Proxy design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_PROXY_PROXY_HPP_
#define STRUCTURAL_PROXY_PROXY_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Subject - interface for real and proxy
 * @note Defines interface both must implement
 * @side_effects None (abstract)
 */
class Image {
 public:
  virtual ~Image() = default;

  /**
   * @brief Displays the image
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void display() const noexcept = 0;
};

/**
 * @brief Real Subject - actual resource-heavy object
 * @note Expensive to create and use
 * @side_effects None (after construction)
 */
class RealImage : public Image {
 private:
  std::string filename_;

 public:
  explicit RealImage(const std::string& filename) noexcept
      : filename_(filename) {
    std::cout << "Loading image: " << filename << " (expensive operation)"
              << std::endl;
  }

  void display() const noexcept override {
    std::cout << "Displaying image: " << filename_ << std::endl;
  }
};

/**
 * @brief Proxy - controls access to real object
 * @note Delays creation of real object
 * @side_effects Manages real object lifetime
 */
class ProxyImage : public Image {
 private:
  std::string filename_;
  mutable std::unique_ptr<RealImage> real_image_;

 public:
  explicit ProxyImage(const std::string& filename) noexcept
      : filename_(filename), real_image_(nullptr) {}

  void display() const noexcept override {
    if (!real_image_) { real_image_ = std::make_unique<RealImage>(filename_); }
    real_image_->display();
  }

  /**
   * @brief Gets filename
   * @return Image filename
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& get_filename() const noexcept { return filename_; }
};

#endif  // STRUCTURAL_PROXY_PROXY_HPP_
