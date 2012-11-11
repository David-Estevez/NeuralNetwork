#ifndef NNFILEINPUT_H
#define NNFILEINPUT_H

#include <fstream>
#include <vector>
#include <cstdlib>

#include "nninput.h"
#include "neuralnetwork.h"
#include "matrix.h"

class NNFileInput : public NNInput
{
public:
    NNFileInput() {}
    NNFileInput(NeuralNetwork& nn): NNInput(nn) {}

    virtual void loadWeights();
    virtual void loadTrainingExamples();
    virtual void loadInput();

    //-- Load a matrix from a file:
    Matrix& loadMatrix( const char *filePath);

    //-- Store the file path:
    void setWeightsFile( const char **filePath);
    void setInputFile( const char *filePath);
    void setTrainingSetFile( const char *filepath, const int n);
private:
    //-- Variables storing file path
    char **weightsFile;
    char *inputFile;
    char **trainingSetFile;
};

#endif // NNFILEINPUT_H
