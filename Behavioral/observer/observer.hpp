// Created: 2025-11-03
// Filename: observer.hpp
// Description: Observer design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_OBSERVER_OBSERVER_HPP_
#define BEHAVIORAL_OBSERVER_OBSERVER_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Notification event
 * @note Immutable representation of property change
 */
struct PropertyChange {
  std::string property;
  std::string old_value;
  std::string new_value;

  PropertyChange(std::string prop, std::string old_val,
                 std::string new_val) noexcept
      : property(std::move(prop)),
        old_value(std::move(old_val)),
        new_value(std::move(new_val)) {}
};

/**
 * @brief Abstract observer interface
 * @note Base class for all observers
 * @side_effects Observers must document their specific side effects
 */
class Observer {
 public:
  virtual ~Observer() = default;

  /**
   * @brief Called when observed object changes
   * @param change Property change event
   * @side_effects Observer-specific (documented in implementations)
   * @throws None (noexcept)
   */
  virtual void OnPropertyChanged(const PropertyChange& change) noexcept = 0;
};

/**
 * @brief Subject that is observed
 * @note Immutable object that creates new instances with updated values
 * @thread_safety Not thread-safe (mutable observer list side effect)
 */
class Person {
 private:
  std::string name_;
  int age_;
  mutable std::vector<std::shared_ptr<Observer>> observers_;

 public:
  // Accept name by-value and move into member to enable move semantics.
  explicit Person(std::string name, int age) noexcept
      : name_(std::move(name)), age_(age) {}

  /**
   * @brief Gets person name
   * @return Person's name
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& GetName() const noexcept { return name_; }

  /**
   * @brief Gets person age
   * @return Person's age
   * @side_effects None
   * @throws None (noexcept)
   */
  int GetAge() const noexcept { return age_; }

  /**
   * @brief Returns person with updated age
   * @param new_age New age value
   * @return New person instance with updated age
   * @side_effects None (returns new object, notifies observers)
   * @throws None (noexcept)
   */
  Person WithAge(int new_age) const noexcept {
    if (age_ == new_age) return *this;

    Person updated(name_, new_age);
    updated.observers_ = observers_;

    // Notify observers of the change (side effect - documented)
    PropertyChange change("age", std::to_string(age_), std::to_string(new_age));
    updated.Notify(change);

    return updated;
  }

  /**
   * @brief Subscribes an observer
   * @param observer Observer to subscribe
   * @return New person with registered observer
   * @side_effects Adds observer to list
   * @throws None (noexcept)
   */
  Person Subscribe(std::shared_ptr<Observer> observer) const noexcept {
    Person subscribed(*this);
    subscribed.observers_.push_back(observer);
    return subscribed;
  }

  /**
   * @brief Notifies all observers of a change
   * @param change Property change event
   * @side_effects Calls OnPropertyChanged on all observers
   * @throws None (noexcept)
   */
  void Notify(const PropertyChange& change) const noexcept {
    for (auto& observer : observers_) observer->OnPropertyChanged(change);
  }
};

/**
 * @brief Concrete observer that prints changes to console
 * @note Receives notifications from subject
 * @side_effects Prints to standard output for demo feedback
 */
class ConsoleObserver : public Observer {
 private:
  std::string name_;

 public:
  // Accept name by-value and move into member to avoid extra copies when
  // callers pass temporaries or std::move'd strings.
  explicit ConsoleObserver(std::string name) noexcept
      : name_(std::move(name)) {}

  /**
   * @brief Called when observed object changes
   * @param change Property change event
   * @side_effects Prints change notification to console for demo feedback
   * @side_effects_reason Demonstration requirement: Observer pattern shows
   *   how multiple objects react to changes. Console output demonstrates
   *   notification flow without requiring complex external logging system
   * @side_effects_what Writes to stdout for change visibility
   * @side_effects_impact Console I/O adds latency per notification in demo
   * context
   * @side_effects_alternatives Inject logger; adds complexity for demo code
   * @throws None (noexcept)
   */
  void OnPropertyChanged(const PropertyChange& change) noexcept override {
    std::cout << name_ << " received update: " << change.property << " = "
              << change.old_value << " -> " << change.new_value << std::endl;
  }
};

/**
 * @brief Concrete observer that logs changes
 * @note Receives notifications and stores them
 * @side_effects Stores notifications in log
 */
class LoggingObserver : public Observer {
 private:
  std::vector<std::string> log_;

 public:
  /**
   * @brief Called when observed object changes
   * @param change Property change event
   * @side_effects Stores change in log vector
   * @throws None (noexcept)
   */
  void OnPropertyChanged(const PropertyChange& change) noexcept override {
    log_.push_back(change.property + ": " + change.old_value + " -> " +
                   change.new_value);
  }

  /**
   * @brief Gets the log of changes
   * @return Vector of log entries
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::vector<std::string>& GetLog() const noexcept { return log_; }
};

#endif  // BEHAVIORAL_OBSERVER_OBSERVER_HPP_
