// Created: 2025-11-03
// Filename: mediator.hpp
// Description: Mediator design pattern demonstration
// Copyright 2025

#ifndef BEHAVIORAL_MEDIATOR_MEDIATOR_HPP_
#define BEHAVIORAL_MEDIATOR_MEDIATOR_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Forward declaration
 */
class Colleague;

/**
 * @brief Message event
 * @note Immutable representation of message communication
 */
struct Message {
  std::string sender;
  std::string content;
  int timestamp;

  Message(std::string from, std::string msg, int time = 0) noexcept
      : sender(std::move(from)), content(std::move(msg)), timestamp(time) {}
};

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
   * @return Message event result
   * @side_effects May relay message to other colleagues
   * @throws None (noexcept)
   */
  virtual Message Send(Colleague* sender,
                       const std::string& message) noexcept = 0;
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
  // Accept name by-value and move into member to enable move semantics and
  // avoid an extra copy when callers pass temporaries or std::move'd strings.
  explicit Colleague(Mediator* mediator, std::string name) noexcept
      : mediator_(mediator), name_(std::move(name)) {}

  virtual ~Colleague() = default;

  /**
   * @brief Gets colleague name
   * @return Name of colleague
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::string& GetName() const noexcept { return name_; }

  /**
   * @brief Sends message through mediator
   * @param message Message to send
   * @return Message event result
   * @side_effects Sends through mediator
   * @throws None (noexcept)
   */
  virtual Message Send(const std::string& message) noexcept {
    return mediator_->Send(this, message);
  }

  /**
   * @brief Receives message from another user
   * @param msg Message event
   * @side_effects Prints message to console
   * @throws None (noexcept)
   */
  virtual void Receive(const Message& msg) noexcept = 0;
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
  void RegisterUser(Colleague* user) noexcept { users_.push_back(user); }

  /**
   * @brief Broadcasts message from sender to all other users
   * @param sender Colleague sending message
   * @param message Message content
   * @return Message event
   * @side_effects Relays message to all other users
   * @throws None (noexcept)
   */
  Message Send(Colleague* sender,
               const std::string& message) noexcept override {
    Message msg(sender->GetName(), message, static_cast<int>(users_.size()));
    for (auto user : users_)
      if (user != sender) user->Receive(msg);
    return msg;
  }
};

/**
 * @brief Concrete colleague - user in chat room
 * @note Participates in group communication
 * @side_effects Prints received messages for demo visibility
 */
class User : public Colleague {
 public:
  // Accept name by-value and forward to base (moved inside Colleague)
  explicit User(Mediator* mediator, std::string name) noexcept
      : Colleague(mediator, std::move(name)) {}

  /**
   * @brief Receives message from another user
   * @param msg Message event
   * @side_effects Prints message to console for demo feedback
   * @side_effects_reason Demonstration requirement: Mediator pattern shows
   *   how objects communicate through a central mediator. Console output
   *   makes message flow and delivery visible without complex logging setup
   * @side_effects_what Writes to stdout for message visibility
   * @side_effects_impact Console I/O adds latency per message in demo context
   * @side_effects_alternatives Inject logger or event dispatcher; adds
   * complexity
   * @throws None (noexcept)
   */
  void Receive(const Message& msg) noexcept override {
    std::cout << name_ << " received from " << msg.sender << ": " << msg.content
              << std::endl;
  }
};

#endif  // BEHAVIORAL_MEDIATOR_MEDIATOR_HPP_
