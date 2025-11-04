# Factory Method Pattern

## Pattern Overview

The **Factory Method Pattern** defines an interface for creating objects in a superclass, letting subclasses decide which class to instantiate. It provides a way to create objects without specifying their exact classes.

## Intent

- Create objects without specifying concrete classes
- Delegate object creation to subclasses
- Centralize object creation logic
- Make system independent of how objects are composed

## Structure

```
----------------------
|  Document           | (Abstract Product)
|---------------------|
| + open()            |
| + save()            |
| + close()           |
---------------------+
             ^
             |
     +---+------+ +---------+
     |          | |         |
 +------+ +--------+ +--------+
 | PDF  | | Word   | | Text   |
 | Doc  | | Doc    | | Doc    |
 +------+ +--------+ +--------+

------------------------
| Application          | (Abstract Creator)
|----------------------|
| + create_document()  |
| + new_document()     |
----------------------+
             ^
             |
     +---+-----+ +--------+ +--------+
     |         | |        | |        |
 +--------+ +--------+ +--------+
 | PDF    | | Word   | | Text   |
 | App    | | App    | | App    |
 +--------+ +--------+ +--------+
```

## Implementation Details

### Key Components

1. **Abstract Product (Document)**: Interface for objects
2. **Concrete Products**: Specific implementations (PDF, Word, Text)
3. **Abstract Creator (Application)**: Declares factory method
4. **Concrete Creators**: Implement factory method

### Factory Method

```cpp
virtual std::unique_ptr<Document> create_document() const noexcept = 0;
```

## Use Cases

- Document processing (different formats)
- UI framework (different platforms)
- Database connections (different types)
- Logging implementations (different outputs)
- Data parsing (different formats)

## Advantages

- Loose coupling between creator and product
- Follows Open/Closed Principle
- Centralized object creation
- Easy to add new product types
- Flexibility in product selection

## Disadvantages

- Additional classes needed
- Code complexity increased
- Overkill for simple objects
- May create unnecessary abstraction

## Related Patterns

- **Abstract Factory**: Combines multiple factory methods
- **Template Method**: Often used with Factory Method
- **Singleton**: Factory method can return singleton
- **Prototype**: Alternative for object creation

## Compilation & Execution

```bash
mkdir -p build
cd build
cmake ..
make
./FactoryMethod
```

## Expected Output

```
=== PDF Application ===
Opening PDF document...
Saving PDF document...
Closing PDF document...

=== Word Application ===
Opening Word document...
Saving Word document...
Closing Word document...

=== Text Application ===
Opening Text document...
Saving Text document...
Closing Text document...
```

## Key Classes

- **Document**: Abstract product interface
- **PdfDocument, WordDocument, TextDocument**: Concrete products
- **Application**: Abstract creator with factory method
- **PdfApplication, WordApplication, TextApplication**: Concrete creators

## Example Usage

```cpp
// Create PDF application
PdfApplication pdf_app;
pdf_app.new_document();  // Creates PDF document

// Create Word application
WordApplication word_app;
word_app.new_document();  // Creates Word document
```

## Notes

- Factory method parameter can control product type
- Products share common interface
- Subclasses determine actual product type
- Decouples client from product classes
