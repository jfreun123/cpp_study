#pragma once

// Expressions
#include "expression.h"

// STD
#include <memory>

namespace Expressions
{
    class IfExpression : public Expression
    {
        std::unique_ptr<Expression> condition;
        std::unique_ptr<Expression> thenBranch;
        std::unique_ptr<Expression> elseBranch;

    public:
        IfExpression(std::unique_ptr<Expression> cond,
                     std::unique_ptr<Expression> thenB,
                     std::unique_ptr<Expression> elseB)
            : condition(std::move(cond)), thenBranch(std::move(thenB)), elseBranch(std::move(elseB)) {}

        double evaluate() const override
        {
            return condition->evaluate() != 0.0 ? thenBranch->evaluate() : elseBranch->evaluate();
        }
    };
}