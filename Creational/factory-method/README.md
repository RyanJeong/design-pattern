# Factory Method Pattern

## Pattern Overview

The **Factory Method Pattern** defines an interface for creating objects in a superclass, letting subclasses decide which class to instantiate. It provides a way to create objects without specifying their exact classes.

## Intent

- Create objects without specifying concrete classes
- Delegate object creation to subclasses
- Centralize object creation logic
- Make system independent of how objects are composed

## Structure

```text
┌────────────────────────────────────┐
│         Document                   │ ◄────── Abstract Product
├────────────────────────────────────┤
│                                    │
├────────────────────────────────────┤
│ + Open(): void = 0                 │
│ + Save(): void = 0                 │
│ + Close(): void = 0                │
└────────────────────────────────────┘
               ▲
               │ inherits
    ┌──────────┼──────────────────────────┐
    │          │                          │
┌──────────┐  ┌────────────┐  ┌─────────────┐
│ PDFDoc   │  │ WordDoc    │  │  TextDoc    │
├──────────┤  ├────────────┤  ├─────────────┤
│          │  │            │  │             │
├──────────┤  ├────────────┤  ├─────────────┤
│ + Open() │  │ + Open()   │  │ + Open()    │
│ + Save() │  │ + Save()   │  │ + Save()    │
│ + Close()│  │ + Close()  │  │ + Close()   │
└──────────┘  └────────────┘  └─────────────┘


┌─────────────────────────────────┐
│      Application                │ ◄────── Abstract Creator
├─────────────────────────────────┤
│                                 │
├─────────────────────────────────┤
│ + CreateDocument(): Document ◆  │ ◄── Factory Method (abstract)
│ + NewDocument(): void           │
│ + OpenFile(doc): void           │
└─────────────────────────────────┘
                              ▲
                              │ inherits
    ┌─────────────────────────┼──────────────────────────┐
    │                         │                          │
┌────────────────────────┐┌─────────────────────────┐┌─────────────────────────┐
│ PDFApplication         ││ WordApplication         ││ TextApplication         │
├────────────────────────┤├─────────────────────────┤├─────────────────────────┤
│                        ││                         ││                         │
├────────────────────────┤├─────────────────────────┤├─────────────────────────┤
│ + CreateDocument():    ││ + CreateDocument():     ││ + CreateDocument():     │
│   Document ◆           ││   Document ◆            ││   Document ◆            │
│   {                    ││   {                     ││   {                     │
│     return new PDFDoc()││     return new WordDoc()││     return new TextDoc()│
│   }                    ││   }                     ││   }                     │
└────────────────────────┘└─────────────────────────┘└─────────────────────────┘

Factory Method Pattern - Client Usage:

    Application* app;
    
    if (type == "PDF")
        app = new PDFApplication();
    else if (type == "Word")
        app = new WordApplication();
    else
        app = new TextApplication();
    
    Document* doc = app->CreateDocument();  ◄── Factory method called
    doc->Open();
    doc->Save();
    doc->Close();

Key Relationships:

    PDFApplication ◄────── inherits ────── Application
    WordApplication ◄────── inherits ────── Application
    TextApplication ◄────── inherits ────── Application
    
    PDFApplication creates ─────► PDFDoc (implements Document)
    WordApplication creates ──► WordDoc (implements Document)
    TextApplication creates ──► TextDoc (implements Document)
```

## Implementation Details

### Key Components

1. **Abstract Product (Document)**: Interface for objects
2. **Concrete Products**: Specific implementations (PDF, Word, Text)
3. **Abstract Creator (Application)**: Declares factory method
4. **Concrete Creators**: Implement factory method

### Factory Method

```cpp
virtual std::unique_ptr<Document> CreateDocument() const noexcept = 0;
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

## Key Classes

- **Document**: Abstract product interface
- **PdfDocument, WordDocument, TextDocument**: Concrete products
- **Application**: Abstract creator with factory method
- **PdfApplication, WordApplication, TextApplication**: Concrete creators

## Notes

- Factory method parameter can control product type
- Products share common interface
- Subclasses determine actual product type
- Decouples client from product classes
