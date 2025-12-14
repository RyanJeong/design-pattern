# Proxy Pattern

## Pattern Overview

The **Proxy Pattern** provides a surrogate or placeholder for another object to control access to it. It acts as an intermediary between client and real object.

## Intent

- Provide placeholder for expensive object
- Delay creation until needed (lazy loading)
- Control access to real object
- Add access control or logging
- Manage resource-intensive operations

## Structure

```text
 +---------------+
 |   Client      |
 +---------------+
   |
   | uses
   v
 +---------------+
 |    Image      | (Subject)
 |---------------|
 | + Display()   |
 +---------------+
   ^
   |
   +-------------+
   |             |
 +----------+  +--------------+
 | RealImage|  | ProxyImage   |
 +----------+  +--------------+
         (lazy loads)
```

## Implementation Details

### Lazy Loading

```cpp
class ProxyImage : public Image {
  mutable std::unique_ptr<RealImage> real_;
  
  void Display() {
    if (!real_)
      real_ = std::make_unique<RealImage>(filename_);
    real->Display();
  }
};
```

## Use Cases

- Lazy initialization (expensive objects)
- Access control (permissions checking)
- Logging/monitoring
- Caching
- Smart references
- Resource pooling
- Network operations (RPC)

## Proxy Types

1. **Virtual Proxy**: Lazy initialization
2. **Protection Proxy**: Access control
3. **Logging Proxy**: Track operations
4. **Remote Proxy**: Network access
5. **Smart Proxy**: Additional operations

## Advantages

- Delays expensive initialization
- Adds access control
- Enables logging/monitoring
- Hides network complexity
- Improves performance

## Disadvantages

- Added complexity
- Slightly slower access
- Thread safety concerns
- May complicate debugging
- Indirection overhead

## Related Patterns

- **Decorator**: Similar structure, different purpose
- **Adapter**: Converts interfaces
- **Factory**: Creates real objects
- **Singleton**: Often used with proxy

## Key Classes

- **Image**: Subject interface
- **RealImage**: Expensive real object
- **ProxyImage**: Proxy with lazy loading

## Notes

- Virtual proxy for lazy initialization
- Protection proxy for access control
- Same interface as real object
- Transparent to client
- Excellent for expensive resources
- Works well with factory patterns

## C++14 Features

- Move semantics: `RealImage` and `ProxyImage` constructors accept the
  filename parameter by-value and move it into the object's member. This
  enables callers to pass temporaries or `std::move`'d strings without extra
  copies during construction (useful when filenames are generated at runtime).
