#include <cstdio>
#include "lib/equations.h"

//------------------------------------------------------------------------------
//! Input three float numbers
//!
//! @params [in]  a Pointer to a-coefficient
//! @params [in]  b Pointer to b-coefficient
//! @params [in]  c Pointer to c-coefficient
//!
//! @return void
//------------------------------------------------------------------------------

void input(float* a, float* b, float* c) {
  printf("Enter coefficients of square equation(three float numbers): ");
  int num_success = scanf("%f %f %f", a, b, c);
  if (num_success != 3) {
    printf("Wrond data in input!");
    exit(1);
  }
}

//------------------------------------------------------------------------------
//! Output number of roots 
//! @params [in]  num_roots Number of roots
//! @params [in]  x1        First root
//! @params [in]  x2        Second root
//!
//! @return void
//!
//! @note   In case of infinite number of roots, print Infinity number of roots
//------------------------------------------------------------------------------

void output(int num_roots, float x1, float x2) {
  if (num_roots == INT_MAX) {
    printf("Infinity number of roots\n");
    exit(0);
  }
  printf("Number of roots: %d\n", num_roots);
  if (num_roots >= 1)
    printf("Root number 1: %f\n", x1);
  if (num_roots >= 2)
    printf("Root number 2: %f\n", x2);
}

int main() {
  float a, b, c;
  input(&a, &b, &c);
  float x1, x2;
  int num_roots = solverSquareEquation(a, b, c, &x1, &x2);
  output(num_roots, x1, x2);
  return 0;
}
