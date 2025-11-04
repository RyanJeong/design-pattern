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
   * @side_effects Depends on implementation
   * @throws None (noexcept)
   */
  virtual void visit_literal(const Literal& literal) noexcept = 0;

  /**
   * @brief Visits binary operation
   * @param op Binary operation to visit
   * @side_effects Depends on implementation
   * @throws None (noexcept)
   */
  virtual void visit_binary_op(const BinaryOp& op) noexcept = 0;
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
   * @side_effects Calls appropriate visit method
   * @throws None (noexcept)
   */
  virtual void accept(ExpressionVisitor& visitor) const noexcept = 0;
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
  double get_value() const noexcept { return value_; }

  /**
   * @brief Accepts a visitor
   * @param visitor Visitor to accept
   * @side_effects Calls visit_literal
   * @throws None (noexcept)
   */
  void accept(ExpressionVisitor& visitor) const noexcept override {
    visitor.visit_literal(*this);
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
  const std::shared_ptr<Expression>& get_left() const noexcept { return left_; }

  /**
   * @brief Gets right operand
   * @return Right expression
   * @side_effects None
   * @throws None (noexcept)
   */
  const std::shared_ptr<Expression>& get_right() const noexcept {
    return right_;
  }

  /**
   * @brief Gets operation type
   * @return Operation (ADD or SUBTRACT)
   * @side_effects None
   * @throws None (noexcept)
   */
  OpType get_op() const noexcept { return op_; }

  /**
   * @brief Accepts a visitor
   * @param visitor Visitor to accept
   * @side_effects Calls visit_binary_op
   * @throws None (noexcept)
   */
  void accept(ExpressionVisitor& visitor) const noexcept override {
    visitor.visit_binary_op(*this);
  }
};

/**
 * @brief Concrete visitor for printing expressions
 * @note Converts expression tree to string
 * @side_effects Builds string representation
 */
class PrintVisitor : public ExpressionVisitor {
 private:
  std::ostringstream oss_;

 public:
  /**
   * @brief Visits literal by appending to output
   * @param literal Literal to visit
   * @side_effects Appends value to stream
   * @throws None (noexcept)
   */
  void visit_literal(const Literal& literal) noexcept override {
    oss_ << literal.get_value();
  }

  /**
   * @brief Visits binary operation by visiting operands
   * @param op Binary operation to visit
   * @side_effects Recursively visits and formats operation
   * @throws None (noexcept)
   */
  void visit_binary_op(const BinaryOp& op) noexcept override {
    oss_ << "(";
    op.get_left()->accept(*this);
    oss_ << (op.get_op() == BinaryOp::ADD ? " + " : " - ");
    op.get_right()->accept(*this);
    oss_ << ")";
  }

  /**
   * @brief Gets string representation
   * @return Result string
   * @side_effects None
   * @throws None (noexcept)
   */
  std::string str() const noexcept { return oss_.str(); }
};

/**
 * @brief Concrete visitor for evaluating expressions
 * @note Calculates expression result
 * @side_effects Computes numeric result
 */
class EvalVisitor : public ExpressionVisitor {
 private:
  double result_{0};

 public:
  /**
   * @brief Visits literal by storing value
   * @param literal Literal to visit
   * @side_effects Sets result to literal value
   * @throws None (noexcept)
   */
  void visit_literal(const Literal& literal) noexcept override {
    result_ = literal.get_value();
  }

  /**
   * @brief Visits binary operation and evaluates
   * @param op Binary operation to visit
   * @side_effects Recursively evaluates and stores result
   * @throws None (noexcept)
   */
  void visit_binary_op(const BinaryOp& op) noexcept override {
    EvalVisitor left_eval;
    op.get_left()->accept(left_eval);

    EvalVisitor right_eval;
    op.get_right()->accept(right_eval);

    if (op.get_op() == BinaryOp::ADD) {
      result_ = left_eval.result_ + right_eval.result_;
    } else {
      result_ = left_eval.result_ - right_eval.result_;
    }
  }

  /**
   * @brief Gets evaluation result
   * @return Numeric result
   * @side_effects None
   * @throws None (noexcept)
   */
  double get_result() const noexcept { return result_; }
};

#endif  // BEHAVIORAL_VISITOR_VISITOR_HPP_
