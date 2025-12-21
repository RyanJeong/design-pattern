// Created: 2025-11-03
// Filename: factory_method.hpp
// Description: Factory Method design pattern implementation
// Copyright 2025

#ifndef CREATIONAL_FACTORY_METHOD_FACTORY_METHOD_HPP_
#define CREATIONAL_FACTORY_METHOD_FACTORY_METHOD_HPP_

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Abstract Product - base class for created objects
 * @note Defines interface for concrete products
 * @side_effects None (abstract)
 */
class Document {
 public:
  virtual ~Document() = default;

  /**
   * @brief Opens document
   * @side_effects Prints to console for demo feedback
   * @side_effects_reason Demonstration requirement: Factory Method pattern
   *   is about delegating object creation to subclasses. Console output
   *   demonstrates which concrete type was created and its behavior
   * @side_effects_what Writes to stdout for document type visibility
   * @side_effects_impact Console I/O adds minimal overhead (one-time per
   * operation)
   * @side_effects_alternatives Inject logger; adds complexity for demo code
   * @throws None (noexcept)
   */
  virtual void Open() const noexcept = 0;

  /**
   * @brief Saves document
   * @side_effects Prints to console (see Open() rationale)
   * @throws None (noexcept)
   */
  virtual void Save() const noexcept = 0;

  /**
   * @brief Closes document
   * @side_effects Prints to console (see Open() rationale)
   * @throws None (noexcept)
   */
  virtual void Close() const noexcept = 0;
};

/**
 * @brief Concrete Product - PDF document
 * @note Implements Document interface for PDF
 * @side_effects None (after construction)
 */
class PdfDocument : public Document {
 public:
  void Open() const noexcept override {
    std::cout << "Opening PDF document..." << std::endl;
  }

  void Save() const noexcept override {
    std::cout << "Saving PDF document..." << std::endl;
  }

  void Close() const noexcept override {
    std::cout << "Closing PDF document..." << std::endl;
  }
};

/**
 * @brief Concrete Product - Word document
 * @note Implements Document interface for Word
 * @side_effects None (after construction)
 */
class WordDocument : public Document {
 public:
  void Open() const noexcept override {
    std::cout << "Opening Word document..." << std::endl;
  }

  void Save() const noexcept override {
    std::cout << "Saving Word document..." << std::endl;
  }

  void Close() const noexcept override {
    std::cout << "Closing Word document..." << std::endl;
  }
};

/**
 * @brief Concrete Product - Text document
 * @note Implements Document interface for Text
 * @side_effects None (after construction)
 */
class TextDocument : public Document {
 public:
  void Open() const noexcept override {
    std::cout << "Opening Text document..." << std::endl;
  }

  void Save() const noexcept override {
    std::cout << "Saving Text document..." << std::endl;
  }

  void Close() const noexcept override {
    std::cout << "Closing Text document..." << std::endl;
  }
};

/**
 * @brief Abstract Creator - defines factory method
 * @note Base class for concrete creators
 * @side_effects None (abstract)
 */
class Application {
 public:
  virtual ~Application() = default;

  /**
   * @brief Factory method - creates documents
   * @return Unique pointer to created Document
   * @side_effects Creates new Document
   * @throws None (noexcept)
   */
  virtual std::unique_ptr<Document> CreateDocument() const noexcept = 0;

  /**
   * @brief Opens a new document
   * @side_effects Creates and opens document
   * @throws None (noexcept)
   */
  void NewDocument() const noexcept {
    auto doc = CreateDocument();
    doc->Open();
    doc->Save();
    doc->Close();
  }
};

/**
 * @brief Concrete Creator - creates PDF documents
 * @note Factory for PDF documents
 * @side_effects None (after construction)
 */
class PdfApplication : public Application {
 public:
  std::unique_ptr<Document> CreateDocument() const noexcept override {
    return std::make_unique<PdfDocument>();
  }
};

/**
 * @brief Concrete Creator - creates Word documents
 * @note Factory for Word documents
 * @side_effects None (after construction)
 */
class WordApplication : public Application {
 public:
  std::unique_ptr<Document> CreateDocument() const noexcept override {
    return std::make_unique<WordDocument>();
  }
};

/**
 * @brief Concrete Creator - creates Text documents
 * @note Factory for Text documents
 * @side_effects None (after construction)
 */
class TextApplication : public Application {
 public:
  std::unique_ptr<Document> CreateDocument() const noexcept override {
    return std::make_unique<TextDocument>();
  }
};

#endif  // CREATIONAL_FACTORY_METHOD_FACTORY_METHOD_HPP_
