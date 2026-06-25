#pragma once

struct matrix {
  float *data;
  int r;
  int c;
  int l;
};

matrix *newMatrix(int x, int y);

matrix newMatrixStack(int x, int y);

void freeMatrix(matrix *mat);

namespace XUtils {
void printMatrix(matrix *m);
void fillMatrix(matrix *m);
void fillRandom(matrix *m);

void setData(matrix *m, float *array);
} // namespace XUtils

namespace XOpps {
void matMul(matrix *m1, matrix *m2, matrix *store);
void matAdd(matrix *m1, matrix *m2, matrix *store);
void transpose(matrix *m);
void elementWiseMatMul(const matrix *m1, const matrix *m2, matrix *store);

void scalerMul(matrix *m1, float num);

} // namespace XOpps
  //

namespace Cuda {
void matMul(matrix *m1, matrix *m2, matrix *store);
void transpose(matrix *m);
} // namespace Cuda
