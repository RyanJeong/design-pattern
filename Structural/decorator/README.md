# Decorator Pattern

## Pattern Overview

The **Decorator Pattern** attaches additional responsibilities to an object dynamically, providing a flexible alternative to subclassing for extending functionality.

## Intent

- Add responsibilities to objects dynamically
- Provide alternative to subclassing for functionality extension
- Support feature combinations
- Maintain single responsibility

## Structure

```text
┌─────────────────────────────┐
│     Component               │ ◄────── Abstract Component
├─────────────────────────────┤
│                             │
├─────────────────────────────┤
│ + GetDescription(): string  │
│ + GetCost(): double = 0     │
│ + Operation(): void = 0     │
└─────────────────────────────┘
         ▲
         │ implements
    ┌────┴──────────────────────┐
    │                           │
┌──────────────────┐  ┌──────────────────────┐
│ SimpleCoffee     │  │ CoffeeDecorator      │
│(Concrete         │  │(Decorator Base)      │
│Component)        │  ├──────────────────────┤
├──────────────────┤  │ # component:         │
│                  │  │   unique_ptr         │
├──────────────────┤  ├──────────────────────┤
│GetDescription(): │  │ GetDescription():    │
│  "Coffee"        │  │   inherited from     │
│GetCost(): 5.0    │  │   component          │
│Operation()       │  │ GetCost(): double=0  │
└──────────────────┘  │ Operation(): void=0  │
                      └──────────────────────┘
                               ▲
                               │ inherits
           ┌───────────────────┼─────────────────────┐
           │                   │                     │
    ┌─────────────┐  ┌──────────────┐  ┌───────────────┐
    │MilkDecorator│  │SugarDecorator│  │ChocolateDecor │
    ├─────────────┤  ├──────────────┤  ├───────────────┤
    │ - component │  │ - component  │  │ - component   │
    ├─────────────┤  ├──────────────┤  ├───────────────┤
    │GetDescr():  │  │GetDescr():   │  │GetDescr():    │
    │ component + │  │ component +  │  │ component +   │
    │ " + Milk"   │  │ " + Sugar"   │  │ " + Chocolate"│
    │GetCost():   │  │GetCost():    │  │GetCost():     │
    │ comp + 2.0  │  │ comp + 1.5   │  │ comp + 3.0    │
    └─────────────┘  └──────────────┘  └───────────────┘

Stacking Decorators (Composition):

    ┌───────────────────────────────┐
    │ ChocolateDecorator            │
    │ "Coffee + Milk + Sugar +      │
    │  Chocolate"  (Cost: 12.5)     │
    │ component ────►               │
    └───────────────┬───────────────┘
                    │
              ┌─────v─────────────────┐
              │ SugarDecorator        │
              │ "Coffee + Milk +      │
              │  Sugar"  (Cost: 9.5)  │
              │ component ────►       │
              └──────┬────────────────┘
                     │
               ┌─────v───────────────┐
               │ MilkDecorator       │
               │ "Coffee + Milk"     │
               │ (Cost: 7.0)         │
               │ component ────►     │
               └──────┬──────────────┘
                      │
                ┌─────v──────────┐
                │ SimpleCoffee   │
                │ "Coffee"       │
                │ (Cost: 5.0)    │
                └────────────────┘

Usage Example:

    auto coffee = make_unique<ChocolateDecorator>(
        make_unique<SugarDecorator>(
            make_unique<MilkDecorator>(
                make_unique<SimpleCoffee>())));
    
    cout << coffee->GetDescription();  // "Coffee + Milk + Sugar + Chocolate"
    cout << coffee->GetCost();         // 12.5

Benefits:
    ✓ Add features dynamically at runtime
    ✓ Avoid subclass explosion (3 components × 7 features = 21 classes!)
    ✓ Single Responsibility Principle
    ✓ Combine features flexibly
```

## Implementation Details

### Decorator Base Class

```cpp
class CoffeeDecorator : public Component {
  std::unique_ptr<Component> component_;
  
  virtual std::string GetDescription() {
    return component_->GetDescription() + ", Extra";
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

## Key Classes

- **Component**: Component interface
- **SimpleCoffee**: Concrete component
- **CoffeeDecorator**: Decorator base
- **MilkDecorator, SugarDecorator, ChocolateDecorator**: Concrete decorators

## Example Usage

```cpp
auto coffee = std::make_unique<MilkDecorator>(
    std::make_unique<SimpleCoffee>());
std::cout << coffee->GetDescription() << " - $"
          << coffee->GetCost() << std::endl;
```

## Notes

- Provides alternative to subclassing
- More flexible for dynamic composition
- Can stack multiple decorators
- Same interface through abstraction
- Perfect for optional features
