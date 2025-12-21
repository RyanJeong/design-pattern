# State Pattern

## Overview

The State pattern is a behavioral design pattern that allows an object to alter its behavior when its internal state changes. The object will appear to change its class.

## Key Concepts

### Problem

- An object's behavior depends on its state and must change at runtime
- Large conditional statements based on state make code hard to maintain
- Multiple objects need different behaviors based on current state

### Solution

- Create separate classes for each possible state
- Move state-specific behavior into these state classes
- Let the context delegate to the current state object
- Change state through state transitions

## Pattern Structure

```text
┌──────────────────────────────────┐
│        State                     │ ◄────── Abstract State
├──────────────────────────────────┤
│                                  │
├──────────────────────────────────┤
│ + On(context): shared_ptr<State> │
│ + Off(context): shared_ptr<State>│
└──────────────────────────────────┘
         ▲
         │ inherits
    ┌────┴─────────────────────────┐
    │                              │
┌────────────────────┐  ┌──────────────────┐
│ OnState            │  │ OffState         │
├────────────────────┤  ├──────────────────┤
│                    │  │                  │
├────────────────────┤  ├──────────────────┤
│ + On(): State      │  │ + On(): State    │
│ + Off(): State     │  │ + Off(): State   │
└────────────────────┘  └──────────────────┘

┌──────────────────────────────────────┐
│       LightSwitch                    │ ◄────── Context
├──────────────────────────────────────┤
│ - state: shared_ptr<State>           │
├──────────────────────────────────────┤
│ + SetState(state: shared_ptr): void  │
│ + GetState(): shared_ptr<State>      │
│ + On(): void                         │
│ + Off(): void                        │
└──────────────────────────────────────┘
         │ uses
         └──────────► State object
```

### Components

- **Context**: Defines the interface for clients and maintains current state
- **State**: Abstract interface for state-specific behavior
- **ConcreteState**: Implements behavior for specific states

## Example Implementation

The implementation demonstrates:

- **LightSwitch**: Context that maintains current state
- **State**: Abstract base for on/off states
- **OnState**: Represents light being on
- **OffState**: Represents light being off

## Key Features

1. **Behavior Encapsulation**: State-specific behavior is encapsulated in separate classes
2. **Single Responsibility**: Each state class handles one state
3. **Easy Extension**: Adding new states is straightforward
4. **Eliminates Conditionals**: Replaces large if-else or switch statements

## Advantages

- Eliminates large conditional statements
- Simplifies code by encapsulating state-specific behavior
- Makes state transitions explicit
- State objects can be shared
- Follows Single Responsibility Principle

## Disadvantages

- Creates many state classes
- Increases code complexity for simple state machines
- Requires careful design to avoid circular dependencies
- State transitions can become hard to trace

## When to Use

- An object's behavior depends on its state and it must change this behavior at runtime
- Operations have large, multi-part conditional statements that depend on object state
- You need to eliminate duplicate state-dependent code
- State transitions should be made explicit

## Real-world Applications

- UI components (buttons, text fields with different states)
- Workflow engines (order processing, task management)
- Game character states (idle, running, jumping)
- TCP connection states
- File parsing with different states
- Media players (playing, paused, stopped)
