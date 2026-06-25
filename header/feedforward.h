#pragma once
#include "../slib/xentorch/header/declaration.h"
#include "activationfunc.h"
#include "neuralnet.h"
#include <cstdlib>

inline float *feedforward(NeuralNet *Network, float *array) {
  for (int i = 0; i < Network->layers[0].node_data.l; i++) {
    Network->layers[0].node_data.data[i] = array[i];
  }

  for (int i = 0; i < Network->numLayers - 1; i++) {

    XOpps::matMul(&Network->layers[i].node_data, &Network->layers[i].weights,
                  &Network->layers[i + 1].node_data);

    XOpps::matAdd(&Network->layers[i + 1].node_data,
                  &Network->layers[i + 1].bias,
                  &Network->layers[i + 1].node_data);

    ApplyActivation(&Network->layers[i + 1].node_data,
                    Network->layers[i + 1].act);
  }
  int lastLayerNodeSize = Network->layers[Network->numLayers - 1].node_data.l;
  int lastLayerNSIZE = lastLayerNodeSize;
  float *returnResult;

  returnResult = (float *)malloc(sizeof(float) * lastLayerNodeSize);
  // NEED TO FREE returnResult!

  for (int i = 0; i < lastLayerNodeSize; i++) {
    returnResult[i] = Network->layers[Network->numLayers - 1].node_data.data[i];
  }
  return returnResult;
};
