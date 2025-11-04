// Created: 2025-11-03
// Filename: observer.hpp
// Description: Observer design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_OBSERVER_OBSERVER_HPP_
#define BEHAVIORAL_OBSERVER_OBSERVER_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Abstract observer interface
 * @note Base class for all observers
 * @side_effects None (abstract)
 */
class Observer {
 public:
  virtual ~Observer() = default;

  /**
   * @brief Called when observed object changes
   * @param property Property name that changed
   * @param new_value New value (as string for simplicity)
   * @side_effects Depends on concrete implementation
   * @throws None (noexcept)
   */
  virtual void update(const std::string& property,
                      const std::string& new_value) noexcept = 0;
};

/**
 * @brief Subject that is observed
 * @note Maintains list of observers and notifies on state change
 * @thread_safety Not thread-safe
 */
class Person {
 private:
  std::string name_;
  int age_;
  std::vector<std::shared_ptr<Observer>> observers_;

 public:
  explicit Person(const std::string& name, int age) noexcept
      : name_(name), age_(age) {}

  /**
   * @brief Gets person name
   * @return Person's name
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& get_name() const noexcept { return name_; }

  /**
   * @brief Gets person age
   * @return Person's age
   * @side_effects None
   * @throws None (noexcept)
   */
  int get_age() const noexcept { return age_; }

  /**
   * @brief Sets person age and notifies observers
   * @param age New age
   * @side_effects Modifies age and notifies all observers
   * @throws None (noexcept)
   */
  void set_age(int age) noexcept {
    if (age_ == age) return;
    age_ = age;
    notify("age", std::to_string(age));
  }

  /**
   * @brief Subscribes an observer
   * @param observer Observer to subscribe
   * @side_effects Adds observer to list
   * @throws None (noexcept)
   */
  void subscribe(std::shared_ptr<Observer> observer) noexcept {
    observers_.push_back(observer);
  }

  /**
   * @brief Notifies all observers of a change
   * @param property Property that changed
   * @param new_value New value
   * @side_effects Calls update on all observers
   * @throws None (noexcept)
   */
  void notify(const std::string& property,
              const std::string& new_value) noexcept {
    for (auto& observer : observers_) { observer->update(property, new_value); }
  }
};

/**
 * @brief Concrete observer that prints changes to console
 * @note Receives notifications from subject
 * @side_effects Prints to standard output
 */
class ConsoleObserver : public Observer {
 private:
  std::string name_;

 public:
  explicit ConsoleObserver(const std::string& name) noexcept : name_(name) {}

  /**
   * @brief Called when observed object changes
   * @param property Property name that changed
   * @param new_value New value
   * @side_effects Prints change notification to console
   * @throws None (noexcept)
   */
  void update(const std::string& property,
              const std::string& new_value) noexcept override {
    std::cout << name_ << " received update: " << property << " = " << new_value
              << std::endl;
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
   * @param property Property name that changed
   * @param new_value New value
   * @side_effects Stores change in log vector
   * @throws None (noexcept)
   */
  void update(const std::string& property,
              const std::string& new_value) noexcept override {
    log_.push_back(property + " changed to " + new_value);
  }

  /**
   * @brief Gets the log of changes
   * @return Vector of log entries
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::vector<std::string>& get_log() const noexcept { return log_; }
};

#endif  // BEHAVIORAL_OBSERVER_OBSERVER_HPP_
