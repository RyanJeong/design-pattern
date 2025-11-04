# Flyweight Pattern

## Pattern Overview

The **Flyweight Pattern** reduces memory usage by sharing common state between many similar objects. It separates intrinsic state (shared) from extrinsic state (unique).

## Intent

- Reduce memory usage for objects with shared state
- Support large numbers of similar objects
- Share common data efficiently
- Trade memory for slight CPU overhead

## Structure

```
┌───────────────────────┐
│ FlyweightFactory      │
├───────────────────────┤
│ - flyweights (cache)  │
│ + get_flyweight()     │
└───────────────────────┘
           │
           │creates/returns
           ▼
┌──────────────────┐
│   Flyweight      │ (Intrinsic state)
├──────────────────┤
│ - font (shared)  │
│ - size (shared)  │
└──────────────────┘

Client provides Extrinsic state:
- Position (x, y)
- Character
```

## Implementation Details

### Intrinsic vs Extrinsic State

```cpp
// Intrinsic (shared in flyweight)
class CharacterFont {
  std::string font;  // shared
  int size;          // shared
};

// Extrinsic (provided by client)
void display(char character, int x, int y);
```

### Factory Caching

```cpp
class FlyweightFactory {
  std::map<Key, Flyweight*> pool;
  
  Flyweight& get(const Key& key) {
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

✓ Dramatically reduces memory usage
✓ Improves performance for large object counts
✓ Centralizes shared state management
✓ Efficient resource pooling

## Disadvantages

✗ Increased CPU overhead from lookup
✗ Thread safety complexity
✗ Difficult to debug
✗ Not beneficial for small object counts
✗ Separates intrinsic/extrinsic state

## Related Patterns

- **Factory Method**: Creates flyweights
- **Object Pool**: Similar resource pooling
- **Singleton**: Factory often singleton
- **Strategy**: Different approach to optimization

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Flyweight
```

## Expected Output

```
=== Flyweight Pattern: Font Sharing ===
Creating new font: Arial_12
Reusing font: Arial_12
Creating new font: Times_14
Creating new font: Arial_14

Displaying characters:
Char 'H' at (10,10) - Font: Arial, Size: 12
Char 'e' at (20,10) - Font: Arial, Size: 12
Char 'l' at (30,10) - Font: Times, Size: 14
Char 'l' at (40,10) - Font: Arial, Size: 14
Char 'o' at (50,10) - Font: Arial, Size: 12

Total unique fonts cached: 3
```

## Key Classes

- **CharacterFont**: Flyweight storing intrinsic state
- **CharacterFontFactory**: Factory managing flyweight pool

## Example Usage

```cpp
CharacterFontFactory factory;

auto arial_12 = factory.get_font("Arial", 12);
auto arial_12_reused = factory.get_font("Arial", 12);

arial_12->display('A', 10, 10);
arial_12_reused->display('B', 20, 10);
```

## Notes

- Significant memory savings for large object counts
- Factory maintains object pool
- Flyweights should be immutable
- Extrinsic state passed by client
- Client responsible for context
- Thread-safe factory recommended
