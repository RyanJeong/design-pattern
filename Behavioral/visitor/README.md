# Visitor Pattern

## Overview

The Visitor pattern is a behavioral design pattern that represents an operation to be performed on the elements of an object structure. It lets you define a new operation without changing the classes of the elements on which it operates.

## Key Concepts

### Problem

- Need to perform different operations on complex object structures
- Object structure frequently changes but operations remain stable
- Adding operations to classes would violate Single Responsibility Principle
- Operations are logically separate from object data

### Solution

- Define visitor interface with visit methods for each element type
- Elements implement accept method to receive visitors
- Each operation becomes a concrete visitor
- New operations added by creating new visitor classes

## Pattern Structure

```
  Element (abstract)         Visitor (abstract)
  /                \         /                \
Concrete1     Concrete2   Concrete1V      Concrete2V
  \             /             /              /
   \___accept__/             /___visit_____/
```

### Components

- **Element**: Object that accepts visitors
- **ConcreteElement**: Specific element implementing accept
- **Visitor**: Abstract interface for operations
- **ConcreteVisitor**: Implements specific operation
- **ObjectStructure**: Collection of elements

## Example Implementation

The implementation demonstrates:

- **Expression**: Element accepting visitors
- **Literal, BinaryOp**: Concrete elements
- **ExpressionVisitor**: Abstract visitor interface
- **PrintVisitor**: Prints expression structure
- **EvalVisitor**: Evaluates expression result

## Key Features

1. **Operation Separation**: Operations separated from data structure
2. **Easy Extension**: New operations added without changing elements
3. **Double Dispatch**: Right method selected at runtime
4. **Centralized Operations**: Related operations grouped in visitor

## Advantages

- Easy to add new operations without changing element classes
- Centralizes operation logic in visitor classes
- Makes operations explicit and structured
- Supports complex traversals and operations
- Follows Open/Closed Principle

## Disadvantages

- Complex to implement for simple structures
- Difficult to add new element types
- Requires double dispatch mechanism
- Can be overkill for simple operations
- Performance overhead compared to direct methods

## When to Use

- Object structure is stable but operations vary
- Many distinct and unrelated operations needed
- Operations should be independent of object structure
- You need to perform operations on deeply nested structures

## Real-world Applications

- Compiler abstract syntax tree processing
- Document processing (XML parsing)
- Graphics rendering systems
- File system operations
- Game entity processing
- Data transformation pipelines
- Report generation systems
