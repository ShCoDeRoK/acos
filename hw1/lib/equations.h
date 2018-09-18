#include <cstdlib>
#include <climits>
#include <cmath>
#include <cfloat>

//------------------------------------------------------------------------------
//! Solves a linear equation ax + b = 0
//!
//! @param [in] a a-coefficient
//! @param [in] b b-coefficient
//! @param [out] x Pointer to the first root
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots, returns INT_MAX.
//------------------------------------------------------------------------------

int solverLinearEquation(float a, float b, float* x) {
  if (x == nullptr) {
    printf("Bad pointer to the root!\n");
    exit(1);
  }
  if (abs(a) < FLT_EPSILON) {
    if (abs(b) < FLT_EPSILON)
      return INT_MAX;
    else
      return 0;
  }
  *x = -b / a;
  return 1;
}

//------------------------------------------------------------------------------
//! Solves a square equation ax^2 + bx + c = 0
//!
//! @param [in] a   a-coefficient
//! @param [in] b   b-coefficient
//! @param [in] c   c-coefficient
//! @param [out] x1 Pointer to the first root
//! @param [out] x2 Pointer to the second root
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots, returns INT_MAX.
//------------------------------------------------------------------------------

int solverSquareEquation(float a, float b, float c, float* x1, float* x2) {
  if (x1 == nullptr || x2 == nullptr) {
    printf("Bad pointers to the roots!\n");
    exit(1);
  }
  if (x1 == x2) {
    printf("Pointers are the same!\n");
    exit(1);
  }
  if (abs(a) < FLT_EPSILON)
    return solverLinearEquation(b, c, x1);
  float d = b * b - 4 * a * c;
  if (d <= -FLT_EPSILON)
    return 0;  
  *x1 = (-b + sqrt(d)) / (2 * a);
  if (abs(d) < FLT_EPSILON)
    return 1;
  *x2 = (-b - sqrt(d)) / (2 * a);
  return 2;
}
