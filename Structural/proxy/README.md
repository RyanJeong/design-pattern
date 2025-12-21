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
┌──────────────────────────┐
│      Image               │ ◄────── Subject Interface
├──────────────────────────┤
│                          │
├──────────────────────────┤
│ + Display(): void = 0    │
│ + GetWidth(): int = 0    │
│ + GetHeight(): int = 0   │
└──────────────────────────┘
         ▲
         │ implements
    ┌────┴──────────────────────┐
    │                           │
┌──────────────────┐  ┌───────────────────────┐
│ RealImage        │  │ ProxyImage            │
│(Real Object -    │  │(Proxy - Placeholder)  │
│Expensive)        │  ├───────────────────────┤
├──────────────────┤  │ - real: unique_ptr    │
│ - filename       │  │   <RealImage>         │
│ - image_data     │  │   (lazy initialized)  │
│   (large!)       │  │ - filename: string    │
├──────────────────┤  │ - width: int          │
│ + Display()      │  │ - height: int         │
│   (load & draw)  │  ├───────────────────────┤
│ + GetWidth()     │  │ + Display(): void     │
│ + GetHeight()    │  │   {                   │
│                  │  │     if(!real)         │
│                  │  │       real = new Real │
│                  │  │     real->Display()   │
│                  │  │   }                   │
│                  │  │ + GetWidth(): int     │
│                  │  │ + GetHeight(): int    │
└──────────────────┘  └───────────────────────┘

Lazy Loading Sequence:

    Client Code
        │
        │ img->Display()
        │
        v
    ┌─────────────────┐
    │ ProxyImage      │
    │ Display()       │
    └────────┬────────┘
             │
      ┌──────v───────┐
      │ real == null?│
      └──┬───────────┘
         │ Yes
         v
    ┌────────────────────┐
    │ Create RealImage   │
    │ (expensive!)       │
    │ - Load from disk   │
    │ - Decompress       │
    │ - Allocate memory  │
    └────────┬───────────┘
             │
         ┌───v────────────┐
         │ Call           │
         │ real->Display()│
         └────────────────┘

Proxy Types:

    1. Virtual Proxy (Lazy Loading)
       └─ Delays expensive object creation
    
    2. Protection Proxy (Access Control)
       └─ Checks permissions before delegating
    
    3. Logging Proxy
       └─ Logs all method calls
    
    4. Remote Proxy
       └─ Communicates over network
    
    5. Smart Proxy
       └─ Reference counting, caching, etc.

Usage Example:

    Image* img = new ProxyImage("large_photo.jpg");
    
    // Image not loaded yet (proxy only)
    
    img->Display();  // Now loads RealImage from disk
                     // (lazy initialization)
    
    // Subsequent calls use cached RealImage
    img->Display();  // Fast! (already loaded)

Benefits:

    ✓ Delays expensive initialization
    ✓ Adds access control
    ✓ Enables logging/monitoring
    ✓ Simplifies resource management
    ✓ Network transparency
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
