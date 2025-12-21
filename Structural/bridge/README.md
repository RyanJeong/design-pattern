# Bridge Pattern

## Pattern Overview

The **Bridge Pattern** decouples an object's abstraction from its implementation so that the two can vary independently. It separates interface from implementation.

## Intent

- Decouple abstraction from implementation
- Avoid permanent binding between abstraction and implementation
- Allow both to vary independently
- Reduce class hierarchy complexity

## Structure

```text
┌─────────────────────────────────┐
│        Shape                    │ ◄────── Abstraction
├─────────────────────────────────┤
│ # renderer: shared_ptr<Renderer>│
├─────────────────────────────────┤
│ # Shape(renderer: shared_ptr)   │
│ + Draw(): void = 0              │
│ + Resize(pct): void = 0         │
└─────────────────────────────────┘
         ▲
         │ inherits
    ┌────┴──────────────────────┐
    │                           │
┌──────────────────┐  ┌──────────────────┐
│ Circle           │  │ Rectangle        │
│(Refined          │  │(Refined          │
│Abstraction)      │  │Abstraction)      │
├──────────────────┤  ├──────────────────┤
│ - radius: int    │  │ - width: int     │
│ - height: int    │  │ - height: int    │
├──────────────────┤  ├──────────────────┤
│ + Draw(): void   │  │ + Draw(): void   │
│   {renderer->    │  │   {renderer->    │
│   RenderCircle()}│  │   RenderRect()}  │
│ + Resize(pct)    │  │ + Resize(pct)    │
└──────────────────┘  └──────────────────┘
         │                    │
         │ uses               │ uses
         └────────┬───────────┘
                  │
                  v
    ┌──────────────────────────┐
    │    Renderer              │ ◄────── Implementer
    ├──────────────────────────┤
    │ + RenderCircle(): void=0 │
    │ + RenderRect(): void=0   │
    └──────────────────────────┘
              ▲
              │ implements
         ┌────┴──────────────────┐
         │                       │
    ┌───────────────┐  ┌──────────────────┐
    │VectorRenderer │  │RasterRenderer    │
    │(Concrete      │  │(Concrete         │
    │Implementer)   │  │Implementer)      │
    ├───────────────┤  ├──────────────────┤
    │               │  │                  │
    ├───────────────┤  ├──────────────────┤
    │RenderCircle() │  │RenderCircle()    │
    │  (vector way) │  │  (raster way)    │
    │RenderRect()   │  │RenderRect()      │
    │  (vector way) │  │  (raster way)    │
    └───────────────┘  └──────────────────┘

Bridge Pattern Concept:

    ┌─────────────────────────────┐
    │       Abstraction           │
    │   (Shape Hierarchy)         │
    └────────────┬────────────────┘
                 │
        ┌────────┴────────┐
        │  Implementation │
        │    Bridge       │
        └────────┬────────┘
                 │
    ┌────────────v────────────┐
    │    Implementation       │
    │   (Renderer Hierarchy)  │
    └─────────────────────────┘

Runtime Flexibility:

    Shape* circle = new Circle(new RasterRenderer());
    circle->Draw();  // Uses raster
    
    circle = new Circle(new VectorRenderer());
    circle->Draw();  // Uses vector
                     (without changing Shape code!)
```

## Implementation Details

### Bridge Connection

```cpp
class Shape {
  std::shared_ptr<Renderer> renderer_;
  
  virtual void Draw() {
    renderer_->RenderCircle(x, y, r);
  }
};
```

### Runtime Switching

Both abstraction and implementation can change:

```cpp
circle.SetRenderer(new RasterRenderer());
circle.Draw();  // Uses raster implementation
```

## Use Cases

- GUI frameworks (abstraction and platform implementations)
- Device drivers (abstract interface, platform-specific drivers)
- Graphics rendering (shape abstraction, renderer implementation)
- Database abstraction layers
- Logging systems

## Advantages

- Decouples abstraction from implementation
- Both can vary independently
- Reduces class proliferation
- Implementation can be selected at runtime
- Improves extensibility

## Disadvantages

- Increases complexity
- Adds extra abstraction level
- Performance overhead from indirection
- Not needed for simple cases

## Related Patterns

- **Adapter**: Similar structure, different intent
- **Abstract Factory**: Often used with Bridge
- **Strategy**: Different approach to flexibility
- **Decorator**: Different structural purpose

## Key Classes

- **Shape**: Abstraction base class
- **Circle, Rectangle**: Refined abstractions
- **Renderer**: Implementer interface
- **VectorRenderer, RasterRenderer**: Concrete implementers

## Notes

- Bridge pattern separates interface (abstraction) from implementation
- Perfect for frameworks with multiple platforms
- Reduces explosion of class hierarchy
- Implementation can be changed at runtime
- More complex than simple inheritance
