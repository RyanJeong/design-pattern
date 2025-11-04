// Created: 2025-11-03
// Filename: adapter.cc
// Description: Adapter design pattern demonstration
// Copyright 2025

#include "adapter.hpp"

int main() {
  std::cout << "=== Media Player with Adapter ===" << std::endl;

  AudioPlayer audio;
  audio.play("song.mp3");

  MediaAdapter vlc_adapter("vlc");
  vlc_adapter.play("movie.vlc");

  MediaAdapter mkv_adapter("mkv");
  mkv_adapter.play("video.mkv");

  return 0;
}
