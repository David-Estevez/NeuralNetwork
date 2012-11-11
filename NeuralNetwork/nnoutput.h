#ifndef NNOUTPUT_H
#define NNOUTPUT_H

#include "neuralnetwork.h"
#include "neuralnetworkio.h"

class NNOutput : public NeuralNetworkIO
{
protected:
    NNOutput() {}
    NNOutput( NeuralNetwork& nn): NeuralNetworkIO( nn) {}

    virtual void showWeights() = 0;
    virtual void showOutput() = 0;
};

#endif // NNOUTPUT_H
