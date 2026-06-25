#pragma once

#include "../slib/xentorch/header/declaration.h"
#include "activationfunc.h"
#include <cmath>
#include <iostream>

/// Build struct
struct DenseLayer {
  int nodes;
  ActivationFuncitonName activation_function;
};
struct nNetworkSet {
  int numLayer;
  DenseLayer *LayersSett;
  int currentLayerIndex;
};

// real deal
struct neuralnetworklayer {
  matrix weights;
  matrix node_data;
  matrix bias;
  ActivationFuncitonName act;
};
struct NeuralNet {
  neuralnetworklayer *layers;
  int numLayers;
};

NeuralNet *NewNeuralNetwork(nNetworkSet &n1);
void addDense(nNetworkSet &n1, int nodes, ActivationFuncitonName name);

nNetworkSet InitNetSettings(int numLayers);
