
// src
#include <setintersection.h>

// Gtest
#include <gtest/gtest.h>

TEST(SetIntersection, Simple)
{
    std::vector<std::vector<int>> in{{{2, 3},
                                      {0, 2, 3},
                                      {2, 3, 4}}};
    std::vector<int> out{2, 3};
    EXPECT_EQ(SetIntersection::intersectKSortedSets(in), out);
}

TEST(SetIntersection, Medium)
{
    std::vector<std::vector<int>> in{{{2, 3}, {0, 1, 2, 3}, {2, 3, 4}}};
    std::vector<int> out{2, 3};
    EXPECT_EQ(SetIntersection::intersectKSortedSets(in), out);
}

TEST(SetIntersection, MediumPartTwo)
{
    std::vector<std::vector<int>> in{
        {{1, 2, 3},
         {3, 4, 5, 6},
         {3}}};
    std::vector<int> out{3};
    EXPECT_EQ(SetIntersection::intersectKSortedSets(in), out);
}