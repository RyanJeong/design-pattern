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
┌──────────────────────────────┐
│      Computer                │ ◄────── Product
├──────────────────────────────┤
│ - cpu: string                │
│ - ram: string                │
│ - storage: string            │
│ - gpu: string                │
├──────────────────────────────┤
│ + GetCPU(): string           │
│ + GetRAM(): string           │
│ + GetStorage(): string       │
│ + GetGPU(): string           │
└──────────────────────────────┘

┌────────────────────────────────┐
│   ComputerBuilder              │ ◄────── Abstract Builder
├────────────────────────────────┤
│ # computer: Computer           │
├────────────────────────────────┤
│ + SetCPU(cpu): Builder&        │
│ + SetRAM(ram): Builder&        │
│ + SetStorage(storage): Builder&│
│ + SetGPU(gpu): Builder&        │
│ + Build(): Computer            │
└────────────────────────────────┘
         ▲
         │ inherits
    ┌────┴──────────────────────────────┐
    │                                   │
┌────────────────────────────┐  ┌──────────────────────────┐
│ GamingComputerBuilder      │  │WorkstationComputerBuilder│
├────────────────────────────┤  ├──────────────────────────┤
│ - computer: Computer       │  │ - computer: Computer     │
├────────────────────────────┤  ├──────────────────────────┤
│ + SetCPU(...): Builder&    │  │ + SetCPU(...): Builder&  │
│   (Gaming CPU)             │  │   (Workstation CPU)      │
│ + SetRAM(...): Builder&    │  │ + SetRAM(...): Builder&  │
│   (High RAM)               │  │   (High RAM)             │
│ + SetStorage(...): Builder&│  │ + SetStorage(...):Builder│
│   (High-speed SSD)         │  │   (Enterprise storage)   │
│ + SetGPU(...): Builder&    │  │ + SetGPU(...): Builder&  │
│   (Gaming GPU)             │  │   (Professional GPU)     │
│ + Build(): Computer        │  │ + Build(): Computer      │
└────────────────────────────┘  └──────────────────────────┘

Fluent Interface (Method Chaining):

    GamingComputerBuilder builder;
    Computer pc = builder
        .SetCPU("Intel Core i9-13900K")
        .SetRAM("64GB DDR5")
        .SetStorage("2TB NVMe SSD")
        .SetGPU("RTX 4090")
        .Build();

Step-by-step Construction:
    
    Builder Step 1 ─► Builder Step 2 ─► Builder Step 3 ─► Builder Step 4 ─► Build()
    (SetCPU)         (SetRAM)          (SetStorage)       (SetGPU)          (Product)
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
