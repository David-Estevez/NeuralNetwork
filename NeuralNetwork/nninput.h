#ifndef NNINPUT_H
#define NNINPUT_H

#include <iostream>
#include <vector>

#include "neuralnetworkio.h"
#include "NeuralNetwork"

class NNInput: NeuralNetworkIO
{
public:
    NNInput();
    NNInput( const NeuralNetwork& nn): NeuralNetworkIO(nn) {}

    virtual void loadWeights();
    virtual void loadTrainingExamples();
    virtual void loadInput();
};

#endif // NNINPUT_H
