# Builder Pattern

## Pattern Overview

The **Builder Pattern** separates the construction of a complex object from its representation, allowing step-by-step construction and different representations of the same object.

## Intent

- Separate complex object construction from representation
- Provide step-by-step construction process
- Support construction of different representations
- Use fluent interface for readable code

## Structure

```
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
    .build();
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

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Builder
```

## Expected Output

```
=== Gaming PC ===
Computer Configuration:
  CPU: Intel Core i9-12900K
  RAM: 32GB DDR5
  Storage: 2TB NVMe SSD
  GPU: RTX 4090

=== Workstation ===
Computer Configuration:
  CPU: Intel Xeon
  RAM: 64GB DDR4
  Storage: 2TB NVMe SSD
  GPU: RTX A6000

=== Custom PC ===
Computer Configuration:
  CPU: AMD Ryzen 7
  RAM: 16GB DDR4
  Storage: 512GB SSD
  GPU: RTX 3060
```

## Key Classes

- **Computer**: Product class with CPU, RAM, Storage, GPU
- **ComputerBuilder**: Abstract builder with fluent interface
- **GamingComputerBuilder**: Builds gaming-optimized computers
- **WorkstationBuilder**: Builds workstation computers

## Example Usage

```cpp
// Gaming PC builder
GamingComputerBuilder builder;
Computer pc = builder
    .set_cpu("Intel Core i9-12900K")
    .set_ram("32GB DDR5")
    .build();

// Custom builder
ComputerBuilder custom;
Computer custom_pc = custom
    .set_cpu("AMD Ryzen 7")
    .set_ram("16GB")
    .build();
```

## Notes

- Fluent interface makes complex construction readable
- Builders can have default configurations
- Method chaining improves API design
- Consider immutability of final product
