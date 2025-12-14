// Created: 2025-11-03
// Filename: adapter.cc
// Description: Adapter design pattern demonstration
// Copyright 2025

#include "adapter.hpp"  // [NOLINT]

#include <iostream>

int main() {
  std::cout << "=== Media Player with Adapter ===" << std::endl;

  AudioPlayer audio;
  audio.Play("song.mp3");

  MediaAdapter vlc_adapter("vlc");
  vlc_adapter.Play("movie.vlc");

  MediaAdapter mkv_adapter("mkv");
  mkv_adapter.Play("video.mkv");

  return 0;
}
