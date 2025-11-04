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

```
      Mediator (abstract)
           |
      ChatRoom
           |
    Colleague (abstract)
    /      |      \
User1   User2   User3
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
