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


private:
    //-- Variables storing file path
    std::vector<std::string> weightsFile;
    std::string inputFile;
    std::vector<std::string> trainingSetFile;

    //-- Load a matrix from a file:
    Matrix& loadMatrix( const std::string filePath);

    //-- Store the file path:
    void addWeightsFile( const std::string filePath);
    void setWeightsFile( const std::string filePath, const int n);

    void setInputFile( const std::string filePath);

    void addTrainingSetFile( const std::string filePath);
    void setTrainingSetFile( const std::string filePath, const int n);

};

#endif // NNFILEINPUT_H
