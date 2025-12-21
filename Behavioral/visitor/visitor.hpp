// Created: 2025-11-03
// Filename: visitor.hpp
// Description: Visitor design pattern implementation
// Copyright 2025

#ifndef BEHAVIORAL_VISITOR_VISITOR_HPP_
#define BEHAVIORAL_VISITOR_VISITOR_HPP_

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

/**
 * @brief Forward declarations
 */
class Literal;
class BinaryOp;

/**
 * @brief Visitor interface for expressions
 * @note Base class for different expression visitors
 * @side_effects None (abstract)
 */
class ExpressionVisitor {
 public:
  virtual ~ExpressionVisitor() = default;

  /**
   * @brief Visits literal expression
   * @param literal Literal to visit
   * @return Visit result
   * @side_effects Depends on implementation
   * @throws None (noexcept)
   */
  virtual std::string VisitLiteral(const Literal& literal) const noexcept = 0;

  /**
   * @brief Visits binary operation
   * @param op Binary operation to visit
   * @return Visit result
   * @side_effects Depends on implementation
   * @throws None (noexcept)
   */
  virtual std::string VisitBinaryOp(const BinaryOp& op) const noexcept = 0;
};

/**
 * @brief Expression element that accepts visitors
 * @note Base class for expression tree nodes
 * @side_effects None (abstract)
 */
class Expression {
 public:
  virtual ~Expression() = default;

  /**
   * @brief Accepts a visitor
   * @param visitor Visitor to accept
   * @return Visit result
   * @side_effects Calls appropriate visit method
   * @throws None (noexcept)
   */
  virtual std::string Accept(
      const ExpressionVisitor& visitor) const noexcept = 0;
};

/**
 * @brief Literal expression - represents number
 * @note Leaf node in expression tree
 * @side_effects None
 */
class Literal : public Expression {
 private:
  double value_;

 public:
  explicit Literal(double value) noexcept : value_(value) {}

  /**
   * @brief Gets the literal value
   * @return The value
   * @side_effects None
   * @throws None (noexcept)
   */
  double GetValue() const noexcept { return value_; }

  /**
   * @brief Accepts a visitor
   * @param visitor Visitor to accept
   * @return Visit result
   * @side_effects Calls visit_literal
   * @throws None (noexcept)
   */
  std::string Accept(const ExpressionVisitor& visitor) const noexcept override {
    return visitor.VisitLiteral(*this);
  }
};

/**
 * @brief Binary operation - represents addition/subtraction
 * @note Internal node combining expressions
 * @side_effects None
 */
class BinaryOp : public Expression {
 public:
  enum OpType {
    ADD,
    SUBTRACT
  };

 private:
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
  OpType op_;

 public:
  explicit BinaryOp(std::shared_ptr<Expression> left,
                    std::shared_ptr<Expression> right, OpType op) noexcept
      : left_(left), right_(right), op_(op) {}

  /**
   * @brief Gets left operand
   * @return Left expression
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::shared_ptr<Expression>& GetLeft() const noexcept { return left_; }

  /**
   * @brief Gets right operand
   * @return Right expression
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::shared_ptr<Expression>& GetRight() const noexcept {
    return right_;
  }

  /**
   * @brief Gets operation type
   * @return Operation (ADD or SUBTRACT)
   * @side_effects None
   * @throws None (noexcept)
   */
  OpType GetOp() const noexcept { return op_; }

  /**
   * @brief Accepts a visitor
   * @param visitor Visitor to accept
   * @return Visit result
   * @side_effects Calls visit_binary_op
   * @throws None (noexcept)
   */
  std::string Accept(const ExpressionVisitor& visitor) const noexcept override {
    return visitor.VisitBinaryOp(*this);
  }
};

/**
 * @brief Concrete visitor for printing expressions
 * @note Converts expression tree to string
 * @side_effects None (returns string)
 */
class PrintVisitor : public ExpressionVisitor {
 public:
  /**
   * @brief Visits literal by converting to string
   * @param literal Literal to visit
   * @return String representation of value
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string VisitLiteral(const Literal& literal) const noexcept override {
    return std::to_string(static_cast<int>(literal.GetValue()));
  }

  /**
   * @brief Visits binary operation
   * @param op Binary operation to visit
   * @return String representation of operation
   * @side_effects None (returns formatted string)
   * @throws None (noexcept)
   */
  std::string VisitBinaryOp(const BinaryOp& op) const noexcept override {
    std::string left = op.GetLeft()->Accept(*this);
    std::string right = op.GetRight()->Accept(*this);
    std::string op_str = (op.GetOp() == BinaryOp::ADD) ? " + " : " - ";
    return "(" + left + op_str + right + ")";
  }
};

/**
 * @brief Concrete visitor for evaluating expressions
 * @note Calculates expression result
 * @side_effects None (returns computed value)
 */
class EvalVisitor : public ExpressionVisitor {
 public:
  /**
   * @brief Visits literal by returning value
   * @param literal Literal to visit
   * @return String representation of value
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string VisitLiteral(const Literal& literal) const noexcept override {
    return std::to_string(static_cast<int>(literal.GetValue()));
  }

  /**
   * @brief Visits binary operation and evaluates
   * @param op Binary operation to visit
   * @return String representation of result
   * @side_effects None (returns computed value)
   * @throws None (noexcept)
   */
  std::string VisitBinaryOp(const BinaryOp& op) const noexcept override {
    std::string left_result = op.GetLeft()->Accept(*this);
    std::string right_result = op.GetRight()->Accept(*this);

    double left_val = std::stod(left_result);
    double right_val = std::stod(right_result);

    double result = (op.GetOp() == BinaryOp::ADD) ? (left_val + right_val)
                                                  : (left_val - right_val);

    return std::to_string(static_cast<int>(result));
  }

  /**
   * @brief Evaluates expression
   * @param expr Expression to evaluate
   * @return Numeric result as string
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string Evaluate(const std::shared_ptr<Expression>& expr) const noexcept {
    return expr->Accept(*this);
  }
};

#endif  // BEHAVIORAL_VISITOR_VISITOR_HPP_
