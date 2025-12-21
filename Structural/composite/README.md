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
┌──────────────────────────────┐
│      Component               │ ◄────── Abstract Base
├──────────────────────────────┤
│ - name: string               │
│ - size: int                  │
├──────────────────────────────┤
│ + GetName(): string          │
│ + GetSize(): int = 0         │
│ + Display(indent: int): void │
│   = 0                        │
│ + Add(component): void       │
│ + Remove(component): void    │
└──────────────────────────────┘
         ▲
         │ inherits
    ┌────┴──────────────────────┐
    │                           │
┌──────────────────────┐  ┌─────────────────────────┐
│ File                 │  │ Directory               │
│(Leaf)                │  │(Composite)              │
├──────────────────────┤  ├─────────────────────────┤
│ - name: string       │  │ - name: string          │
│ - size: int          │  │ - children: vector      │
├──────────────────────┤  │   <unique_ptr>          │
│ + GetName(): string  │  ├─────────────────────────┤
│ + GetSize(): int     │  │ + GetName(): string     │
│ + Display(indent)    │  │ + GetSize(): int        │
│   (prints file info) │  │   (sum of children)     │
│                      │  │ + Display(indent): void │
│                      │  │   {                     │
│                      │  │     for(each child)     │
│                      │  │       child->Display()  │
│                      │  │   }                     │
│                      │  │ + Add(child): void      │
│                      │  │ + Remove(child): void   │
└──────────────────────┘  └─────────────────────────┘

Tree Structure Example:

       ┌─────────────────┐
       │ Directory: root │
       │ Size: 8192 B    │
       └────────┬────────┘
                │
        ┌───────┴────────┐
        │                │
   ┌─────────┐      ┌──────────────┐
   │File:txt │      │Dir: home     │
   │Size: 512│      │Size: 4096    │
   └─────────┘      └──────┬───────┘
                           │
                    ┌──────┴──────┐
                    │             │
              ┌──────────┐   ┌──────────┐
              │File: doc │   │File: pic │
              │Size: 1024│   │Size: 2048│
              └──────────┘   └──────────┘

Composite Pattern Operations:

    Directory root("root");
    Directory home("home");
    
    home.Add(make_unique<File>("doc.txt", 1024));
    home.Add(make_unique<File>("pic.jpg", 2048));
    
    root.Add(make_unique<File>("readme", 512));
    root.Add(make_unique<Directory>("home", ...));
    
    root.Display(0);  // Recursively displays tree
    
    int total = root.GetSize();  // 512 + (1024+2048) = 3584

Uniform Interface:

    Component* item1 = new File("file.txt", 512);
    Component* item2 = new Directory("folder");
    
    item1->Display();  // Works for both leaf and composite
    item2->Display();  // Same interface!
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
