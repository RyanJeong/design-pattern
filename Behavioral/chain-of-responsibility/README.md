# Chain of Responsibility Pattern

## Overview

The Chain of Responsibility pattern is a behavioral design pattern that lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides whether to process the request or pass it along to the next handler in the chain.

## Key Concepts

### Problem

- You need to issue requests to objects without knowing which object will handle the request
- Multiple objects might be able to handle a specific request
- The set of handlers should be specifiable at runtime

### Solution

- Create an abstract handler class that defines the interface for handling requests
- Implement concrete handlers that either process the request or pass it to the next handler
- Build a chain of handlers where each handler has a reference to the next handler
- Send requests through the chain where each handler makes a decision

## Pattern Structure

```text
      Handler
    /        \
  Concrete1  Concrete2
```

### Components

- **Handler**: Abstract base class that defines the request processing interface
- **ConcreteHandler**: Implements request processing logic or passes to next handler
- **Client**: Sends requests to the chain

## Example Implementation

The implementation demonstrates:

- **Modifier**: Abstract handler for creature modifications
- **DoubleAttackModifier**: Concrete handler that doubles attack value
- **IncreaseDefenseModifier**: Concrete handler that conditionally increases defense
- **NoBonusesModifier**: Concrete handler that blocks the chain
- **Creature**: The object being modified

## Key Features

1. **Decoupled Processing**: Senders and receivers are decoupled
2. **Dynamic Chain**: Chain composition can be modified at runtime
3. **Single Responsibility**: Each handler has one specific processing task
4. **Sequential Processing**: Handlers process requests in defined order

## Advantages

- Decouples object that sends a request from those that receive and handle it
- Simplifies object architecture by removing explicit sender-receiver bindings
- Gives you more control over the order of request handling
- Supports dynamic modification of processing chains

## Disadvantages

- No guarantee that a request will be processed
- Can be hard to debug and trace request flow
- Performance overhead with many handlers
- Potential for infinite loops if chain not properly terminated

## When to Use

- Multiple objects may handle a request and which one should handle it is unknown beforehand
- You want to dynamically compose handlers at runtime
- You need to decouple senders from receivers
- Processing should be in a specific order through the chain

## Real-world Applications

- Event handling systems (GUI frameworks)
- HTTP request processing (middleware chains)
- Approval workflows with multiple levels
- Error handling and logging systems
- ATM transaction processing

## C++14 Features

- Move semantics: The `Creature` constructor now accepts the `name` parameter
  by value and moves it into the internal member. This allows constructors to
  accept temporaries or `std::move`'d strings without an extra copy.
