# Interpreter Pattern

## Overview

The Interpreter pattern is a behavioral design pattern that defines a grammatical representation for a language and an interpreter to interpret sentences in that language. It lets you define how to represent language and provides a mechanism to interpret strings.

## Key Concepts

### Problem

- You need to evaluate sentences in a domain-specific language
- Build abstract syntax trees (AST) that represent sentences
- Evaluate and manipulate the AST
- Extend the language grammar without modifying existing code

### Solution

- Define classes for each grammar rule
- Terminal expressions represent basic elements
- Non-terminal expressions combine other expressions
- Build expression trees and evaluate recursively

## Pattern Structure

```text
    Expression (abstract)
    /              \
Terminal        NonTerminal
Number          Add, Subtract, etc.
```

### Components

- **Expression**: Abstract interface for all expressions
- **TerminalExpression**: Represents leaf nodes (literals)
- **NonTerminalExpression**: Represents complex expressions
- **Context**: Contains data shared during interpretation

## Example Implementation

The implementation demonstrates:

- **Expression**: Abstract base for all expressions
- **Number**: Terminal expression for numeric literals
- **Add, Subtract, Multiply**: Non-terminal expressions
- **Expression trees** built and evaluated recursively

## Key Features

1. **Grammar Representation**: Language grammar represented as classes
2. **Recursive Evaluation**: Tree structure allows recursive evaluation
3. **Easy Extension**: New operations added by new classes
4. **Clear Structure**: Expression tree clearly shows relationships

## Advantages

- Easy to implement for simple grammars
- Grammar changes are easy to incorporate
- Clear object-oriented structure
- Follows the Single Responsibility Principle

## Disadvantages

- Complex grammars create many classes
- Less efficient than hand-coded parsers
- May consume significant memory
- Can be difficult to parse complex languages

## When to Use

- You need to define a simple language or DSL
- Grammar rules can be represented in classes
- Evaluation strategy needs to be flexible
- You need to build and manipulate syntax trees

## Real-world Applications

- Mathematical expression evaluation
- SQL query parsing and execution
- Configuration file parsing
- Scripting language interpretation
- Template engines
- Query languages (XPath, JSONPath)
- Configuration management DSLs
