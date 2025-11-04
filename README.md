# Design Patterns

A growing collection of design patterns implemented in C++14, starting with the Gang of Four (GoF) patterns and expanding with additional concurrency and architectural patterns.

## Pattern Categories

### [Behavioral Patterns](./Behavioral/)

Behavioral patterns define manners of communication between classes and objects. They help establish communication protocols and distribution of responsibilities among objects.

- [Chain of Responsibility](./Behavioral/chain-of-responsibility) - Pass requests along a chain of handlers
- [Command](./Behavioral/command) - Encapsulate requests as objects
- [Interpreter](./Behavioral/interpreter) - Define grammar for a language
- [Iterator](./Behavioral/iterator) - Access collection elements sequentially
- [Mediator](./Behavioral/mediator) - Reduce coupling between communicating classes
- [Memento](./Behavioral/memento) - Capture and restore object state
- [Observer](./Behavioral/observer) - Notify multiple objects about state changes
- [State](./Behavioral/state) - Alter behavior based on internal state
- [Strategy](./Behavioral/strategy) - Encapsulate interchangeable algorithms
- [Template Method](./Behavioral/template-method) - Define algorithm skeleton in base class
- [Visitor](./Behavioral/visitor) - Add operations to object structures

### [Creational Patterns](./Creational/)

Creational patterns provide ways to instantiate single objects or groups of related objects. They abstract the instantiation process to make systems independent of how objects are created.

- [Abstract Factory](./Creational/abstract-factory) - Create families of related objects
- [Builder](./Creational/builder) - Construct complex objects step by step
- [Factory Method](./Creational/factory-method) - Create objects without specifying concrete classes
- [Prototype](./Creational/prototype) - Create objects by cloning existing ones
- [Singleton](./Creational/singleton) - Ensure single instance of a class

### [Structural Patterns](./Structural/)

Structural patterns provide a manner to define relationships between classes or objects. They help ensure that changes in one part do not require changes in all other parts.

- [Adapter](./Structural/adapter) - Make incompatible interfaces work together
- [Bridge](./Structural/bridge) - Decouple abstraction from implementation
- [Composite](./Structural/composite) - Compose objects into tree structures
- [Decorator](./Structural/decorator) - Add functionality to objects dynamically
- [Facade](./Structural/facade) - Provide simplified interface to complex subsystem
- [Flyweight](./Structural/flyweight) - Share objects to reduce memory usage
- [Proxy](./Structural/proxy) - Control access to another object

### [Concurrency Patterns](./Concurrency/)

Concurrency patterns manage multi-threaded programming and synchronization between multiple threads. They provide solutions for coordinating thread execution and shared resource access.

- [Producer-Consumer](./Concurrency/producer-consumer) - Decouple production and consumption using shared buffer
- [ThreadPool](./Concurrency/threadpool) - Manage reusable worker threads for task execution

---

## Building and Running

Each pattern is self-contained with its own build configuration:

```bash
# Build all patterns in a category
cd <Category> && ./build_all.sh

# Build specific pattern
cd <Category>/<pattern-name>
mkdir -p build && cd build
cmake ..
make

# Run pattern demonstration
./<PatternName>
```

---

## Class Relationships

Understanding relationships between classes is fundamental to design patterns. The following UML relationships are commonly used:

### Inheritance (Generalization)

Inheritance represents an "is-a" relationship where a subclass is a specialized version of a parent class. The subclass inherits attributes and behaviors from the parent class.

**UML Notation:** Solid line with hollow arrowhead pointing to parent

```cpp
class Shape {
 public:
  virtual void draw() = 0;
  virtual ~Shape() = default;
};

class Rectangle : public Shape {
 public:
  void draw() override { /* ... */ }
};

class Circle : public Shape {
 public:
  void draw() override { /* ... */ }
};
```

**Key Characteristics:**

- Represents "is-a" relationship
- Subclass inherits all public and protected members
- Enables polymorphism through virtual functions
- Used in Template Method, Strategy, State patterns

### Association

Association represents a "knows-about" relationship between two classes, indicating that one class uses or interacts with another. This is the most general form of relationship.

**UML Notation:** Solid line connecting the two classes

```cpp
class Course {
  // ...
};

class Student {
 private:
  std::vector<Course*> courses_;

 public:
  void enroll(Course* course) { courses_.push_back(course); }
};
```

**Key Characteristics:**

- One object "knows about" another object
- Most general relationship type
- Objects can have independent lifespans
- Used in many patterns (Observer, Mediator, etc.)

#### Aggregation (Weak Composition)

Aggregation is a specialized form of association representing a "part-of" or "has-a" relationship where the contained object **can exist independently** of the container. This is sometimes called "weak composition."

**UML Notation:** Solid line with hollow diamond at the container end

```cpp
class Address {
 public:
  Address(const std::string& street, const std::string& city)
      : street_(street), city_(city) {}
 private:
  std::string street_;
  std::string city_;
};

class Student {
 private:
  Address* address_;  // Can exist independently

 public:
  Student(Address* addr) : address_(addr) {}
  ~Student() { /* address_ is not deleted */ }
};
```

**Key Characteristics:**

- "Has-a" relationship with shared lifetime management
- Contained object can exist without container
- Container does not own the contained object
- Typically uses raw pointers or shared ownership
- Used in Composite, Flyweight patterns

#### Composition (Strong Composition)

Composition is a stronger form of association representing an "owns-a" relationship where the contained object **cannot exist independently** of the container. When the container is destroyed, the contained objects are also destroyed.

**UML Notation:** Solid line with filled diamond at the container end

```cpp
class Point {
 public:
  Point(double x = 0, double y = 0) : x_(x), y_(y) {}
 private:
  double x_;
  double y_;
};

class Circle {
 private:
  Point center_;  // Owned by Circle, cannot exist independently
  double radius_;

 public:
  Circle(double x, double y, double r)
      : center_(x, y), radius_(r) {}
  ~Circle() { /* center_ is automatically destroyed */ }
};
```

**Key Characteristics:**

- Strongest form of "owns-a" relationship
- Contained object's lifetime is bound to container
- Container owns the contained object
- Typically uses member variables or unique_ptr
- Used in Composite, Decorator patterns

### Dependency

Dependency indicates that one class temporarily uses another class. The dependent class can function without the other, but may require it for specific operations. If the dependency class definition changes, it may affect the dependent class, but generally not vice versa.

**UML Notation:** Dashed line with hollow arrowhead

```cpp
class Movie {
 public:
  std::string getTitle() const { return title_; }
 private:
  std::string title_;
};

class Person {
 public:
  void watch(const Movie& movie) {
    std::cout << "Watching: " << movie.getTitle() << std::endl;
  }
};
```

**Key Characteristics:**

- "Uses" relationship, typically temporary
- Dependent class does not hold reference to dependency
- Often appears as function parameters
- Weakest form of coupling
- Common in Strategy, Command patterns

## UML Relationship Summary

| Relationship | Notation | Meaning | Lifetime | Ownership |
|--------------|----------|---------|----------|-----------|
| **Inheritance** | Solid line + hollow arrow | Is-a | Parent outlives children | N/A |
| **Association** | Solid line | Knows-about | Independent | None |
| **Aggregation** | Solid line + hollow diamond | Part-of (weak) | Independent | Shared |
| **Composition** | Solid line + filled diamond | Owns (strong) | Container owns | Container |
| **Dependency** | Dashed line + hollow arrow | Uses | Temporary | None |

---

## References

- **Gang of Four Design Patterns** - [BlackWasp](http://www.blackwasp.co.uk/gofpatterns.aspx)
  - Comprehensive overview of all 23 GoF design patterns with C# examples
- **C++ Design Patterns** - [Wikibooks](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns)
  - C++ specific implementation of design patterns
- **Modern C++ (C++14 and beyond)** - [cppreference.com](https://en.cppreference.com/)
- **PlantUML** - [plantuml.com](https://plantuml.com/)

---

## License

This project is licensed under the [Apache License](./LICENSE)
