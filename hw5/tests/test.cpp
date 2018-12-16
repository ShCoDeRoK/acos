#include <gtest/gtest.h>
#include "../lib/differentiator.h"
#include <iostream>


TEST(differentiator, simple) {
  Differentiator d("((x)+(1))");
  d.differentiate("simple.txt");
}

TEST(differentiator, sin) {
  Differentiator d("(sin((x)*(x)))");
  d.differentiate("sin.txt");
}

TEST(differentiator, cos) {
  Differentiator d("((cos(x))/(cos(3)))");
  d.differentiate("cos.txt");
}

