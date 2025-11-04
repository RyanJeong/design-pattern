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

```
┌───────────────┐
│   Client      │
└───────────────┘
        │
        │ uses
        ▼
┌───────────────┐
│    Image      │ (Subject)
├───────────────┤
│ + display()   │
└───────────────┘
       ▲
       │
   ┌───┴──────────┐
   │              │
┌──────────┐  ┌──────────────┐
│ RealImage│  │ ProxyImage   │
└──────────┘  └──────────────┘
              (lazy loads)
```

## Implementation Details

### Lazy Loading

```cpp
class ProxyImage : public Image {
  mutable std::unique_ptr<RealImage> real;
  
  void display() {
    if (!real)
      real = std::make_unique<RealImage>(filename);
    real->display();
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

✓ Delays expensive initialization
✓ Adds access control
✓ Enables logging/monitoring
✓ Hides network complexity
✓ Improves performance

## Disadvantages

✗ Added complexity
✗ Slightly slower access
✗ Thread safety concerns
✗ May complicate debugging
✗ Indirection overhead

## Related Patterns

- **Decorator**: Similar structure, different purpose
- **Adapter**: Converts interfaces
- **Factory**: Creates real objects
- **Singleton**: Often used with proxy

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Proxy
```

## Expected Output

```
=== Proxy Pattern: Lazy Image Loading ===

Proxies created (no real images loaded yet)

Calling display on image1:
Loading image: photo1.jpg (expensive operation)
Displaying image: photo1.jpg

Calling display on image1 again:
Displaying image: photo1.jpg

Calling display on image2:
Loading image: photo2.jpg (expensive operation)
Displaying image: photo2.jpg

Calling display on image3:
Loading image: photo3.jpg (expensive operation)
Displaying image: photo3.jpg
```

## Key Classes

- **Image**: Subject interface
- **RealImage**: Expensive real object
- **ProxyImage**: Proxy with lazy loading

## Example Usage

```cpp
ProxyImage image1("photo1.jpg");
ProxyImage image2("photo2.jpg");

image1.display();  // Loads image
image1.display();  // Reuses loaded image
image2.display();  // Loads different image
```

## Notes

- Virtual proxy for lazy initialization
- Protection proxy for access control
- Same interface as real object
- Transparent to client
- Excellent for expensive resources
- Works well with factory patterns
