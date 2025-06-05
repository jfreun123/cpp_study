#pragma once

// Expressions
#include "expression.h"

namespace Expressions
{

    class LiteralExpression : public Expression
    {
    private:
        double value;

    public:
        explicit LiteralExpression(double val) : value(val) {}
        double evaluate() const override { return value; }
    };
}
