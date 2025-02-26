
// src
#include <generateProducts.hpp>

// Gtest
#include <gtest/gtest.h>

TEST(GenerateProduct, Interview)
{
    std::vector<int> in{2, 3};
    std::vector<int> out{2, 3, 6};
    EXPECT_EQ(PrimeHelpers::generateProducts(in), out);
    EXPECT_EQ(PrimeHelpers::generateProductsClean(in), out);
}

TEST(GenerateProduct, InterviewTwo)
{
    std::vector<int> in{2, 3, 5};
    std::vector<int> out{2, 3, 5, 6, 10, 15, 30};
    EXPECT_EQ(PrimeHelpers::generateProducts(in), out);
    EXPECT_EQ(PrimeHelpers::generateProductsClean(in), out);
}