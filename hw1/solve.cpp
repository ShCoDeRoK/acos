#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>

void input(float* a, float* b, float* c) {
  printf("Enter coefficients of square equation: ");
  int num_success = scanf("%f %f %f", a, b, c);
  if (num_success != 3) {
    printf("Wrond data in input!");
    exit(1);
  }
}

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

int solverSquareEquation(float a, float b, float c, float* x1, float* x2) {
  if (a == 0)
    return solverLinearEquation(b, c, x1);
  float d = 4 * a * c - b * b;
  if (d < 0)
    return 0;  
  *x1 = (-b + sqrt(d)) / (2 * a);
  if (d == 0)
    return 1;
  *x2 = (-b - sqrt(d)) / (2 * a);
  return 2;
}

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
