# Abstract Factory Pattern

## Pattern Overview

The **Abstract Factory Pattern** provides an interface for creating families of related or dependent objects without specifying their concrete classes. It groups factory methods for multiple product families.

## Intent

- Create families of related objects
- Ensure products from same family are used together
- Isolate product creation from client code
- Make system independent of object creation

## Structure

```text
-------------------------------
|         UIFactory           | (Abstract Factory)
|-----------------------------|
| + CreateButton()            |
| + CreateCheckbox()          |
-------------------------------
  ^                ^
  |                |
 +----------+     +----------+
 | Windows  |     | Mac      |
 | Factory  |     | Factory  |
 +----------+     +----------+
  |                |
  +----+-----------+
       |
     +---------------------+
     | Button Checkbox     |
     | (Abstract Products) |
     +---------------------+
       |            |
+-----------+      +----------+
| (Windows) |      | (Mac)    |
| Products  |      | Products |
+-----------+      +----------+
```

## Implementation Details

### Key Components

1. **Abstract Factory (UIFactory)**: Interface for factories
2. **Concrete Factories (WindowsFactory, MacFactory)**: Create product families
3. **Abstract Products (Button, Checkbox)**: Interfaces for products
4. **Concrete Products**: Platform-specific implementations

### Ensure Product Family Consistency

```cpp
class UIFactory {
  virtual std::unique_ptr<Button> CreateButton() noexcept = 0;
  virtual std::unique_ptr<Checkbox> CreateCheckbox() noexcept = 0;
};
```

## Use Cases

- Cross-platform UI frameworks (Windows, Mac, Linux)
- Theme systems (Light, Dark themes with matching components)
- Database abstraction (MySQL, PostgreSQL, MongoDB)
- GUI toolkits with multiple looks and feels
- System abstraction layers

## Advantages

- Isolates concrete classes
- Ensures product family consistency
- Makes switching families easy
- Loose coupling between product families
- Follows Single Responsibility Principle

## Disadvantages

- Complex design with many classes
- Difficult to add new product types
- Code might be overkill for simple scenarios
- Challenging to extend with new products

## Related Patterns

- **Factory Method**: Base pattern for Abstract Factory
- **Builder**: Often combined for complex object creation
- **Singleton**: Factories often implemented as singletons
- **Facade**: Can use Abstract Factory internally

## Key Classes

- **UIFactory**: Abstract factory for UI components
- **WindowsFactory, MacFactory**: Concrete factories
- **Button, Checkbox**: Abstract product interfaces
- **WindowsButton, MacButton, WindowsCheckbox, MacCheckbox**: Concrete products
- **Application**: Client using factory

## Notes

- Each factory creates related product families
- Products from different factories are compatible
- Client doesn't know about concrete product types
- Easy to add new platforms by creating new factory
- Difficult to add new product types to existing families
