#pragma once

#include <vector>
#include <string>

namespace LispParser
{
    std::vector<std::string> tokenize(const std::string &input)
    {
        std::vector<std::string> tokens;
        std::string token;
        for (char c : input)
        {
            if (std::isspace(c))
            {
                if (!token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
            }
            else if (c == '(' || c == ')')
            {
                if (!token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
                tokens.emplace_back(1, c);
            }
            else
            {
                token += c;
            }
        }
        if (!token.empty())
            tokens.push_back(token);
        return tokens;
    }
}