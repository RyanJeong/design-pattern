# Composite Pattern

## Pattern Overview

The **Composite Pattern** allows you to compose objects into tree structures to represent part-whole hierarchies, letting clients treat individual objects and compositions uniformly.

## Intent

- Compose objects into tree structures
- Represent part-whole hierarchies
- Clients treat individual and composite objects uniformly
- Support recursive composition

## Structure

```
┌─────────────┐
│  Component  │ (Base)
├─────────────┤
│ + add()     │
│ + display() │
└─────────────┘
       ▲
       │
   ┌───┴──────┐
   │          │
┌────────┐ ┌──────────────┐
│ File   │ │ Directory    │ (Composite)
│(Leaf)  │ └──────────────┘
└────────┘   - children
             + add()
             + display()
```

## Implementation Details

### Component Interface

All objects (leaf and composite) implement common interface:

```cpp
class Component {
  virtual void display(int indent = 0) = 0;
  virtual void add(std::unique_ptr<Component> child);
};
```

### Tree Structure

```cpp
Directory root("root");
Directory home("home");
home.add(std::make_unique<File>("doc.txt", 2048));
root.add(std::move(home));
```

## Use Cases

- File system hierarchies
- GUI component hierarchies
- Organizational structures
- Menu systems
- Graphics scene graphs
- XML/JSON DOM trees

## Advantages

✓ Simplifies client code (uniform treatment)
✓ Easy to add new component types
✓ Natural representation of hierarchies
✓ Recursive composition support
✓ Follows Open/Closed Principle

## Disadvantages

✗ May be overly general for simple structures
✗ Type-specific operations difficult
✗ Performance overhead for large trees
✗ Complex design for simple use cases

## Related Patterns

- **Visitor**: Adds operations to composite structures
- **Iterator**: Traversing composite structures
- **Decorator**: Similar recursive composition
- **Chain of Responsibility**: Works with composite

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Composite
```

## Expected Output

```
=== File System Hierarchy ===
Directory: root/
  Directory: home/
    File: document.txt (2048 bytes)
    File: image.jpg (4096 bytes)
    Directory: Documents/
      File: resume.pdf (3072 bytes)
      File: letter.docx (1536 bytes)
  Directory: usr/
    Directory: bin/
      File: gcc (8192 bytes)
      File: make (4096 bytes)
```

## Key Classes

- **Component**: Base interface for all components
- **File**: Leaf node (no children)
- **Directory**: Composite node (has children)

## Example Usage

```cpp
auto root = std::make_unique<Directory>("root");
auto home = std::make_unique<Directory>("home");

home->add(std::make_unique<File>("doc.txt", 2048));
root->add(std::move(home));

root->display();
```

## Notes

- Works with any tree structure
- Leaf and composite have same interface
- Recursive composition natural
- Uniform treatment simplifies client code
- Perfect for recursive hierarchies
