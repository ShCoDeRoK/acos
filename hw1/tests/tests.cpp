#include <gtest/gtest.h>
#include "../lib/equations.h"

const int EPS = 1e-8;

TEST(_000_Test, SquareEquationSolver) {
  float x1, x2;
  EXPECT_EQ(INT_MAX, solverSquareEquation(0, 0, 0, &x1, &x2));
}

TEST(_105_TEST, SquareEquationSolver) {
  float x1, x2;
  EXPECT_EQ(0, solverSquareEquation(1, 0, 5, &x1, &x2));
}

TEST(_015_TEST, SquareEquationSolver) {
  float x1, x2;
  EXPECT_EQ(1, solverSquareEquation(0, 1, 5, &x1, &x2));
  EXPECT_LE(abs(x1 - (-5)), EPS);
}

TEST(_100_TEST, SquareEquationSolver) {
  float x1, x2;
  EXPECT_EQ(1, solverSquareEquation(1, 0, 0, &x1, &x2));
  EXPECT_LE(abs(x1), FLT_EPSILON);
}

TEST(FLOAT_TEST, SquareEquationSolver) {
  float x1, x2;
  EXPECT_EQ(2, solverSquareEquation(12.123, -5.999, -7.3234, &x1, &x2));
  EXPECT_LE(abs(std::min(x1, x2) + 0.568243), EPS);
  EXPECT_LE(abs(std::max(x1, x2) - 1.06309), EPS);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
