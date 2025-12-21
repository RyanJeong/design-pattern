# Mediator Pattern

## Overview

The Mediator pattern is a behavioral design pattern that defines an object that encapsulates how a set of objects interact. This pattern is considered to be a behavioral solution due to the way it can alter the program's flow by centralizing communication between objects.

## Key Concepts

### Problem

- Multiple objects communicate with each other
- Objects have complex interdependencies
- Changing one object affects many others
- Tight coupling makes code hard to maintain

### Solution

- Create a mediator object that handles communication
- Objects communicate only through the mediator
- Mediator encapsulates communication logic
- Objects don't need to know about each other

## Pattern Structure

```text
┌──────────────────────────────┐
│    Mediator (abstract)       │ ◄────── Abstract Mediator
├──────────────────────────────┤
│                              │
├──────────────────────────────┤
│ + RegisterColleague(c): ◆    │
│ + Send(msg, from, to): ◆     │
└──────────────────────────────┘
         ▲
         │ inherits
         │
┌────────────────────────────────┐
│      ChatRoom                  │
├────────────────────────────────┤
│ - users: vector<unique_ptr>    │
├────────────────────────────────┤
│ + RegisterColleague(user): void│
│ + Send(msg, from, to): void    │
│ + Display(): void              │
└────────────────────────────────┘
         ▲
         │ coordinates
         │
    ┌────┴──────────────────────────────┐
    │                                   │
┌────────────────────────────┐  ┌─────────────────────────┐
│ Colleague (abstract)       │  │                         │
├────────────────────────────┤  │ (Concrete Colleagues)   │
│ # mediator: Mediator*      │  │                         │
│ # name: string             │  │ - ChatRoom*             │
├────────────────────────────┤  │ - name: string          │
│ + Send(msg, to): void      │  │ + Send(msg, to): void   │
│ + Receive(msg, from): void │  └─────────────────────────┘
└────────────────────────────┘
         ▲
         │ inherits
         │
      User
    + Receive(msg): void

Relationship:
   ┌──────────┐       ┌──────────┐
   │  User 1  │       │  User 2  │
   └────┬─────┘       └────┬─────┘
        │                  │
        └──────┬───────────┘
               │ communicate
               │ through
               v
        ┌─────────────┐
        │  ChatRoom   │
        │  (Mediator) │
        └─────────────┘
```

### Components

- **Mediator**: Defines interface for colleague communication
- **ConcreteMediator**: Implements coordination logic
- **Colleague**: Abstract base for communicating objects
- **ConcreteColleague**: Implements specific colleague type

## Example Implementation

The implementation demonstrates:

- **Mediator**: Abstract mediator interface
- **ChatRoom**: Concrete mediator managing user communication
- **Colleague**: Abstract colleague base class
- **User**: Concrete colleague participating in chat

## Key Features

1. **Centralized Communication**: All messages flow through mediator
2. **Loose Coupling**: Colleagues don't know each other
3. **Reusability**: Colleagues can be reused with different mediators
4. **Simplified Communication**: Complex interactions simplified

## Advantages

- Reduces coupling between communicating objects
- Centralizes communication logic
- Simplifies object interactions
- Makes system easier to maintain and understand
- Follows Single Responsibility Principle

## Disadvantages

- Mediator can become a "God Object"
- Mediator complexity grows with colleague count
- Can be overkill for simple communications
- Harder to debug communication flows

## When to Use

- Multiple objects need to communicate in complex ways
- Objects are tightly coupled and hard to reuse
- Communication logic should be centralized
- You want to reduce dependencies between objects

## Real-world Applications

- Chat room systems
- Air traffic control systems
- GUI dialog boxes
- Event system mediators
- Game multiplayer lobbies
- Workflow engines
- Dialog box handling in UI frameworks

## C++14 Features

- Move semantics: Colleague/User constructors accept the name parameter by-value and move it into the member (e.g. `Colleague(Mediator*, std::string name)` then `name_ = std::move(name)`). This lets callers pass temporaries or `std::move` existing strings to avoid unnecessary copies.
