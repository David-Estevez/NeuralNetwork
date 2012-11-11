#ifndef NNINPUT_H
#define NNINPUT_H

#include <iostream>
#include <vector>

#include "neuralnetworkio.h"
#include "neuralnetwork.h"
#include "matrix.h"

class NNInput: NeuralNetworkIO
{
protected:
    NNInput() {}
    NNInput(NeuralNetwork& nn): NeuralNetworkIO(nn) {}

    virtual void loadInput();
    virtual void loadWeights();
    virtual void loadTrainingExamples();

 private:
    std::vector<Matrix> weights;
    std::vector<double> input;

    //-- std::vector<TrainingExample> TS;
};

#endif // NNINPUT_H
