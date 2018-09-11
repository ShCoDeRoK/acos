#include <cstdlib>
#include <climits>
#include <cmath>


//------------------------------------------------------------------------------
//! Solves a linear equation ax + b = 0
//!
//! @param [in] a a-coefficient
//! @param [in] b b-coefficient
//! @param [ut] x Pointer to the first root
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots, returns INT_MAX.
//------------------------------------------------------------------------------

int solverLinearEquation(float a, float b, float* x) {
  if (a == 0) {
    if (b == 0)
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
  if (a == 0)
    return solverLinearEquation(b, c, x1);
  float d = b * b - 4 * a * c;
  if (d < 0)
    return 0;  
  *x1 = (-b + sqrt(d)) / (2 * a);
  if (d == 0)
    return 1;
  *x2 = (-b - sqrt(d)) / (2 * a);
  return 2;
}
