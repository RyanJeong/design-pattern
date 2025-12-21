// Created: 2025-11-03
// Filename: iterator.hpp
// Description: Iterator design pattern demonstration
// Copyright 2025

#ifndef BEHAVIORAL_ITERATOR_ITERATOR_HPP_
#define BEHAVIORAL_ITERATOR_ITERATOR_HPP_

#include <memory>
#include <utility>
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
  virtual std::shared_ptr<Iterator<T>> CreateIterator() noexcept = 0;
};

/**
 * @brief Iterator state
 * @note Immutable snapshot of iteration progress
 */
template <typename T>
struct IterationState {
  T current_value;
  bool has_more;
  size_t position;

  IterationState(T value, bool more, size_t pos) noexcept
      : current_value(value), has_more(more), position(pos) {}
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
  virtual bool HasNext() const noexcept = 0;

  /**
   * @brief Gets the next element and creates new iterator state
   * @return Next element with iteration state
   * @side_effects None (immutable iterator)
   * @throws None (noexcept)
   */
  virtual IterationState<T> Next() const noexcept = 0;
};

/**
 * @brief Concrete iterator for vector
 * @note Immutable iteration through vector collection
 * @side_effects None
 */
template <typename T>
class VectorIterator : public Iterator<T> {
 private:
  std::vector<T>& collection_;
  size_t current_;

 public:
  explicit VectorIterator(std::vector<T>& collection, size_t pos = 0) noexcept
      : collection_(collection), current_(pos) {}

  /**
   * @brief Checks if more elements exist
   * @return true if more elements exist
   * @side_effects None
   * @throws None (noexcept)
   */
  bool HasNext() const noexcept override {
    return current_ < collection_.size();
  }

  /**
   * @brief Gets the next element and creates new iterator state
   * @return Current element with next iterator state
   * @side_effects None (returns new iterator)
   * @throws None (noexcept)
   */
  IterationState<T> Next() const noexcept override {
    if (current_ < collection_.size()) {
      return IterationState<T>(collection_[current_],
                               current_ + 1 < collection_.size(), current_ + 1);
    }
    return IterationState<T>(T{}, false, current_);
  }
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
  // Accept item by-value and move into internal vector to enable callers
  // to pass temporaries or std::move existing objects without extra copies.
  void AddItem(T item) noexcept { items_.push_back(std::move(item)); }

  /**
   * @brief Creates an iterator for this collection
   * @return Iterator for the collection
   * @side_effects None
   * @throws None (noexcept)
   */
  std::shared_ptr<Iterator<T>> CreateIterator() noexcept override {
    return std::make_shared<VectorIterator<T>>(items_);
  }
};

#endif  // BEHAVIORAL_ITERATOR_ITERATOR_HPP_
