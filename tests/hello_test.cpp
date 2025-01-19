// src
#include <rwlock.hpp>

// Gtest
#include <gtest/gtest.h>



// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  EXPECT_EQ(4, rwlock::doubleNum(2));  
}