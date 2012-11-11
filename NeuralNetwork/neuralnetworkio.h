#ifndef NEURALNETWORKIO_H
#define NEURALNETWORKIO_H

#include "neuralnetwork.h"

class NeuralNetworkIO
{
protected:
    NeuralNetworkIO() {}
    NeuralNetworkIO(NeuralNetwork& nn) { this->nn = &nn;}

    void connectToNeuralNetwork(NeuralNetwork& nn) {this->nn = &nn;}

    NeuralNetwork* nn;

};

#endif // NEURALNETWORKIO_H
