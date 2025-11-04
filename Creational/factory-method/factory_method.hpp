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
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void open() const noexcept = 0;

  /**
   * @brief Saves document
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void save() const noexcept = 0;

  /**
   * @brief Closes document
   * @side_effects Prints to console
   * @throws None (noexcept)
   */
  virtual void close() const noexcept = 0;
};

/**
 * @brief Concrete Product - PDF document
 * @note Implements Document interface for PDF
 * @side_effects None (after construction)
 */
class PdfDocument : public Document {
 public:
  void open() const noexcept override {
    std::cout << "Opening PDF document..." << std::endl;
  }

  void save() const noexcept override {
    std::cout << "Saving PDF document..." << std::endl;
  }

  void close() const noexcept override {
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
  void open() const noexcept override {
    std::cout << "Opening Word document..." << std::endl;
  }

  void save() const noexcept override {
    std::cout << "Saving Word document..." << std::endl;
  }

  void close() const noexcept override {
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
  void open() const noexcept override {
    std::cout << "Opening Text document..." << std::endl;
  }

  void save() const noexcept override {
    std::cout << "Saving Text document..." << std::endl;
  }

  void close() const noexcept override {
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
  virtual std::unique_ptr<Document> create_document() const noexcept = 0;

  /**
   * @brief Opens a new document
   * @side_effects Creates and opens document
   * @throws None (noexcept)
   */
  void new_document() const noexcept {
    auto doc = create_document();
    doc->open();
    doc->save();
    doc->close();
  }
};

/**
 * @brief Concrete Creator - creates PDF documents
 * @note Factory for PDF documents
 * @side_effects None (after construction)
 */
class PdfApplication : public Application {
 public:
  std::unique_ptr<Document> create_document() const noexcept override {
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
  std::unique_ptr<Document> create_document() const noexcept override {
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
  std::unique_ptr<Document> create_document() const noexcept override {
    return std::make_unique<TextDocument>();
  }
};

#endif  // CREATIONAL_FACTORY_METHOD_FACTORY_METHOD_HPP_
