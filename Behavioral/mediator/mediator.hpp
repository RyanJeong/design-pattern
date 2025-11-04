// Created: 2025-11-03
// Filename: mediator.hpp
// Description: Mediator design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_MEDIATOR_MEDIATOR_HPP_
#define BEHAVIORAL_MEDIATOR_MEDIATOR_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Forward declaration
 */
class Colleague;

/**
 * @brief Abstract mediator interface
 * @note Centralizes communication between colleagues
 * @side_effects None (abstract)
 */
class Mediator {
 public:
  virtual ~Mediator() = default;

  /**
   * @brief Handles message from colleague
   * @param sender Colleague sending message
   * @param message Message content
   * @side_effects May relay message to other colleagues
   * @throws None (noexcept)
   */
  virtual void send(Colleague* sender, const std::string& message) noexcept = 0;
};

/**
 * @brief Colleague that communicates through mediator
 * @note Base class for communicating objects
 * @side_effects None (abstract)
 */
class Colleague {
 protected:
  Mediator* mediator_;
  std::string name_;

 public:
  explicit Colleague(Mediator* mediator, const std::string& name) noexcept
      : mediator_(mediator), name_(name) {}

  virtual ~Colleague() = default;

  /**
   * @brief Gets colleague name
   * @return Name of colleague
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& get_name() const noexcept { return name_; }

  /**
   * @brief Sends message through mediator
   * @param message Message to send
   * @side_effects Sends through mediator
   * @throws None (noexcept)
   */
  virtual void send(const std::string& message) noexcept {
    mediator_->send(this, message);
  }

  /**
   * @brief Receives message from mediator
   * @param sender Original sender
   * @param message Message content
   * @side_effects Prints message
   * @throws None (noexcept)
   */
  virtual void receive(const std::string& sender,
                       const std::string& message) noexcept = 0;
};

/**
 * @brief Concrete mediator - chat room
 * @note Manages communication between users
 * @thread_safety Not thread-safe
 */
class ChatRoom : public Mediator {
 private:
  std::vector<Colleague*> users_;

 public:
  /**
   * @brief Registers a user in the chat room
   * @param user User to register
   * @side_effects Adds user to list
   * @throws None (noexcept)
   */
  void register_user(Colleague* user) noexcept { users_.push_back(user); }

  /**
   * @brief Broadcasts message from sender to all other users
   * @param sender Colleague sending message
   * @param message Message content
   * @side_effects Relays message to all other users
   * @throws None (noexcept)
   */
  void send(Colleague* sender, const std::string& message) noexcept override {
    for (auto user : users_) {
      if (user != sender) { user->receive(sender->get_name(), message); }
    }
  }
};

/**
 * @brief Concrete colleague - user in chat room
 * @note Participates in group communication
 * @side_effects Prints received messages
 */
class User : public Colleague {
 public:
  explicit User(Mediator* mediator, const std::string& name) noexcept
      : Colleague(mediator, name) {}

  /**
   * @brief Receives message from another user
   * @param sender Original sender name
   * @param message Message content
   * @side_effects Prints message to console
   * @throws None (noexcept)
   */
  void receive(const std::string& sender,
               const std::string& message) noexcept override {
    std::cout << name_ << " received from " << sender << ": " << message
              << std::endl;
  }
};

#endif  // BEHAVIORAL_MEDIATOR_MEDIATOR_HPP_
