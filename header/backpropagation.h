#pragma once
#include "../slib/xentorch/header/declaration.h"
#include "activationfunc.h"
#include "feedforward.h"
#include "neuralnet.h"
#include <cmath>
#include <cstdlib>

namespace lossFunctions {

namespace MeanSquareEv {
inline float exec(float output, float expected) {
  float diff = expected - output;

  return .5 * diff * diff;
}
inline float derivative(float output, float expected) {
  return output - expected;
}
} // namespace MeanSquareEv

} // namespace lossFunctions

inline float *Vanilla(NeuralNet *net) { return 0; }

namespace Backprogation {
namespace Gradient { // returns a big 1D array of gradients

}
} // namespace Backprogation
