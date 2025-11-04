// Created: 2025-11-03
// Filename: adapter.hpp
// Description: Adapter design pattern implementation
// Copyright 2025

#ifndef STRUCTURAL_ADAPTER_ADAPTER_HPP_
#define STRUCTURAL_ADAPTER_ADAPTER_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Target interface - expected by client
 * @note Defines interface client expects
 * @side_effects None (abstract)
 */
class MediaPlayer {
 public:
  virtual ~MediaPlayer() = default;

  /**
   * @brief Plays media file
   * @param filename File to play
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void play(const std::string& filename) const noexcept = 0;
};

/**
 * @brief Adaptee - incompatible interface
 * @note Existing class with different interface
 * @side_effects None (after construction)
 */
class AdvancedMediaPlayer {
 public:
  virtual ~AdvancedMediaPlayer() = default;

  /**
   * @brief Plays VLC format
   * @param filename File to play
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void play_vlc(const std::string& filename) const noexcept = 0;

  /**
   * @brief Plays MKV format
   * @param filename File to play
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void play_mkv(const std::string& filename) const noexcept = 0;
};

/**
 * @brief Concrete Adaptee - VLC player
 * @note Existing VLC player implementation
 * @side_effects None (after construction)
 */
class VlcPlayer : public AdvancedMediaPlayer {
 public:
  void play_vlc(const std::string& filename) const noexcept override {
    std::cout << "Playing VLC file: " << filename << std::endl;
  }

  void play_mkv(const std::string&) const noexcept override {
    std::cout << "Cannot play MKV in VLC" << std::endl;
  }
};

/**
 * @brief Concrete Adaptee - MKV player
 * @note Existing MKV player implementation
 * @side_effects None (after construction)
 */
class MkvPlayer : public AdvancedMediaPlayer {
 public:
  void play_vlc(const std::string&) const noexcept override {
    std::cout << "Cannot play VLC in MKV player" << std::endl;
  }

  void play_mkv(const std::string& filename) const noexcept override {
    std::cout << "Playing MKV file: " << filename << std::endl;
  }
};

/**
 * @brief Adapter - makes incompatible interface compatible
 * @note Adapts AdvancedMediaPlayer to MediaPlayer interface
 * @side_effects Stores adaptee reference
 */
class MediaAdapter : public MediaPlayer {
 private:
  std::unique_ptr<AdvancedMediaPlayer> player_;
  std::string file_type_;

 public:
  explicit MediaAdapter(const std::string& file_type) noexcept
      : file_type_(file_type) {
    if (file_type == "vlc") {
      player_ = std::make_unique<VlcPlayer>();
    } else if (file_type == "mkv") {
      player_ = std::make_unique<MkvPlayer>();
    }
  }

  void play(const std::string& filename) const noexcept override {
    if (file_type_ == "vlc") {
      player_->play_vlc(filename);
    } else if (file_type_ == "mkv") {
      player_->play_mkv(filename);
    }
  }
};

/**
 * @brief Concrete Target - audio player
 * @note Implementation of MediaPlayer interface
 * @side_effects None (after construction)
 */
class AudioPlayer : public MediaPlayer {
 public:
  void play(const std::string& filename) const noexcept override {
    std::cout << "Playing audio file: " << filename << std::endl;
  }
};

#endif  // STRUCTURAL_ADAPTER_ADAPTER_HPP_
