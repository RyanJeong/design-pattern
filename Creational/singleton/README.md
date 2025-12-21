# Singleton Pattern

## Pattern Overview

The **Singleton Pattern** ensures that a class has only one instance and provides a global point of access to it. It is commonly used for centralized resource management.

## Intent

- Ensure a class has only one instance
- Provide a global access point to that instance
- Delay instance creation until first use (lazy initialization)

## Structure

```
-----------------
|  Singleton     |
|----------------|
| - instance     |
|----------------|
| + getInstance()|
-----------------
```

## Implementation Details

### Thread-Safe Implementation (C++14)

Uses static variable initialization which is thread-safe in C++11 and later:

```cpp
static Logger& instance() noexcept {
  static Logger instance;
  return instance;
}
```

### Key Components

1. **Private Constructor**: Prevents external instantiation
2. **Deleted Copy Constructor**: Prevents copying
3. **Deleted Assignment Operator**: Prevents assignment
4. **Static getInstance()**: Returns the single instance

## Use Cases

- Logger instances
- Database connections
- Application configuration
- Thread pools
- Caches
- Registry objects

## Advantages

- Ensures single instance across application
- Global access point to instance
- Lazy initialization (instance created on first use)
- Thread-safe in C++11 and later
- Memory-efficient

## Disadvantages

- Difficult to test (hides dependencies)
- Makes unit testing more complex
- Can mask design issues
- Global state management

## Related Patterns

- **Factory Method**: Can create singletons
- **Abstract Factory**: Can use singletons as factories
- **Facade**: Often implemented as singleton

## Key Classes

- **Logger**: Singleton class providing logging functionality
  - Private constructor
  - Static `get_instance()` method
  - `log()` method for logging messages

## Notes

- Use mutex if additional synchronization is needed (beyond compiler)
- Meyer's Singleton (static variable) is recommended for C++11+
- Consider using dependency injection for testability
