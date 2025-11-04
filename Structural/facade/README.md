# Facade Pattern

## Pattern Overview

The **Facade Pattern** provides a unified, simplified interface to a set of interfaces in a subsystem, making it easier to use.

## Intent

- Provide simplified interface to complex subsystem
- Reduce complexity for client code
- Decouple client from subsystem components
- Provide common operations

## Structure

```
+--------------------+
|    Facade          |
|--------------------|
| - cpu, memory, hd  |
| + start()          |
| + shutdown()       |
+--------------------+
  |      |      |
  v      v      v
 +------+ +--------+ +----------+
 | CPU  | | Memory | | HardDrive| (Subsystems)
 +------+ +--------+ +----------+
```

## Implementation Details

### Simplified Interface

```cpp
class ComputerFacade {
  CPU cpu;
  Memory memory;
  HardDrive disk;
  
  void start() {
    disk.read("boot.bin");
    memory.load(data);
    cpu.freeze();
    cpu.execute(0);
  }
};
```

## Use Cases

- System initialization (complex startup)
- Database connections
- Payment processing systems
- Library APIs
- Framework initialization
- Hardware abstraction

## Advantages

- Simplifies client code
- Decouples client from complex subsystems
- Reduces dependencies
- Promotes subsystem independence
- Eases maintenance

## Disadvantages

- Facade can become too large
- May hide important details
- Can limit flexibility
- May not be needed for simple systems
- Additional abstraction layer

## Related Patterns

- **Adapter**: Different purpose, simplifies interface
- **Bridge**: Separates abstraction from implementation
- **Composite**: Can work with facade
- **Abstract Factory**: Can use facade

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./Facade
```

## Expected Output

```
=== Computer Facade ===
Computer starting...
Reading file: boot.bin
Reading file: os.bin
Loading program: Program code from os.bin
Freezing CPU...
Jumping to location: 0
Executing from location: 0
Computer ready.

Computer shutting down...
Freezing CPU...
Computer off.
```

## Key Classes

- **ComputerFacade**: Facade providing simplified interface
- **CPU, Memory, HardDrive**: Subsystem components

## Example Usage

```cpp
ComputerFacade computer;
computer.start();   // Complex operation simplified
computer.shutdown();
```

## Notes

- Simplifies complex systems for clients
- Single entry point for subsystem
- Clients don't need to know subsystem details
- Good for initialization sequences
- Often used in frameworks
