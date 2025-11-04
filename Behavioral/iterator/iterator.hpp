// Created: 2025-11-03
// Filename: iterator.hpp
// Description: Iterator design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_ITERATOR_ITERATOR_HPP_
#define BEHAVIORAL_ITERATOR_ITERATOR_HPP_

#include <memory>
#include <vector>

template <typename T>
class Iterator;

/**
 * @brief Aggregate collection interface
 * @note Base class for collections
 * @side_effects None (abstract)
 */
template <typename T>
class Collection {
 public:
  virtual ~Collection() = default;

  /**
   * @brief Creates an iterator for this collection
   * @return Iterator for the collection
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual std::shared_ptr<Iterator<T>> create_iterator() noexcept = 0;
};

/**
 * @brief Iterator interface
 * @note Base class for iterators
 * @side_effects None (abstract)
 */
template <typename T>
class Iterator {
 public:
  virtual ~Iterator() = default;

  /**
   * @brief Checks if more elements exist
   * @return true if more elements exist
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual bool has_next() const noexcept = 0;

  /**
   * @brief Gets the next element
   * @return Next element
   * @side_effects Advances iterator
   * @throws None (noexcept)
   */
  virtual T next() noexcept = 0;
};

/**
 * @brief Concrete iterator for vector
 * @note Iterates through vector collection
 * @side_effects Advances position
 */
template <typename T>
class VectorIterator : public Iterator<T> {
 private:
  std::vector<T>& collection_;
  size_t current_{0};

 public:
  explicit VectorIterator(std::vector<T>& collection) noexcept
      : collection_(collection) {}

  /**
   * @brief Checks if more elements exist
   * @return true if more elements exist
   * @side_effects None
   * @throws None (noexcept)
   */
  bool has_next() const noexcept override {
    return current_ < collection_.size();
  }

  /**
   * @brief Gets the next element and advances
   * @return Next element
   * @side_effects Increments current position
   * @throws None (noexcept)
   */
  T next() noexcept override { return collection_[current_++]; }
};

/**
 * @brief Concrete vector collection
 * @note Stores elements in vector
 * @thread_safety Not thread-safe
 */
template <typename T>
class VectorCollection : public Collection<T> {
 private:
  std::vector<T> items_;

 public:
  /**
   * @brief Adds item to collection
   * @param item Item to add
   * @side_effects Adds to internal vector
   * @throws None (noexcept)
   */
  void add_item(const T& item) noexcept { items_.push_back(item); }

  /**
   * @brief Creates an iterator for this collection
   * @return Iterator for the collection
   * @side_effects None
   * @throws None (noexcept)
   */
  std::shared_ptr<Iterator<T>> create_iterator() noexcept override {
    return std::make_shared<VectorIterator<T>>(items_);
  }
};

#endif  // BEHAVIORAL_ITERATOR_ITERATOR_HPP_
