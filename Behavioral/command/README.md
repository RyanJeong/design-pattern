# Command Pattern

## Overview

The Command pattern is a behavioral design pattern that encapsulates a request as an object, thereby letting you parameterize clients with different requests, queue requests, and support undoable operations.

## Key Concepts

### Problem

- You need to issue requests without knowing the receiver's exact type
- You need to queue, log, or execute requests with retry logic
- You need to support undo/redo operations
- You need to structure systems around high-level operations composed of primitives

### Solution

- Encapsulate each request as a separate command object
- Create an abstract command interface with execute and undo methods
- Implement concrete commands for specific operations
- Use an invoker to execute and manage command history

## Pattern Structure

```text
    Command (abstract)
    /              \
Concrete1      Concrete2
    \              /
    Invoker (manages history)
```

### Components

- **Command**: Abstract interface for all concrete commands
- **ConcreteCommand**: Encapsulates a specific request and action
- **Invoker**: Asks commands to carry out requests and manages history
- **Receiver**: Performs the actual work (e.g., BankAccount)
- **Client**: Creates concrete commands and associates them with invokers

## Example Implementation

The implementation demonstrates:

- **Command**: Abstract base class with execute and undo
- **DepositCommand**: Concrete command for deposit operation
- **WithdrawCommand**: Concrete command for withdrawal operation
- **CommandInvoker**: Manages execution history and undo/redo
- **BankAccount**: Receiver that performs the operations

## Key Features

1. **Encapsulation**: Requests are encapsulated as objects
2. **Undo/Redo**: Commands can be undone and redone
3. **Queuing**: Commands can be queued for later execution
4. **Macro Commands**: Multiple commands can be composed together
5. **Logging**: Command history can be logged and replayed

## Advantages

- Decouples the object that invokes the operation from the object that performs it
- Lets you create a sequence of commands to be executed later
- Supports undo/redo functionality
- Supports macro commands (composite commands)
- Supports transactional systems

## Disadvantages

- May result in lots of command classes
- Adds complexity to the code structure
- Memory overhead for storing command history
- Can be overused in simple scenarios

## When to Use

- You need to parameterize objects with operations
- You need to queue operations, schedule their execution, or execute them remotely
- You need to support undo/redo functionality
- You need to structure systems as a set of high-level commands built on primitives
- You need to implement a callback mechanism

## Real-world Applications

- GUI applications (button clicks, menu items)
- Transaction systems (bank transactions)
- Macro recording and playback
- Undo/redo functionality in editors
- Task scheduling systems
- Job queues in application servers
