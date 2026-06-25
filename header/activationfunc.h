#pragma once
#include "../slib/xentorch/header/declaration.h"
#include <cmath>

inline float Exp = 2.71828;

enum ActivationFuncitonName {
  Sigmoid,
  LeakyRely,
};

namespace ActivationFunctions {

namespace LeakyRelu {
inline float alpha = 0.01;

inline float exec(float x) {
  float cpData = x;
  if (x < 0) {
    cpData = x * alpha;
  }
  return cpData;
};

inline void exec(matrix *m1) {
  for (int i = 0; i < m1->l; i++) {
    m1->data[i] = exec(m1->data[i]);
  }
};
inline float derivative(float x) {
  if (x < 0) {
    return x * alpha;
  }
  return x;
};
inline void derivative(matrix *m) {
  for (int i = 0; i < m->l; i++) {
    float elades;
    elades = derivative(m->data[i]);
    m->data[i] = elades;
  }
}
} // namespace LeakyRelu

namespace sigmoid {

inline float exec(float x) { return 1 / (1 + std::exp(-x)); };

inline void exec(matrix *m1) {
  for (int i = 0; i < m1->l; i++) {
    m1->data[i] = exec(m1->data[i]);
  }
};
inline float derivative(float x) {
  float s = exec(x);

  return s * (1.0f - s);
};
} // namespace sigmoid

} // namespace ActivationFunctions
  //
  //

inline void ApplyActivation(matrix *m, ActivationFuncitonName name) {
  if (name == Sigmoid) {
    ActivationFunctions::sigmoid::exec(m);
  }
  if (name == LeakyRely) {
    ActivationFunctions::LeakyRelu::exec(m);
  }
}
