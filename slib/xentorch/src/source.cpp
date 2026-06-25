#include "../header/declaration.h"
#include <cstdlib>
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<float> dist(0.0f, 1.1f); // mean=0, std=0.1

matrix *newMatrix(int r, int c) {
  matrix *m = new matrix;
  m->r = r;
  m->c = c;
  m->l = r * c;

  m->data = (float *)malloc(m->l * sizeof(float));

  return m;
};

matrix newMatrixStack(int x, int y) {
  matrix *tempMatrix = newMatrix(x, y);
  matrix toRet;

  toRet = (*tempMatrix);
  freeMatrix(tempMatrix);

  return toRet;
};

void XUtils::printMatrix(matrix *m) {
  std::cout << "\n";
  for (int i = 0; i < m->r; i++) {
    for (int j = 0; j < m->c; j++) {
      std::cout << m->data[i * m->c + j] << ", ";
    }

    std::cout << "\n";
  }
}

void XUtils::fillMatrix(matrix *m) {
  for (int i = 0; i < m->l; i++) {
    m->data[i] = i;
  }
}

void XUtils::fillRandom(matrix *m) {
  for (int i = 0; i < m->l; i++) {
    float rand = dist(gen);
    m->data[i] = rand;
  }
}

void XUtils::setData(matrix *m, float *arr) {

  for (int i = 0; i < m->l; i++) {
    m->data[i] = arr[i];
  }
}

//////////////////////////////////////

void XOpps::matMul(matrix *m1, matrix *m2, matrix *store) {
  int index = 0;

  // std::cout << "MAT MUL INITIATED WITH: \n";
  // XUtils::printMatrix(m1);
  //  XUtils::printMatrix(m2);

  if (m1->c == m2->r) {

  } else {
    std::cout << "INVALID DIMENTION OF MATRIX";
    return;
  }

  for (int i = 0; i < m1->r; i++) {
    for (int j = 0; j < m2->c; j++) {
      float sum = 0;
      for (int f = 0; f < m2->r; f++) {
        sum = sum + (m2->data[j + (f * m2->c)] * m1->data[(i * m1->c) + f]);
        store->data[index] = sum;
      }
      index++;
    }
  }

  // XUtils::printMatrix(store);
  // std::cout << "DONE : \n";
};

void XOpps::elementWiseMatMul(const matrix *m1, const matrix *m2,
                              matrix *store) {
  for (int i = 0; i < m1->l; i++) {
    store->data[i] = m1->data[i] * m2->data[i];
  };
};

void XOpps::matAdd(matrix *m1, matrix *m2, matrix *store) {
  if (m1->l != m2->l) {
    std::cout << "WARNING: invalid matrix dimensions \n";
    return;
  }

  for (int i = 0; i < m1->l; i++) {
    if (i > store->l - 1) {
      std::cout << "WARNING: matrix memory is insufficient. working with what "
                   "we got already.. \n";
      break;
    }

    float sum = m1->data[i] + m2->data[i];
    store->data[i] = sum;
  }
}
void XOpps::transpose(matrix *a) {
  int linearindex = 0;
  float *tempArray;
  tempArray = (float *)malloc(sizeof(float) * a->l);

  // do work

  for (int i = 0; i < a->c; i++) {
    for (int j = 0; j < a->r; j++) {

      int ind = i + (j * a->c);
      float entry = a->data[ind];

      tempArray[linearindex] = entry;
      linearindex++;
    }
  }
  free(a->data);
  a->data = tempArray;
  int rr = a->r;
  a->r = a->c;
  a->c = rr;
}

void XOpps::scalerMul(matrix *m1, float num) {
  float *tempArray;
  tempArray = (float *)malloc(sizeof(float) * m1->l);

  for (int i = 0; i < m1->l; i++) {
    tempArray[i] = m1->data[i] * num;
  }
  free(m1->data);
  m1->data = tempArray;
}

void freeMatrix(matrix *mat) {
  free(mat->data);
  delete mat;
}
