# Builder Pattern

## Pattern Overview

The **Builder Pattern** separates the construction of a complex object from its representation, allowing step-by-step construction and different representations of the same object.

## Intent

- Separate complex object construction from representation
- Provide step-by-step construction process
- Support construction of different representations
- Use fluent interface for readable code

## Structure

```text
-----------------------
|     Computer         | (Product)
|----------------------|
| - cpu                |
| - ram                |
| - storage            |
| - gpu                |
-----------------------
      ^
      |
-----------------------
| ComputerBuilder      | (Abstract Builder)
|----------------------|
| + set_cpu()          |
| + set_ram()          |
| + build()            |
-----------------------
      ^
      |
    +----+----+
    |         |
 +---------+ +-------------+
 | Gaming  | | Workstation |
 | Builder | | Builder     |
 +---------+ +-------------+
```

## Implementation Details

### Builder Pattern Components

1. **Product (Computer)**: Complex object being built
2. **Abstract Builder (ComputerBuilder)**: Interface for construction steps
3. **Concrete Builders**: Specific implementations (Gaming, Workstation)

### Fluent Interface

Methods return reference to builder for method chaining:

```cpp
Computer pc = builder
    .set_cpu("Intel Core i9")
    .set_ram("32GB DDR5")
    .set_storage("2TB SSD")
    .set_gpu("RTX 4090")
    .Build();
```

## Use Cases

- Object configuration (UI components, HTTP requests)
- Complex data structures (documents, configurations)
- Constructors with many optional parameters
- Immutable objects
- Object creation with validation

## Advantages

- Separates construction from representation
- Flexible step-by-step construction
- Same builder can build different representations
- Better code readability with fluent interface
- Immutable objects after construction

## Disadvantages

- More classes needed
- Increased memory usage
- Not beneficial for simple objects
- Requires mutable state during construction

## Related Patterns

- **Abstract Factory**: Often combined with Builder
- **Factory Method**: Alternative for object creation
- **Composite**: Can use Builder for construction

## Key Classes

- **Computer**: Product class with CPU, RAM, Storage, GPU
- **ComputerBuilder**: Abstract builder with fluent interface
- **GamingComputerBuilder**: Builds gaming-optimized computers
- **WorkstationBuilder**: Builds workstation computers

## Notes

- Fluent interface makes complex construction readable
- Builders can have default configurations
- Method chaining improves API design

## C++14 Features

- Move semantics: Builder setters and the `Computer` constructor accept
  parameters by-value and move them into internal members. The `Build()`
  implementation moves the builder's internal strings into the constructed
  `Computer` to avoid unnecessary copies when calling `Build()`.
- Consider immutability of final product
