#include <gtest/gtest.h>
#include "../lib/stack.h"
#include <iostream>

TEST(stack, push_test) {
  Stack<int> s(1);
  for (int i = 0; i < 10000; ++i) {
    s.push(i);
  }
  for (int i = 9999; i >= 0; --i) {
    EXPECT_EQ(i, s.pop());
  }
}

TEST(stack, change_checksum_test) {
  Stack<int> s(1);
  char* ptr = (char*)(&s);
  for (int i = 0; i < 2; ++i) {
    s.push(i);
  }
  *ptr = 113;
  for (int i = 1; i >= 0; --i) {
    EXPECT_EQ(i, s.pop());
  }
}


//For peer-to-peer review
/*
TEST(Pop_Test, Stack) {
  Stack<int> s;
  for (int i = 0; i < 10; ++i) {
    s.pop();
  }
}

TEST(stack, push_test) {
  Stack<int> s(1);
  char* ptr = (char*)(&s);
  for (int i = 0; i < 2; ++i) {
    s.push(i);
  }
  *ptr = 113;
  for (int i = 1; i >= 0; --i) {
    EXPECT_EQ(i, s.pop());
  }
}
*/
