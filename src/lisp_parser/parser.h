#pragma once

// Expressions
#include "expressions/ifexpression.h"
#include "expressions/binaryexpression.h"
#include "expressions/literalexpressions.h"

// STD
#include <vector>
#include <string>
#include <memory>

namespace LispParser
{

    class Parser
    {
    private:
        std::vector<std::string> tokens;
        size_t pos = 0;

        [[nodiscard]] std::string peek() const
        {
            return pos < tokens.size() ? tokens[pos] : "";
        }

        [[nodiscard]] std::string consume()
        {
            return tokens[pos++];
        }

        [[nodiscard]] bool match(std::string_view expected)
        {
            if (peek() == expected)
            {
                std::ignore = consume();
                return true;
            }
            return false;
        }

        void expect(std::string_view tok)
        {
            if (!match(tok))
            {
                throw std::runtime_error("Expected '" + std::string(tok) + "'");
            }
        }

        std::unique_ptr<Expressions::Expression> parse_number(std::string_view tok)
        {
            return std::make_unique<Expressions::LiteralExpression>(std::stod(std::string(tok)));
        }

        template <typename ExprType>
        std::unique_ptr<Expressions::Expression> parse_binary_expression()
        {
            auto lhs = parse_expression();
            auto rhs = parse_expression();
            expect(")");
            return std::make_unique<ExprType>(std::move(lhs), std::move(rhs));
        }

        std::unique_ptr<Expressions::Expression> parse_expression()
        {
            if (match("("))
            {
                std::string op = consume();

                if (op == "+")
                {
                    return parse_binary_expression<Expressions::AddExpression>();
                }
                else if (op == "-")
                {
                    return parse_binary_expression<Expressions::SubtractExpression>();
                }
                else if (op == "/")
                {
                    return parse_binary_expression<Expressions::DivideExpression>();
                }
                else if (op == "==")
                {
                    return parse_binary_expression<Expressions::EqualsExpression>();
                }
                else if (op == "If")
                {
                    auto cond = parse_expression();
                    auto thenB = parse_expression();
                    auto elseB = parse_expression();
                    expect(")");
                    return std::make_unique<Expressions::IfExpression>(std::move(cond), std::move(thenB), std::move(elseB));
                }
                else
                {
                    throw std::runtime_error("Unknown operator: " + op);
                }
            }
            else
            {
                return parse_number(consume());
            }
        }

    public:
        explicit Parser(std::vector<std::string> tokens) : tokens(std::move(tokens)) {}
        std::unique_ptr<Expressions::Expression> parse()
        {
            return parse_expression();
        }
    };
}