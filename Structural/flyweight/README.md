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
┌──────────────────────────────────┐
│   FlyweightFactory               │ ◄────── Factory with Cache
├──────────────────────────────────┤
│ - flyweights: map<Key, Flyweight>│
│   (object pool)                  │
├──────────────────────────────────┤
│ + GetFlyweight(key): Flyweight&  │
│   {                              │
│     if (!pool.contains(key))     │
│       pool[key] = new Flyweight()│
│     return pool[key]             │
│   }                              │
│ + GetOrCreate(): Flyweight&      │
└──────────────────────────────────┘
         │
         │ manages/caches
         │
┌────────v─────────────────┐
│    Flyweight             │ ◄────── Shareable Object
├──────────────────────────┤
│ - font: string           │ (Intrinsic State)
│   (SHARED, immutable)    │
│ - size: int              │ (SHARED, immutable)
│ - color: Color           │ (SHARED, immutable)
├──────────────────────────┤
│ + Display(x, y):void     │ (uses extrinsic state)
│   {                      │
│     render(x,y,          │
│       font,size,color)   │
│   }                      │
└──────────────────────────┘

Intrinsic vs Extrinsic State:

    Intrinsic (SHARED in Flyweight):
    ┌──────────────────────┐
    │ Font: Arial          │
    │ Size: 12             │
    │ Color: Black         │
    │ Style: Bold          │
    └──────────────────────┘
         ▲
         │ (stored once, reused)
         │
    ┌────┴────────────────┼─────────────────┐
    │                     │                 │
    Client 1         Client 2         Client 3
    Char: 'A'       Char: 'B'        Char: 'C'
    X: 10           X: 20            X: 30
    Y: 100          Y: 100           Y: 100
    (Extrinsic state = position + character)

Usage Example:

    FlyweightFactory factory;
    
    // Create characters with same font (shared flyweight)
    auto char_a = factory.GetFlyweight(
        {font: "Arial", size: 12, color: Black});
    char_a->Display(10, 100);  // 'A' at (10,100)
    
    auto char_b = factory.GetFlyweight(
        {font: "Arial", size: 12, color: Black});
    char_b->Display(20, 100);  // 'B' at (20,100)
    
    // char_a and char_b share same Flyweight object!

Memory Savings:

    Without Flyweight (1 Million Characters):
    ├─ 1,000,000 objects × 100 bytes = 100 MB
    
    With Flyweight (assuming 256 unique fonts):
    ├─ 256 flyweight objects × 100 bytes = 25.6 KB
    ├─ 1,000,000 clients × 16 bytes (x,y,char) = 16 MB
    └─ Total: ~16 MB (84% reduction!)

Factory Pool Management:

    Pool: {Key1 → Flyweight1, Key2 → Flyweight2, ...}
        │
        ├─ Always reuses existing objects
        └─ Thread-safe with synchronization

Thread Safety Consideration:

    FlyweightFactory (singleton or static)
    + synchronization (mutex)
    ├─ Lock when accessing pool
    └─ Ensure only one thread modifies pool
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
