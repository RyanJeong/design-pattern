# Bridge Pattern

## Pattern Overview

The **Bridge Pattern** decouples an object's abstraction from its implementation so that the two can vary independently. It separates interface from implementation.

## Intent

- Decouple abstraction from implementation
- Avoid permanent binding between abstraction and implementation
- Allow both to vary independently
- Reduce class hierarchy complexity

## Structure

```
┌─────────────────┐
│     Shape       │ (Abstraction)
├─────────────────┤
│ - renderer      │
└─────────────────┘
       ▲
       │
   ┌───┴──────┐
   │          │
┌────────┐ ┌──────────┐
│ Circle │ │Rectangle │ (Refined Abstractions)
└────────┘ └──────────┘

┌──────────────────┐
│   Renderer       │ (Implementer)
├──────────────────┤
│ + render_circle()│
│ + render_rect()  │
└──────────────────┘
       ▲
       │
   ┌───┴──────┐
   │          │
┌────────────┐ ┌──────────────┐
│ Vector     │ │ Raster       │
│ Renderer   │ │ Renderer     │
└────────────┘ └──────────────┘
```

## Implementation Details

### Bridge Connection

```cpp
class Shape {
  std::shared_ptr<Renderer> renderer_;
  
  virtual void draw() {
    renderer_->render_circle(x, y, r);
  }
};
```

### Runtime Switching

Both abstraction and implementation can change:

```cpp
circle.set_renderer(new RasterRenderer());
circle.draw();  // Uses raster implementation
```

## Use Cases

- GUI frameworks (abstraction and platform implementations)
- Device drivers (abstract interface, platform-specific drivers)
- Graphics rendering (shape abstraction, renderer implementation)
- Database abstraction layers
- Logging systems

## Advantages

✓ Decouples abstraction from implementation
✓ Both can vary independently
✓ Reduces class proliferation
✓ Implementation can be selected at runtime
✓ Improves extensibility

## Disadvantages

✗ Increases complexity
✗ Adds extra abstraction level
✗ Performance overhead from indirection
✗ Not needed for simple cases

## Related Patterns

- **Adapter**: Similar structure, different intent
- **Abstract Factory**: Often used with Bridge
- **Strategy**: Different approach to flexibility
- **Decorator**: Different structural purpose

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Bridge
```

## Expected Output

```
=== Vector Renderer ===
Rendering circle in vector: center(10,20), radius=5
Rendering rectangle in vector: pos(0,0), size=100x50

=== Raster Renderer ===
Rendering circle in raster: center(30,40), radius=8
Rendering rectangle in raster: pos(10,10), size=200x150

=== Runtime Renderer Switch ===
Rendering circle in vector: center(50,60), radius=3
Rendering circle in raster: center(50,60), radius=3
```

## Key Classes

- **Shape**: Abstraction base class
- **Circle, Rectangle**: Refined abstractions
- **Renderer**: Implementer interface
- **VectorRenderer, RasterRenderer**: Concrete implementers

## Example Usage

```cpp
auto vector_renderer = std::make_shared<VectorRenderer>();
Circle circle(vector_renderer, 10, 20, 5);
circle.draw();

circle.set_renderer(std::make_shared<RasterRenderer>());
circle.draw();  // Different implementation
```

## Notes

- Bridge pattern separates interface (abstraction) from implementation
- Perfect for frameworks with multiple platforms
- Reduces explosion of class hierarchy
- Implementation can be changed at runtime
- More complex than simple inheritance
