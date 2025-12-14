# Composite Pattern

## Pattern Overview

The **Composite Pattern** allows you to compose objects into tree structures to represent part-whole hierarchies, letting clients treat individual objects and compositions uniformly.

## Intent

- Compose objects into tree structures
- Represent part-whole hierarchies
- Clients treat individual and composite objects uniformly
- Support recursive composition

## Structure

```text
+-------------+
|  Component  | (Base)
|-------------|
| + Add()     |
| + Display() |
+-------------+
       ^
       |
   +---+------+ 
   |          |
 +--------+ +--------------+
 | File   | | Directory    | (Composite)
 |(Leaf)  | +--------------+
 +--------+   - children
              + Add()
              + Display()
```

## Implementation Details

### Component Interface

All objects (leaf and composite) implement common interface:

```cpp
class Component {
  virtual void Display(int indent = 0) = 0;
  virtual void Add(std::unique_ptr<Component> child);
};
```

### Tree Structure

```cpp
Directory root("root");
Directory home("home");
home.Add(std::make_unique<File>("doc.txt", 2048));
root.Add(std::move(home));
```

## Use Cases

- File system hierarchies
- GUI component hierarchies
- Organizational structures
- Menu systems
- Graphics scene graphs
- XML/JSON DOM trees

## Advantages

- Simplifies client code (uniform treatment)
- Easy to add new component types
- Natural representation of hierarchies
- Recursive composition support
- Follows Open/Closed Principle

## Disadvantages

- May be overly general for simple structures
- Type-specific operations difficult
- Performance overhead for large trees
- Complex design for simple use cases

## Related Patterns

- **Visitor**: Adds operations to composite structures
- **Iterator**: Traversing composite structures
- **Decorator**: Similar recursive composition
- **Chain of Responsibility**: Works with composite

## Key Classes

- **Component**: Base interface for all components
- **File**: Leaf node (no children)
- **Directory**: Composite node (has children)

## Notes

- Works with any tree structure
- Leaf and composite have same interface
- Recursive composition natural
- Uniform treatment simplifies client code
- Perfect for recursive hierarchies

## C++14 Features

- Move semantics: Component/File/Directory constructors accept name parameters by-value and move them into members (`Component(std::string name) : name_(std::move(name))`). This enables callers to pass temporaries or `std::move` existing strings to reduce copies.
