#pragma once

namespace Expressions
{
    class Expression
    {
    public:
        virtual double evaluate() const = 0;
        virtual ~Expression() = default;
    };
}