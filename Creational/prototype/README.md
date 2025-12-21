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

```text
┌───────────────────────────────┐
│      Shape                    │ ◄────── Prototype Interface
├───────────────────────────────┤
│ - x: int                      │
│ - y: int                      │
├───────────────────────────────┤
│ + Clone(): unique_ptr = 0     │
│ + Display(): void = 0         │
└───────────────────────────────┘
         ▲
         │ inherits
    ┌────┴──────────────────┐
    │                       │
┌──────────────┐  ┌──────────────────┐
│ Circle       │  │ Rectangle        │
├──────────────┤  ├──────────────────┤
│ - radius: int│  │ - width: int     │
│              │  │ - height: int    │
├──────────────┤  ├──────────────────┤
│ + Clone():   │  │ + Clone():       │
│   unique_ptr │  │   unique_ptr     │
│ + Display()  │  │ + Display()      │
└──────────────┘  └──────────────────┘

┌──────────────────────────────────────┐
│    ShapeRegistry                     │ ◄────── Prototype Registry
├──────────────────────────────────────┤
│ - prototypes:                        │
│   map<string, unique_ptr<Shape>>     │
├──────────────────────────────────────┤
│ + RegisterPrototype(                 │
│     key: string,                     │
│     shape: unique_ptr): void         │
│                                      │
│ + CreateShape(key: string):          │
│   unique_ptr<Shape>                  │
│   {                                  │
│     return prototypes[key]->Clone()  │
│   }                                  │
└──────────────────────────────────────┘

Clone Process:

    Prototype Pattern Advantages:
    
    Shape* original = new Circle(50, 50, 20);
    Shape* clone1 = original->Clone();  ◄── No need for subclass knowledge
    Shape* clone2 = original->Clone();  ◄── Creates independent copies
    
    ShapeRegistry registry;
    registry.RegisterPrototype("circle", 
                              make_unique<Circle>(0, 0, 5));
    
    auto shape = registry.CreateShape("circle");  ◄── Clones from registry
```

## Implementation Details

### Clone Method

```cpp
virtual std::unique_ptr<Shape> Clone() const noexcept {
  return std::make_unique<Circle>(*this);  // Copy constructor
}
```

### Prototype Registry

Stores prototypes for reuse:

```cpp
class ShapeRegistry {
  std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes_;
  
  void RegisterPrototype(const std::string& key, 
                         std::unique_ptr<Shape> shape) noexcept;
  
  std::unique_ptr<Shape> CreateShape(const std::string& key) const;
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

- Avoids subclassing and complex creation logic
- Efficient object creation by cloning
- Dynamic object creation at runtime
- Reduces initialization overhead
- Flexibility in object variations

## Disadvantages

- Copy constructors must implement deep copying
- Circular reference handling is complex
- Cloning large objects can be expensive
- Not suitable for all object types
- Requires careful handling of pointers/references

## Related Patterns

- **Abstract Factory**: Can use prototypes
- **Factory Method**: Alternative for object creation
- **Builder**: Different approach to complex creation
- **Memento**: Can use prototype for state copying

## Key Classes

- **Shape**: Abstract prototype with clone method
- **Circle, Rectangle**: Concrete prototypes
- **ShapeRegistry**: Registry managing prototypes

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

## C++14 Features

- Move semantics: Constructors and setters in the example accept string
  parameters by-value and move them into members (e.g. `Shape(std::string name)`
  and `set_name(std::string name)`). This enables callers to pass temporaries
  or `std::move` existing strings to avoid unnecessary copies.
