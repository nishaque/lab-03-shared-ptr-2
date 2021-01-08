// Copyright 2020 Yulia Timoshenko <timoshenkojulie01@gmail.com>

#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "SharedPtr.hpp"

TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

TEST(SharedPtr, constructorFromPointer) {
  SharedPtr<int> i{new int{5}};
  ASSERT_EQ(*i, 5);
}
TEST(SharedPtr, constructorFromSelf) {
  SharedPtr<int> i{new int{5}};
  SharedPtr<int> j(i);
  ASSERT_EQ(i.get(), j.get());
  SharedPtr<int> k(std::move(i));
  ASSERT_EQ(k.get(), j.get());
}
TEST(SharedPtr, defaultConstructor) {
  SharedPtr<int> i;
  EXPECT_FALSE(bool(i));
}
TEST(SharedPtr, movingOperatorEq) {
  SharedPtr<int> i{new int{5}};
  SharedPtr<int> j = std::move(i);
  ASSERT_EQ(*j, 5);
}
TEST(SharedPtr, copyingOperatorEq) {
  SharedPtr<int> i{new int{5}};
  SharedPtr<int> j = i;
  ASSERT_EQ(i.get(), j.get());
}
TEST(SharedPtr, reseting) {
  SharedPtr<int> i{new int{5}};
  i.reset();
  ASSERT_EQ(i.get(), nullptr);
  int *a = new int{5};
  i.reset(a);
  ASSERT_EQ(i.get(), a);
}
TEST(SharedPtr, countinf) {
  SharedPtr<int> i{new int{5}};
  SharedPtr<int> j(i);
  SharedPtr<int> k = i;
  ASSERT_EQ(i.use_count(), 3);
  i.reset();
  j.reset();
  k.reset();
  ASSERT_EQ(i.use_count(), 0);
}
TEST(SharedPtr, swapping) {
  int *a = new int{5};
  SharedPtr<int> i(a);
  int *b = new int{7};
  SharedPtr<int> j(b);
  i.swap(j);
  ASSERT_EQ(i.get(), b);
  ASSERT_EQ(j.get(), a);
}
TEST(SharedPtr, operatorArrow) {
  SharedPtr<std::pair<int, int>> a{new std::pair<int, int>{1, 2}};
  ASSERT_EQ(a->first, 1);
}
