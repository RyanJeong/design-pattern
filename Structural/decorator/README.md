# Decorator Pattern

## Pattern Overview

The **Decorator Pattern** attaches additional responsibilities to an object dynamically, providing a flexible alternative to subclassing for extending functionality.

## Intent

- Add responsibilities to objects dynamically
- Provide alternative to subclassing for functionality extension
- Support feature combinations
- Maintain single responsibility

## Structure

```
+--------------+
|  Component   | (Base Interface)
|--------------|
| + operation()|
+--------------+
     ^
     |
   +---+----------+
   |              |
 +--------+  +--------------+
 | Simple |  |  Decorator   |
 |Component|  |--------------|
 +--------+  | - component  |
       | + operation()|
       +--------------+
          ^
          |
         +----+----+----+--------+
         |         |    |        |
       +--------+ +------+ +---------+ +-------+
       | Milk   | | Sugar| |Chocolate| | ...   |
       +--------+ +------+ +---------+ +-------+
```

## Implementation Details

### Decorator Base Class

```cpp
class CoffeeDecorator : public Component {
  std::unique_ptr<Component> component_;
  
  virtual std::string get_description() {
    return component_->get_description() + ", Extra";
  }
};
```

### Stacking Decorators

```cpp
auto coffee = std::make_unique<ChocolateDecorator>(
    std::make_unique<SugarDecorator>(
        std::make_unique<MilkDecorator>(
            std::make_unique<SimpleCoffee>())));
```

## Use Cases

- Adding features dynamically (UI components)
- Text formatting (bold, italic, underline)
- Stream processing (compression, encryption)
- GUI components with additional features
- Logging/authentication wrappers

## Advantages

- More flexible than inheritance
- Single Responsibility Principle
- Combine features at runtime
- Avoid class proliferation
- Same interface maintained

## Disadvantages

- Creates many small objects
- Complex ordering of decorators
- Difficult to remove specific decorator
- Performance overhead
- Harder to understand than inheritance

## Related Patterns

- **Adapter**: Different purpose, wraps object
- **Strategy**: Different behavior selection
- **Composite**: Tree of decorators
- **Proxy**: Controls access

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Decorator
```

## Expected Output

```
=== Coffee Ordering ===
Simple Coffee - $2
Simple Coffee, Milk - $2.5
Simple Coffee, Milk, Sugar - $2.75
Simple Coffee, Milk, Sugar, Chocolate - $3.5
```

## Key Classes

- **Component**: Component interface
- **SimpleCoffee**: Concrete component
- **CoffeeDecorator**: Decorator base
- **MilkDecorator, SugarDecorator, ChocolateDecorator**: Concrete decorators

## Example Usage

```cpp
auto coffee = std::make_unique<MilkDecorator>(
    std::make_unique<SimpleCoffee>());
std::cout << coffee->get_description() << " - $"
          << coffee->get_cost() << std::endl;
```

## Notes

- Provides alternative to subclassing
- More flexible for dynamic composition
- Can stack multiple decorators
- Same interface through abstraction
- Perfect for optional features
