#include "../header/declaration.h"
#include "iostream"

int main() {
  std::cout << "CUDA ACCELERATED MATRIX MULTIPLICATIONNN \n";

  matrix *m1 = newMatrix(2, 3);
  matrix *m2 = newMatrix(3, 2);
  matrix *s = newMatrix(2, 2);
  XUtils::fillMatrix(m1);
  XUtils::fillMatrix(m2);
  XOpps::matMul(m1, m2, s);
  XUtils::printMatrix(m1);
  XUtils::printMatrix(m2);
  XUtils::printMatrix(s);

  XOpps::transpose(s);
  XUtils::printMatrix(s);

  return 0;
}
