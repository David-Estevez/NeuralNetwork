#ifndef NNINPUT_H
#define NNINPUT_H

#include <vector>

#include "neuralnetworkio.h"
#include "neuralnetwork.h"
#include "matrix.h"

class NNInput: NeuralNetworkIO
{
protected:
    NNInput() {}
    NNInput(NeuralNetwork& nn): NeuralNetworkIO(nn) {}

    virtual void loadInput() = 0;
    virtual void loadWeights() = 0;
    virtual void loadTrainingExamples() = 0;

 private:
    std::vector<Matrix> weights;
    std::vector<double> input;

    //-- std::vector<TrainingExample> TS;
};

#endif // NNINPUT_H
