#!/bin/bash
# Build script for Behavioral Design Patterns
# This script builds all behavioral design patterns in this directory

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Add pattern names below. Add new patterns here when new patterns are added.
PATTERNS=(
  "chain-of-responsibility"
  "command"
  "interpreter"
  "iterator"
  "mediator"
  "memento"
  "observer"
  "state"
  "strategy"
  "template-method"
  "visitor"
)

echo "=========================================="
echo "Building Behavioral Design Patterns"
echo "=========================================="

for pattern in "${PATTERNS[@]}"; do
  PATTERN_DIR="$SCRIPT_DIR/$pattern"

  if [ ! -d "$PATTERN_DIR" ]; then
    echo "Warning: $pattern directory not found, skipping..."
    continue
  fi

  echo ""
  echo "Building: $pattern"
  echo "----------------------------------------"

  cd "$PATTERN_DIR"

  # Create build directory if it doesn't exist
  if [ ! -d "build" ]; then
    mkdir -p build
  fi

  # Configure and build
  cd build
  cmake ..
  make

  cd ..

  echo "- $pattern built successfully"
done

echo ""
echo "=========================================="
echo "All behavioral patterns built successfully!"
echo "=========================================="
