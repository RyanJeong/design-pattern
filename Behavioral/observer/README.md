# Observer Pattern

## Overview

The Observer pattern is a behavioral design pattern that defines a one-to-many relationship between objects where, when one object (the subject) changes state, all its dependents (observers) are notified automatically.

## Key Concepts

### Problem

- Multiple objects need to be notified of state changes in another object
- Objects are tightly coupled through direct references
- You need loose coupling between objects that interact

### Solution

- Define a subject that maintains a list of observers
- Observers subscribe to the subject to receive notifications
- When the subject's state changes, it notifies all observers
- Observers react to the notifications independently

## Pattern Structure

```text
Subject        Observer (abstract)
   \              /          \
    Concrete1  Concrete2
```

### Components

- **Subject**: Maintains state and notifies observers of changes
- **Observer**: Defines the interface for receiving notifications
- **ConcreteObserver**: Implements observer interface and reacts to updates
- **ConcreteSubject**: Maintains state and sends notifications

## Example Implementation

The implementation demonstrates:

- **Person**: Subject that notifies observers of age changes
- **Observer**: Abstract base class for observers
- **ConsoleObserver**: Concrete observer that prints changes
- **LoggingObserver**: Concrete observer that logs changes

## Key Features

1. **Loose Coupling**: Subject and observers are loosely coupled
2. **Dynamic Subscriptions**: Observers can subscribe and unsubscribe at runtime
3. **Automatic Updates**: Changes automatically propagate to all observers
4. **Multiple Observers**: One subject can have many observers

## Advantages

- Establishes a clean interface between subjects and observers
- Supports broadcast-type communication
- Observers can be added and removed at runtime
- Reduces coupling between communicating objects
- Follows the Open/Closed Principle

## Disadvantages

- Observers are notified in random order
- Can lead to unexpected update cascades
- Memory overhead from storing observer lists
- Observers have no knowledge of other observers

## When to Use

- A change to one object requires changing others, and you don't know how many objects need to change
- An object should notify other objects without assuming who these objects are
- You need to establish communication between layers without creating strong dependencies

## Real-world Applications

- MVC architecture (model-view updates)
- Event handling systems
- Real-time data updates (stock prices, weather)
- UI component updates
- Publish-subscribe messaging systems
- Change notifications in document editors

## C++14 Features

- Move semantics: Subject/observer constructors (e.g. `Person` and `ConsoleObserver`) accept string parameters by-value and move them into members (`Person(std::string name, int age) : name_(std::move(name)), ...`). This avoids extra copies when callers pass temporaries or `std::move` existing strings.
