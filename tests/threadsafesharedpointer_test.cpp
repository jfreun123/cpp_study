// src
#include <threadsafesharedpointer.hpp>

// Gtest
#include <gtest/gtest.h>

// Helper class to track destruction
class TestObject
{
public:
  static int destructor_calls;
  int value;

  explicit TestObject(int v) : value(v) {}
  ~TestObject()
  {
    ++destructor_calls;
  }
};

int TestObject::destructor_calls = 0;

TEST(SharedPointerTest, DefaultConstructor)
{
  core::shared_pointer<int> sp;
  EXPECT_EQ(sp.get(), nullptr);
  EXPECT_EQ(sp.use_count(), 0);
}

TEST(SharedPointerTest, ConstructorWithRawPointer)
{
  core::shared_pointer<int> sp(new int(10));
  EXPECT_NE(sp.get(), nullptr);
  EXPECT_EQ(*sp, 10);
  EXPECT_EQ(sp.use_count(), 1);
}

TEST(SharedPointerTest, CopyConstructor)
{
  core::shared_pointer<int> sp1(new int(20));
  core::shared_pointer<int> sp2(sp1);
  EXPECT_EQ(sp1.use_count(), 2);
  EXPECT_EQ(sp2.use_count(), 2);
  EXPECT_EQ(*sp1, 20);
  EXPECT_EQ(*sp2, 20);
}

TEST(SharedPointerTest, AssignmentOperator)
{
  core::shared_pointer<int> sp1(new int(30));
  core::shared_pointer<int> sp2;
  sp2 = sp1;
  EXPECT_EQ(sp1.use_count(), 2);
  EXPECT_EQ(sp2.use_count(), 2);
  EXPECT_EQ(*sp1, 30);
  EXPECT_EQ(*sp2, 30);
}

TEST(SharedPointerTest, Reset)
{
  core::shared_pointer<int> sp(new int(40));
  EXPECT_EQ(sp.use_count(), 1);
  sp.reset(new int(50));
  EXPECT_EQ(*sp, 50);
  EXPECT_EQ(sp.use_count(), 1);
}

TEST(SharedPointerTest, DestructionAndRefCount)
{
  TestObject::destructor_calls = 0;
  core::shared_pointer<TestObject> sp1(new TestObject(100));
  {
    core::shared_pointer<TestObject> sp2(sp1);
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
  }
  EXPECT_EQ(sp1.use_count(), 1);
  sp1.reset();
  EXPECT_EQ(TestObject::destructor_calls, 1);
}

TEST(SharedPointerTest, SelfAssignment)
{
  core::shared_pointer<int> sp(new int(60));
  sp = sp; // Self-assignment
  EXPECT_EQ(sp.use_count(), 1);
  EXPECT_EQ(*sp, 60);
}

TEST(SharedPointerTest, NullptrReset)
{
  core::shared_pointer<int> sp(new int(70));
  sp.reset(nullptr);
  EXPECT_EQ(sp.get(), nullptr);
  EXPECT_EQ(sp.use_count(), 0);
}

TEST(SharedPointerTest, DereferenceAndMemberAccess)
{
  core::shared_pointer<TestObject> sp(new TestObject(80));
  EXPECT_EQ(sp->value, 80);
  EXPECT_EQ((*sp).value, 80);
}