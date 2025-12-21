# Memento Pattern

## Overview

The Memento pattern is a behavioral design pattern that captures and saves the internal state of an object without violating encapsulation, so it can be restored later. This pattern is used to implement undo/redo functionality.

## Key Concepts

### Problem

- Need to save and restore object state
- Can't violate encapsulation by exposing internal state
- Need to support undo/redo operations
- State snapshots needed at various points

### Solution

- Create memento objects that capture state
- Originator creates mementos and restores from them
- Caretaker manages memento history
- Encapsulation maintained through accessor patterns

## Pattern Structure

```text
Originator     Memento      Caretaker
   |              |             |
   +--creates---->+             |
   +--restores---<+             |
                                |
                         +------+
                         |stores
                         v
                      History
```

### Components

- **Originator**: Creates mementos and restores state
- **Memento**: Stores snapshot of state (immutable)
- **Caretaker**: Manages and stores mementos
- **Client**: Uses originator and caretaker for undo/redo

## Example Implementation

The implementation demonstrates:

- **BankAccount**: Originator that creates mementos
- **BankAccountMemento**: Memento storing balance state
- **BankAccountCaretaker**: Manages undo/redo history
- **History management** with save/undo/redo operations

## Key Features

1. **State Capture**: Snapshot of object state stored
2. **Undo/Redo**: Navigate through state history
3. **Encapsulation**: Internal state protected
4. **History Management**: Automatic redo stack clearing

## Advantages

- Provides undo/redo capability
- Maintains encapsulation
- Allows rollback to previous states
- Clean separation of concerns
- Easy to implement for simple objects

## Disadvantages

- High memory overhead for large objects
- Memento objects can be expensive to create
- Difficult to manage complex object graphs
- No garbage collection of old states

## When to Use

- Need to implement undo/redo functionality
- Must preserve encapsulation when saving state
- Objects have discrete states worth capturing
- State restoration needed at multiple points

## Real-world Applications

- Text editor undo/redo
- Version control systems
- Database transaction rollback
- Game save/load functionality
- Configuration checkpoint/restore
- Workflow state management
- Photo editor history
