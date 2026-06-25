#include "../header/neuralnet.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

nNetworkSet InitNetSettings(int numLayers) {
  nNetworkSet n1;
  n1.numLayer = numLayers;
  n1.LayersSett = (DenseLayer *)malloc(sizeof(DenseLayer) * n1.numLayer);
  n1.currentLayerIndex = 0;

  return n1;
};

void addDense(nNetworkSet &n1, int nodes, ActivationFuncitonName act_function) {
  int index = n1.currentLayerIndex;
  DenseLayer laysetttt;
  laysetttt.activation_function = act_function;
  laysetttt.nodes = nodes;
  n1.LayersSett[index] = laysetttt;
  n1.currentLayerIndex++;
};

NeuralNet *NewNeuralNetwork(nNetworkSet &n1) {
  NeuralNet *ReturnNetwork = new NeuralNet;
  ReturnNetwork->layers =
      (neuralnetworklayer *)malloc(sizeof(neuralnetworklayer) * n1.numLayer);

  ReturnNetwork->numLayers = n1.numLayer;

  for (int i = 0; i < n1.numLayer; i++) {

    neuralnetworklayer &xLay = ReturnNetwork->layers[i];
    int nextLayerNodes = 0;
    if (i + 1 <= n1.numLayer) {
      nextLayerNodes = n1.LayersSett[i + 1].nodes;
    }
    matrix *w1Temp;
    matrix *n1nodes;
    matrix *tempBias;

    n1nodes = newMatrix(1, n1.LayersSett[i].nodes);
    if (nextLayerNodes == 0) {
      w1Temp = newMatrix(0, 0);
    } else {
      w1Temp = newMatrix(n1.LayersSett[i].nodes, nextLayerNodes);
    }
    tempBias = newMatrix(1, n1nodes->c);

    XUtils::fillRandom(tempBias);
    // XUtils::fillRandom(n1nodes);
    XUtils::fillRandom(w1Temp);

    // std::cout << "current nodes : " << w1Temp->r
    //          << " later nodes : " << w1Temp->c << "done \n";

    xLay.weights = (*w1Temp);
    xLay.node_data = (*n1nodes);
    xLay.bias = (*tempBias);
    xLay.act = n1.LayersSett[i].activation_function;

    xLay.node_data.data = (float *)malloc(sizeof(float) * xLay.node_data.l);
    memcpy(xLay.node_data.data, n1nodes->data,
           sizeof(float) * xLay.node_data.l);

    xLay.weights.data = (float *)malloc(sizeof(float) * xLay.weights.l);
    memcpy(xLay.weights.data, w1Temp->data, sizeof(float) * xLay.weights.l);

    xLay.bias.data = (float *)malloc(sizeof(float) * xLay.bias.l);
    memcpy(xLay.bias.data, tempBias->data, sizeof(float) * xLay.bias.l);

    freeMatrix(n1nodes);
    freeMatrix(w1Temp);
    freeMatrix(tempBias);

    // XUtils::printMatrix(&xLay.weights);
  }

  return ReturnNetwork;
};
