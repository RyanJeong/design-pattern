# Prototype Pattern

## Pattern Overview

The **Prototype Pattern** creates new objects by copying an existing object (prototype) rather than creating from scratch. It allows cloning objects without coupling to specific classes.

## Intent

- Create new objects by cloning prototypes
- Avoid subclassing for object creation
- Reduce initialization costs
- Support dynamic object creation
- Create object variations without subclassing

## Structure

```
┌──────────────┐
│    Shape     │ (Prototype Interface)
├──────────────┤
│ + clone()    │
│ + display()  │
└──────────────┘
       ▲
       │
   ┌───┴──────┐
   │          │
┌────────┐ ┌──────────┐
│ Circle │ │Rectangle │
└────────┘ └──────────┘

┌─────────────────┐
│ ShapeRegistry   │
├─────────────────┤
│ - prototypes    │
├─────────────────┤
│ + register()    │
│ + create_shape()│
└─────────────────┘
```

## Implementation Details

### Clone Method

```cpp
virtual std::unique_ptr<Shape> clone() const noexcept {
  return std::make_unique<Circle>(*this);  // Copy constructor
}
```

### Prototype Registry

Stores prototypes for reuse:

```cpp
class ShapeRegistry {
  std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes_;
  
  void register_prototype(const std::string& key, 
                         std::unique_ptr<Shape> shape) noexcept;
  
  std::unique_ptr<Shape> create_shape(const std::string& key) const;
};
```

## Use Cases

- Complex object cloning
- Avoiding expensive initialization
- Creating object variations quickly
- Undo/redo functionality
- Dynamic object creation
- Genetic algorithms
- Game AI cloning

## Advantages

✓ Avoids subclassing and complex creation logic
✓ Efficient object creation by cloning
✓ Dynamic object creation at runtime
✓ Reduces initialization overhead
✓ Flexibility in object variations

## Disadvantages

✗ Copy constructors must implement deep copying
✗ Circular reference handling is complex
✗ Cloning large objects can be expensive
✗ Not suitable for all object types
✗ Requires careful handling of pointers/references

## Related Patterns

- **Abstract Factory**: Can use prototypes
- **Factory Method**: Alternative for object creation
- **Builder**: Different approach to complex creation
- **Memento**: Can use prototype for state copying

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Prototype
```

## Expected Output

```
=== Creating Shapes from Prototypes ===
Circle: Default Circle (radius: 5)
Circle: Cloned Circle 2 (radius: 5)

Rectangle: Default Rectangle (10 x 20)
Rectangle: Cloned Rectangle 2 (10 x 20)
```

## Key Classes

- **Shape**: Abstract prototype with clone method
- **Circle, Rectangle**: Concrete prototypes
- **ShapeRegistry**: Registry managing prototypes

## Example Usage

```cpp
ShapeRegistry registry;

// Register prototypes
registry.register_prototype("circle", 
    std::make_unique<Circle>("Default Circle", 5.0));

// Clone prototypes
auto circle1 = registry.create_shape("circle");
auto circle2 = registry.create_shape("circle");
circle2->set_name("Cloned Circle");
```

## Deep vs Shallow Copy

- **Shallow Copy**: Copies references (shared state)
- **Deep Copy**: Copies actual data (independent state)

For Prototype pattern, deep copy is typically needed:

```cpp
Circle clone = prototype;  // Deep copy via copy constructor
```

## Notes

- Use default copy constructor if members are simple types
- Implement custom copy constructor for complex members
- Clone method should use copy constructor
- Registry pattern often accompanies Prototype
- Performance benefit depends on object complexity
