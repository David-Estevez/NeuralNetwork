#ifndef NNINPUT_H
#define NNINPUT_H

#include <vector>

#include "neuralnetworkio.h"
#include "neuralnetwork.h"
#include "matrix.h"

//-- Temporal fix:
struct TrainingExample
{
std::vector<double> x, y;
};

class NNInput: public NeuralNetworkIO
{
protected:
    NNInput() {}
    NNInput(NeuralNetwork& nn): NeuralNetworkIO(nn) {}

    ~NNInput();

    virtual void loadInput() = 0;
    virtual void loadWeights() = 0;
    virtual void loadTrainingExamples() = 0;

    std::vector<Matrix *> weights;
    Matrix *input;
    std::vector<TrainingExample> TS;
};

#endif // NNINPUT_H
