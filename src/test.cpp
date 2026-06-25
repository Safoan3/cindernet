#include "../header/feedforward.h"
#include "../header/neuralnet.h"
#include "../slib/xentorch/header/declaration.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <thread>

std::random_device r15;
std::mt19937 gen3(r15());
std::uniform_real_distribution<float> dist1(-1.0f, 1.0f);

void matrixTest() {
  matrix *m1 = newMatrix(9, 5);
  matrix *m2 = newMatrix(5, 10);
  matrix *s = newMatrix(9, 10);
  XUtils::fillMatrix(m1);
  XUtils::fillMatrix(m2);
  XOpps::matMul(m1, m2, s);
  XUtils::printMatrix(m1);
  XUtils::printMatrix(m2);
  XUtils::printMatrix(s);
  XUtils::printMatrix(m1);
  XOpps::transpose(m1);
  XUtils::printMatrix(m1);
}

void NeuralNetworkTest() {
  nNetworkSet networkSettings = InitNetSettings(4);
  addDense(networkSettings, 3, LeakyRely);
  addDense(networkSettings, 128, LeakyRely);
  addDense(networkSettings, 1028, LeakyRely);
  addDense(networkSettings, 1, LeakyRely);

  /*
  for (int i = 0; i < networkSettings.numLayer; i++) {

    std::cout << "NODES : " << networkSettings.LayersSett[i].nodes << " "
              << networkSettings.LayersSett[i].activation_function << std::endl;
  }

  std::cout << "TEST 2" << "\n";
*/

  NeuralNet *network1;
  network1 = NewNeuralNetwork(networkSettings);
  /*
    std::cout << "TEST 3" << "\n";

    for (int i = 0; i < network1->numLayers; i++) {
      std::cout << "weight data: \n";
      XUtils::printMatrix(&(network1->layers[i].weights));
      std::cout << "\n";
    }

    std::cout << "TEST -4 FEEDFORWARD TEST \n";
  */

  //  while (true) {
  auto now = std::chrono::high_resolution_clock::now();

  float inputnet[3] = {1.2, 5.2, 9.1};
  float *Output = feedforward(network1, inputnet);
  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  auto now1 = std::chrono::high_resolution_clock::now();

  std::cout << std::to_string(Output[0]) << "\n";
  free(Output);

  float timeEscaped;
  timeEscaped = std::chrono::duration<float>(now1 - now).count();
  timeEscaped = timeEscaped * 1000;

  std::cout << "operation lasted " + std::to_string(timeEscaped) + "ms \n";

  //  std::this_thread::sleep_for(std::chrono::milliseconds(1111));
  // }

  /*
  std::cout << "Rcursive sum test \n";

  matrix *testMat = newMatrix(4, 4);
  XUtils::fillRandom(testMat);
  matrix *bias;
  bias = newMatrix(4, 4);
  float dataX[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  XUtils::setData(bias, dataX);


  for (int i = 0; i < 100; i++) {
    std::cout << "you never take me to bangladesh you never cook sausage in an "
                 "open flame \n";
    XUtils::printMatrix(testMat);

    XOpps::matAdd(bias, testMat, testMat);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }*/
}

int main() {
  // matrixTest();

  NeuralNetworkTest();

  return 0;
}
