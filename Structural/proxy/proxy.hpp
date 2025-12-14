// Created: 2025-11-03
// Filename: proxy.hpp
// Description: Proxy design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_PROXY_PROXY_HPP_
#define STRUCTURAL_PROXY_PROXY_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <utility>

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
   * @side_effects Prints to console for demo feedback (see RealImage rationale)
   * @throws None (noexcept)
   */
  virtual void Display() const noexcept = 0;
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
  /**
   * @brief Constructor with expensive operation simulation
   * @param filename Image filename
   * @side_effects Prints to console to demonstrate expensive creation
   * @side_effects_reason Demonstration requirement: Proxy pattern controls
   *   access to expensive resources. Console output makes lazy loading
   *   visible, showing when RealImage is created vs cached
   * @side_effects_what Writes to stdout for creation cost visibility
   * @side_effects_impact Console I/O demonstrates one-time expensive operation
   * @side_effects_alternatives Silent loading; hides proxy benefit from demo
   * @throws None (noexcept)
   */
  explicit RealImage(std::string filename) noexcept
      : filename_(std::move(filename)) {
    std::cout << "Loading image: " << filename_ << " (expensive operation)"
              << std::endl;
  }

  /**
   * @brief Displays the image
   * @side_effects Prints to console (see constructor rationale)
   * @throws None (noexcept)
   */
  void Display() const noexcept override {
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
  explicit ProxyImage(std::string filename) noexcept
      : filename_(std::move(filename)), real_image_(nullptr) {}

  void Display() const noexcept override {
    if (!real_image_) real_image_ = std::make_unique<RealImage>(filename_);
    real_image_->Display();
  }

  /**
   * @brief Gets filename
   * @return Image filename
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& GetFilename() const noexcept { return filename_; }
};

#endif  // STRUCTURAL_PROXY_PROXY_HPP_
