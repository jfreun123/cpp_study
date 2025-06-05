// src
#include <parser.h>
#include <tokenizer.h>

// Gtest
#include <gtest/gtest.h>

TEST(LispParser, IfStatement)
{
    const std::string input = "(If (== 3 5) (/ 1 0) (+ 9 10))";
    auto tokens = LispParser::tokenize(input);
    LispParser::Parser parser(tokens);
    auto expr = parser.parse();
    EXPECT_EQ(expr->evaluate(), 19.0);
}