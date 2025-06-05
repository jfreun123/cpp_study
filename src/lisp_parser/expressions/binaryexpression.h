#pragma once

// Expressions
#include "expression.h"

// STD
#include <memory>
#include <stdexcept>

namespace Expressions
{
    class BinaryExpression : public Expression
    {
    protected:
        std::unique_ptr<Expression> left;
        std::unique_ptr<Expression> right;

    public:
        BinaryExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
            : left(std::move(lhs)), right(std::move(rhs)) {}
    };

    class AddExpression : public BinaryExpression
    {
    public:
        using BinaryExpression::BinaryExpression;
        double evaluate() const override
        {
            return left->evaluate() + right->evaluate();
        }
    };

    class SubtractExpression : public BinaryExpression
    {
    public:
        using BinaryExpression::BinaryExpression;
        double evaluate() const override
        {
            return left->evaluate() - right->evaluate();
        }
    };

    class EqualsExpression : public BinaryExpression
    {
    public:
        using BinaryExpression::BinaryExpression;
        double evaluate() const override
        {
            return left->evaluate() == right->evaluate() ? 1.0 : 0.0;
        }
    };

    class DivideExpression : public BinaryExpression
    {
    public:
        using BinaryExpression::BinaryExpression;
        double evaluate() const override
        {
            double denom = right->evaluate();
            if (denom == 0)
                throw std::runtime_error("Division by zero");
            return left->evaluate() / denom;
        }
    };
}