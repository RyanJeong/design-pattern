# Strategy Pattern

## Overview

The Strategy pattern is a behavioral design pattern that defines a family of algorithms, encapsulates each one in a separate class, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

## Key Concepts

### Problem

- Multiple algorithms exist for a specific task
- The algorithm should be selected at runtime
- Large conditional statements determine which algorithm to use
- Algorithms need to be changed without modifying client code

### Solution

- Create an abstract strategy interface
- Implement concrete strategies for each algorithm
- Allow client to select strategy at runtime
- Strategy behavior becomes interchangeable

## Pattern Structure

```text
    Strategy (abstract)
    /              \
Concrete1      Concrete2
    \              /
    Context (uses strategy)
```

### Components

- **Strategy**: Abstract interface for algorithms
- **ConcreteStrategy**: Implements specific algorithm
- **Context**: Uses strategy interface
- **Client**: Selects and uses appropriate strategy

## Example Implementation

The implementation demonstrates:

- **ListStrategy**: Abstract interface for list rendering
- **MarkdownListStrategy**: Renders lists in Markdown
- **HtmlListStrategy**: Renders lists in HTML
- **TextProcessor**: Context that uses selected strategy

## Key Features

1. **Algorithm Encapsulation**: Each algorithm is in separate class
2. **Runtime Selection**: Strategy chosen at runtime
3. **Easy Extension**: New strategies can be added easily
4. **Eliminates Conditionals**: Replaces if-else chains

## Advantages

- Simplifies if-else blocks
- Makes algorithms independent
- Allows dynamic algorithm selection
- Improves code maintainability
- Follows Open/Closed Principle

## Disadvantages

- Creates many strategy classes
- Adds complexity for simple problems
- Clients must understand different strategies
- Increased memory overhead

## When to Use

- Many classes differ only in their behavior
- Different variants of an algorithm are needed
- You need to avoid conditional statements
- Related classes differ only in their algorithms

## Real-world Applications

- Sorting algorithms (bubble sort, quick sort, merge sort)
- Rendering engines (different output formats)
- Compression algorithms (ZIP, GZIP, BZIP2)
- Payment methods (credit card, PayPal, Apple Pay)
- Authentication strategies (OAuth, JWT, basic auth)
- File export formats (CSV, JSON, XML)
