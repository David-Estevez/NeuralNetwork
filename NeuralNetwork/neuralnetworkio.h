#ifndef NEURALNETWORKIO_H
#define NEURALNETWORKIO_H

#include "neuralnetwork.h"

class NeuralNetworkIO
{
protected:
    NeuralNetworkIO();
    NeuralNetworkIO(const NeuralNetwork& nn) { this->nn = &nn;}

    void connectToNeuralNetwork(const NeuralNetwork& nn) {this->nn = &nn;}

private:
    NeuralNetwork* nn;

};

#endif // NEURALNETWORKIO_H
