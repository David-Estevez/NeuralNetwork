#ifndef NNINPUT_H
#define NNINPUT_H

#include <vector>

#include "neuralnetworkio.h"
#include "neuralnetwork.h"
#include "matrix.h"

//-- Temporal fix:
struct TrainingExample;

class NNInput: NeuralNetworkIO
{
protected:
    NNInput() {}
    NNInput(NeuralNetwork& nn): NeuralNetworkIO(nn) {}

    virtual void loadInput() = 0;
    virtual void loadWeights() = 0;
    virtual void loadTrainingExamples() = 0;

    std::vector<Matrix> weights;
    Matrix input;

    std::vector<TrainingExample> TS;
};

#endif // NNINPUT_H
