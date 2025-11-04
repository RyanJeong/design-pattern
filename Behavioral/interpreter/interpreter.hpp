// Created: 2025-11-03
// Filename: interpreter.hpp
// Description: Interpreter design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_INTERPRETER_INTERPRETER_HPP_
#define BEHAVIORAL_INTERPRETER_INTERPRETER_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Abstract expression in the grammar
 * @note Base class for all expressions
 * @side_effects None (abstract)
 */
class Expression {
 public:
  virtual ~Expression() = default;

  /**
   * @brief Evaluates the expression
   * @return Result of evaluation
   * @side_effects None
   * @throws None (noexcept)
   */
  virtual int evaluate() const noexcept = 0;
};

/**
 * @brief Terminal expression - represents a number
 * @note Leaf node in expression tree
 * @side_effects None
 */
class Number : public Expression {
 private:
  int value_;

 public:
  explicit Number(int value) noexcept : value_(value) {}

  /**
   * @brief Returns the number value
   * @return The number
   * @side_effects None
   * @throws None (noexcept)
   */
  int evaluate() const noexcept override { return value_; }
};

/**
 * @brief Non-terminal expression - represents addition
 * @note Internal node combining two expressions
 * @side_effects None
 */
class Add : public Expression {
 private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

 public:
  explicit Add(std::shared_ptr<Expression> left,
               std::shared_ptr<Expression> right) noexcept
      : left_(left), right_(right) {}

  /**
   * @brief Evaluates sum of left and right expressions
   * @return Sum of left and right
   * @side_effects None
   * @throws None (noexcept)
   */
  int evaluate() const noexcept override {
    return left_->evaluate() + right_->evaluate();
  }
};

/**
 * @brief Non-terminal expression - represents subtraction
 * @note Internal node combining two expressions
 * @side_effects None
 */
class Subtract : public Expression {
 private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

 public:
  explicit Subtract(std::shared_ptr<Expression> left,
                    std::shared_ptr<Expression> right) noexcept
      : left_(left), right_(right) {}

  /**
   * @brief Evaluates difference of left and right expressions
   * @return Difference of left and right
   * @side_effects None
   * @throws None (noexcept)
   */
  int evaluate() const noexcept override {
    return left_->evaluate() - right_->evaluate();
  }
};

/**
 * @brief Non-terminal expression - represents multiplication
 * @note Internal node combining two expressions
 * @side_effects None
 */
class Multiply : public Expression {
 private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;

 public:
  explicit Multiply(std::shared_ptr<Expression> left,
                    std::shared_ptr<Expression> right) noexcept
      : left_(left), right_(right) {}

  /**
   * @brief Evaluates product of left and right expressions
   * @return Product of left and right
   * @side_effects None
   * @throws None (noexcept)
   */
  int evaluate() const noexcept override {
    return left_->evaluate() * right_->evaluate();
  }
};

#endif  // BEHAVIORAL_INTERPRETER_INTERPRETER_HPP_
