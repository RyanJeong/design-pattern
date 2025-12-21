// Created: 2025-11-03
// Filename: strategy.hpp
// Description: Strategy design pattern demonstration
// Copyright 2025

#ifndef BEHAVIORAL_STRATEGY_STRATEGY_HPP_
#define BEHAVIORAL_STRATEGY_STRATEGY_HPP_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Abstract strategy for rendering lists
 * @note Base class for different rendering strategies
 * @side_effects None (abstract)
 */
class ListStrategy {
 public:
  virtual ~ListStrategy() = default;

  /**
   * @brief Formats list start
   * @return Formatted string for list start
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual std::string FormatStart() const noexcept { return ""; }

  /**
   * @brief Formats list end
   * @return Formatted string for list end
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual std::string FormatEnd() const noexcept { return ""; }

  /**
   * @brief Formats a list item
   * @param item Item to format
   * @return Formatted item string
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual std::string FormatItem(const std::string& item) const noexcept = 0;
};

/**
 * @brief Markdown list rendering strategy
 * @note Renders lists in Markdown format
 * @side_effects None
 */
class MarkdownListStrategy : public ListStrategy {
 public:
  /**
   * @brief Formats list item in Markdown format
   * @param item Item to format
   * @return Formatted item
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string FormatItem(const std::string& item) const noexcept override {
    return " * " + item + "\n";
  }
};

/**
 * @brief HTML list rendering strategy
 * @note Renders lists in HTML format
 * @side_effects None
 */
class HtmlListStrategy : public ListStrategy {
 public:
  /**
   * @brief Formats list start
   * @return HTML list start tag
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string FormatStart() const noexcept override { return "<ul>\n"; }

  /**
   * @brief Formats list end
   * @return HTML list end tag
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string FormatEnd() const noexcept override { return "</ul>\n"; }

  /**
   * @brief Formats list item in HTML format
   * @param item Item to format
   * @return Formatted item
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string FormatItem(const std::string& item) const noexcept override {
    return "<li>" + item + "</li>\n";
  }
};

/**
 * @brief Text processor using strategy pattern
 * @note Encapsulates rendering strategy
 * @thread_safety Not thread-safe
 */
class TextProcessor {
 private:
  std::string buffer_;
  std::shared_ptr<ListStrategy> list_strategy_;

 public:
  /**
   * @brief Clears the buffer
   * @return Empty string (for chaining)
   * @side_effects Clears internal buffer
   * @throws None (noexcept)
   */
  TextProcessor Clear() const noexcept {
    TextProcessor processor;
    processor.list_strategy_ = list_strategy_;
    return processor;
  }

  /**
   * @brief Sets the output format strategy
   * @param strategy New strategy
   * @return Reference to this processor
   * @side_effects Changes internal strategy
   * @throws None (noexcept)
   */
  TextProcessor WithStrategy(
      std::shared_ptr<ListStrategy> strategy) const noexcept {
    TextProcessor processor;
    processor.buffer_ = buffer_;
    processor.list_strategy_ = strategy;
    return processor;
  }

  /**
   * @brief Appends list with current strategy
   * @param items Items to add
   * @return New processor with appended list
   * @side_effects None (returns new object)
   * @throws None (noexcept)
   */
  TextProcessor AppendList(
      const std::vector<std::string>& items) const noexcept {
    TextProcessor result;
    result.buffer_ = buffer_;
    result.list_strategy_ = list_strategy_;

    if (!list_strategy_) return result;

    result.buffer_ += list_strategy_->FormatStart();
    for (const auto& item : items) {
      result.buffer_ += list_strategy_->FormatItem(item);
    }
    result.buffer_ += list_strategy_->FormatEnd();

    return result;
  }

  /**
   * @brief Gets the processed text
   * @return String representation
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string str() const noexcept { return buffer_; }
};

#endif  // BEHAVIORAL_STRATEGY_STRATEGY_HPP_
