# Iterator Pattern

## Overview

The Iterator pattern is a behavioral design pattern that provides a way to access elements of a collection sequentially without exposing its underlying representation. It lets you traverse different collection types using the same interface.

## Key Concepts

### Problem

- Need to traverse different collection types (list, tree, graph)
- Traversal logic couples client code to collection structure
- Multiple traversal methods needed for same collection
- Collection structure changes require code changes

### Solution

- Define iterator interface with has_next() and next()
- Move traversal logic from collection to iterator
- Collection creates appropriate iterator
- Client uses iterator interface regardless of structure

## Pattern Structure

```text
┌────────────────────────────────┐
│  Iterator (abstract)           │ ◄────── Abstract Iterator
├────────────────────────────────┤
│                                │
├────────────────────────────────┤
│ + HasNext(): bool              │
│ + Next(): T                    │
└────────────────────────────────┘
         ▲
         │ inherits
         │
┌───────────────────────────────────┐
│ VectorIterator<T>                 │
├───────────────────────────────────┤
│ - collection: Collection<T>*      │
│ - index: size_t                   │
├───────────────────────────────────┤
│ + HasNext(): bool                 │
│ + Next(): T                       │
└───────────────────────────────────┘

┌──────────────────────────────────┐
│  Collection (abstract)           │ ◄────── Abstract Collection
├──────────────────────────────────┤
│                                  │
├──────────────────────────────────┤
│ + CreateIterator(): Iterator     │
│ + GetSize(): size_t              │
│ + GetElement(int): T             │
└──────────────────────────────────┘
         ▲
         │ inherits
         │
┌──────────────────────────────────────┐
│ VectorCollection<T>                  │
├──────────────────────────────────────┤
│ - items: vector<T>                   │
├──────────────────────────────────────┤
│ + CreateIterator(): Iterator         │
│ + GetSize(): size_t                  │
│ + GetElement(i): T                   │
│ + AddItem(item: T): void             │
└──────────────────────────────────────┘
         │ creates
         └──────────> VectorIterator

Usage:
    Collection* col = new VectorCollection();
    col->AddItem(1);
    col->AddItem(2);
    
    Iterator* it = col->CreateIterator();
    while(it->HasNext()) {
        cout << it->Next() << endl;
    }
```

### Components

- **Iterator**: Abstract interface for traversing elements
- **ConcreteIterator**: Implements traversal for specific collection
- **Collection**: Defines collection interface and creates iterators
- **ConcreteCollection**: Stores elements and creates appropriate iterator

## Example Implementation

The implementation demonstrates:

- **Iterator**: Abstract base for iterators
- **Collection**: Abstract base for collections
- **VectorIterator**: Concrete iterator for vectors
- **VectorCollection**: Concrete collection storing items

## Key Features

1. **Uniform Access**: Same interface for different collections
2. **Encapsulation**: Iterator encapsulates traversal logic
3. **Multiple Iterators**: Multiple iterations possible simultaneously
4. **Collection Independence**: Iterator works without knowing collection structure

## Advantages

- Simplifies collection code by moving traversal to iterator
- Provides uniform interface for different collections
- Supports multiple simultaneous traversals
- Collections can change without affecting iterators

## Disadvantages

- May be overkill for simple collections
- Adds complexity with additional classes
- Performance overhead compared to direct access
- Limited usefulness without proper collection design

## When to Use

- Need to traverse different aggregate objects without coupling code
- Want to hide internal structure of collection
- Need multiple simultaneous traversals
- Want to provide multiple traversal methods

## Real-world Applications

- STL iterators (begin, end, ++, *)
- Java Collections framework (Iterator interface)
- Database result sets
- File system traversal
- Tree and graph traversals
- Generator functions in Python/C++17

## C++14 Features

- Move semantics: `VectorCollection::add_item` now accepts its parameter by-value and moves it into the internal vector (`void add_item(T item) { items_.push_back(std::move(item)); }`). This enables callers to pass temporaries or `std::move` existing objects without extra copies.
