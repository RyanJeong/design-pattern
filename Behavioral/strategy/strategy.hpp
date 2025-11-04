// Created: 2025-11-03
// Filename: strategy.hpp
// Description: Strategy design pattern implementation
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
   * @brief Starts list rendering
   * @param oss Output string stream
   * @side_effects May append to stream
   * @throws None (noexcept)
   */
  virtual void start(std::ostringstream&) noexcept {}

  /**
   * @brief Ends list rendering
   * @param oss Output string stream
   * @side_effects May append to stream
   * @throws None (noexcept)
   */
  virtual void end(std::ostringstream&) noexcept {}

  /**
   * @brief Adds list item
   * @param oss Output string stream
   * @param item Item to add
   * @side_effects Appends to stream
   * @throws None (noexcept)
   */
  virtual void add_list_item(std::ostringstream& oss,
                             const std::string& item) noexcept = 0;
};

/**
 * @brief Markdown list rendering strategy
 * @note Renders lists in Markdown format
 * @side_effects Appends to stream
 */
class MarkdownListStrategy : public ListStrategy {
 public:
  /**
   * @brief Adds list item in Markdown format
   * @param oss Output string stream
   * @param item Item to add
   * @side_effects Appends " * item\n" to stream
   * @throws None (noexcept)
   */
  void add_list_item(std::ostringstream& oss,
                     const std::string& item) noexcept override {
    oss << " * " << item << "\n";
  }
};

/**
 * @brief HTML list rendering strategy
 * @note Renders lists in HTML format
 * @side_effects Appends to stream
 */
class HtmlListStrategy : public ListStrategy {
 public:
  /**
   * @brief Starts HTML list
   * @param oss Output string stream
   * @side_effects Appends "<ul>\n" to stream
   * @throws None (noexcept)
   */
  void start(std::ostringstream& oss) noexcept override { oss << "<ul>\n"; }

  /**
   * @brief Ends HTML list
   * @param oss Output string stream
   * @side_effects Appends "</ul>\n" to stream
   * @throws None (noexcept)
   */
  void end(std::ostringstream& oss) noexcept override { oss << "</ul>\n"; }

  /**
   * @brief Adds list item in HTML format
   * @param oss Output string stream
   * @param item Item to add
   * @side_effects Appends "<li>item</li>\n" to stream
   * @throws None (noexcept)
   */
  void add_list_item(std::ostringstream& oss,
                     const std::string& item) noexcept override {
    oss << "<li>" << item << "</li>\n";
  }
};

/**
 * @brief Text processor using strategy pattern
 * @note Encapsulates rendering strategy
 * @thread_safety Not thread-safe
 */
class TextProcessor {
 private:
  std::ostringstream oss_;
  std::shared_ptr<ListStrategy> list_strategy_;

 public:
  /**
   * @brief Clears the buffer
   * @side_effects Clears ostringstream
   * @throws None (noexcept)
   */
  void clear() noexcept {
    oss_.str("");
    oss_.clear();
  }

  /**
   * @brief Sets the output format strategy
   * @param strategy New strategy
   * @side_effects Changes internal strategy
   * @throws None (noexcept)
   */
  void set_strategy(std::shared_ptr<ListStrategy> strategy) noexcept {
    list_strategy_ = strategy;
  }

  /**
   * @brief Appends list with current strategy
   * @param items Items to add
   * @side_effects Appends rendered list to stream
   * @throws None (noexcept)
   */
  void append_list(const std::vector<std::string>& items) noexcept {
    if (!list_strategy_) return;
    list_strategy_->start(oss_);
    for (const auto& item : items) {
      list_strategy_->add_list_item(oss_, item);
    }
    list_strategy_->end(oss_);
  }

  /**
   * @brief Gets the processed text
   * @return String representation
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string str() const noexcept { return oss_.str(); }
};

#endif  // BEHAVIORAL_STRATEGY_STRATEGY_HPP_
