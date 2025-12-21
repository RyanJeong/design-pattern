# Template Method Pattern

## Overview

The Template Method pattern is a behavioral design pattern that defines the skeleton of an algorithm in a method, deferring some steps to subclasses. It lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.

## Key Concepts

### Problem

- Multiple classes have similar algorithms with small differences
- Algorithm structure should be shared, but implementations vary
- Code duplication in algorithms with similar flow
- Changing algorithm structure affects many subclasses

### Solution

- Create abstract base class with template method
- Template method defines algorithm skeleton
- Override hook methods in subclasses for specific steps
- Subclasses implement specific behavior while sharing structure

## Pattern Structure

```text
┌────────────────────────────────────────┐
│        Game (abstract)                 │ ◄────── Abstract Base Class
├────────────────────────────────────────┤
│                                        │
├────────────────────────────────────────┤
│ + Play(): void                         │ ◄── Template Method
│ # Start(): void = 0                    │ ◄── Hook Methods
│ # TakeTurn(): void = 0                 │     (abstract)
│ # HaveWinner(): bool = 0               │
│ # End(): void = 0                      │
└────────────────────────────────────────┘
         ▲
         │ inherits
    ┌────┴──────────────────────────┐
    │                               │
┌───────────────────────────┐  ┌──────────────────────┐
│ Chess                     │  │ Checkers             │
├───────────────────────────┤  ├──────────────────────┤
│ - players_count: int      │  │ - players_count: int │
│ - current_player: int     │  │ - current_player: int│
├───────────────────────────┤  ├──────────────────────┤
│ # Start(): void           │  │ # Start(): void      │
│ # TakeTurn(): void        │  │ # TakeTurn(): void   │
│ # HaveWinner(): bool      │  │ # HaveWinner(): bool │
│ # End(): void             │  │ # End(): void        │
└───────────────────────────┘  └──────────────────────┘

Template Method (Play) Flow:
    ┌─────────────────┐
    │  Play()         │ (Final)
    └────────┬────────┘
             │
    ┌────────v─────────┐
    │  Start()         │ (hook override)
    └────────┬─────────┘
             │
    ┌────────v─────────────────┐
    │  while(!HaveWinner())    │
    │    TakeTurn()            │ (hook override)
    └────────┬─────────────────┘
             │
    ┌────────v─────────┐
    │  End()           │ (hook override)
    └──────────────────┘
```

### Components

- **AbstractClass**: Defines template method and hook methods
- **ConcreteClass**: Implements hook methods
- **TemplateMethod**: Defines algorithm structure
- **HookMethod**: Points where subclasses provide specific behavior

## Example Implementation

The implementation demonstrates:

- **Game**: Abstract template method class
- **Chess**: Concrete game with chess-specific behavior
- **Checkers**: Concrete game with checkers-specific behavior
- **play()**: Template method defining game flow
- **Hook methods**: start(), take_turn(), have_winner(), end()

## Key Features

1. **Algorithm Structure**: Common structure defined in base class
2. **Customization**: Subclasses implement specific steps
3. **Inversion of Control**: Framework calls subclass methods
4. **Code Reuse**: Common algorithm logic shared

## Advantages

- Promotes code reuse through inheritance
- Reduces code duplication
- Lets subclasses override specific steps
- Provides clean structure for algorithm
- Follows Open/Closed Principle

## Disadvantages

- May require abstract classes
- Can lead to large base classes
- Tight coupling through inheritance
- Difficult to refactor if structure changes

## When to Use

- Multiple classes have similar algorithms with different implementations
- Common algorithm structure needed across classes
- You want to avoid code duplication
- You need to control subclass extensions

## Real-world Applications

- Framework design (Spring, Qt, web frameworks)
- Data processing pipelines
- Document processing (parsing, rendering)
- Game engine loops
- Testing frameworks (setUp, runTest, tearDown)
- Report generation systems
