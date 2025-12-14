# Flyweight Pattern

## Pattern Overview

The **Flyweight Pattern** reduces memory usage by sharing common state between many similar objects. It separates intrinsic state (shared) from extrinsic state (unique).

## Intent

- Reduce memory usage for objects with shared state
- Support large numbers of similar objects
- Share common data efficiently
- Trade memory for slight CPU overhead

## Structure

```text
+-----------------------+
| FlyweightFactory      |
|-----------------------|
| - flyweights_ (cache) |
| + GetFlyweight()      |
+-----------------------+
           |
           | creates/returns
           v
+------------------+
|   Flyweight      | (Intrinsic state)
|------------------|
| - font_ (shared) |
| - size_ (shared) |
+------------------+

Client provides Extrinsic state:
- Position (x, y)
- Character
```

## Implementation Details

### Intrinsic vs Extrinsic State

```cpp
// Intrinsic (shared in flyweight)
class CharacterFont {
  std::string font_;  // shared
  int size_;          // shared
};

// Extrinsic (provided by client)
void Display(char character, int x, int y);
```

### Factory Caching

```cpp
class FlyweightFactory {
  std::map<Key, Flyweight*> pool;
  
  Flyweight& Get(const Key& key) {
    if (pool.find(key) == pool.end())
      pool[key] = new Flyweight(key);
    return pool[key];
  }
};
```

## Use Cases

- Text editors (character formatting)
- Game particles (millions of bullets/particles)
- Caches (database connection pooling)
- String pooling
- Object pooling
- Web browser rendering

## Advantages

- Dramatically reduces memory usage
- Improves performance for large object counts
- Centralizes shared state management
- Efficient resource pooling

## Disadvantages

- Increased CPU overhead from lookup
- Thread safety complexity
- Difficult to debug
- Not beneficial for small object counts
- Separates intrinsic/extrinsic state

## Related Patterns

- **Factory Method**: Creates flyweights
- **Object Pool**: Similar resource pooling
- **Singleton**: Factory often singleton
- **Strategy**: Different approach to optimization

## Key Classes

- **CharacterFont**: Flyweight storing intrinsic state
- **CharacterFontFactory**: Factory managing flyweight pool

## Notes

- Significant memory savings for large object counts
- Factory maintains object pool
- Flyweights should be immutable
- Extrinsic state passed by client
- Client responsible for context
- Thread-safe factory recommended

## C++14 Features

- Move semantics: `CharacterFont` constructor and `CharacterFontFactory::get_font` accept the font name by-value and move it into members or newly created flyweights. This allows callers to pass temporaries or `std::move` existing strings and avoid unnecessary copies when creating cached fonts.
