# Facade Pattern

## Pattern Overview

The **Facade Pattern** provides a unified, simplified interface to a set of interfaces in a subsystem, making it easier to use.

## Intent

- Provide simplified interface to complex subsystem
- Reduce complexity for client code
- Decouple client from subsystem components
- Provide common operations

## Structure

```text
┌──────────────────────────────────────┐
│       ComputerFacade                 │ ◄────── Facade
├──────────────────────────────────────┤
│ - cpu: CPU                           │
│ - memory: Memory                     │
│ - hard_drive: HardDrive              │
├──────────────────────────────────────┤
│ + Start(): void                      │
│   {                                  │
│     hd.Read("boot.bin")              │
│     memory.Load(data)                │
│     cpu.Freeze()                     │
│     cpu.Execute(0)                   │
│   }                                  │
│ + Shutdown(): void                   │
│   {                                  │
│     cpu.Halt()                       │
│     memory.Release()                 │
│   }                                  │
└──────────────────────────────────────┘
    │         │          │
    │ uses    │ uses     │ uses
    v         v          v
┌────────┐  ┌─────────┐  ┌──────────┐
│  CPU   │  │ Memory  │  │HardDrive │ ◄────── Subsystems
├────────┤  ├─────────┤  ├──────────┤
│        │  │         │  │          │
├────────┤  ├─────────┤  ├──────────┤
│Freeze()│  │Load()   │  │Read()    │
│Execute()  │Release()│  │Write()   │
│Halt()  │  │         │  │          │
└────────┘  └─────────┘  └──────────┘

Complex Subsystem Without Facade:

    CPU cpu;
    Memory memory;
    HardDrive hd;
    
    hd.Read("boot.bin");
    memory.Load(boot_data);
    cpu.Freeze();
    cpu.Execute(0);
    // ... complex initialization

Simplified With Facade:

    ComputerFacade computer;
    computer.Start();  // One simple call!

Facade Benefits:

    Client Code
        │
        │ uses (simple interface)
        │
        ▼
    ┌──────────┐
    │ Facade   │ ◄── Single Entry Point
    └─────┬────┘
          │
       ┌──┼──┬──────┐
       │  │  │      │
       ▼  ▼  ▼      ▼
      Component 1,2,3,4,5...  (Complex subsystems hidden)

Layer Separation:

    ┌─────────────────────┐
    │  Client Code        │
    │  (Simple Interface) │
    └──────────┬──────────┘
               │
    ┌──────────▼──────────┐
    │ Facade Layer        │ ◄── Hides Complexity
    └──────────┬──────────┘
               │
    ┌──────────▼──────────┐
    │ Subsystem Layer     │ (Complex Implementation)
    │ (CPU, Memory, HD...)│
    └─────────────────────┘
```

## Implementation Details

### Simplified Interface

```cpp
class ComputerFacade {
  CPU cpu_;
  Memory memory_;
  HardDrive disk_;
  
  void Start() {
    disk.Read("boot.bin");
    memory.Load(data);
    cpu.Freeze();
    cpu.Execute(0);
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

## Key Classes

- **ComputerFacade**: Facade providing simplified interface
- **CPU, Memory, HardDrive**: Subsystem components

## Notes

- Simplifies complex systems for clients
- Single entry point for subsystem
- Clients don't need to know subsystem details
- Good for initialization sequences
- Often used in frameworks
