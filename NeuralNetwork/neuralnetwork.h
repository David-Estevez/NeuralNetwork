#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <iostream>

#include "layer.h"
#include "matrix.h"

class NeuralNetwork
{
public:
    NeuralNetwork( int, int, ...);
    NeuralNetwork( std::vector<int> );

    ~NeuralNetwork();

    //-- Input functions:
    void setInput( std::vector<double> input);
    void setInput( double * input, int size);

    void setWeights( std::vector<Matrix> theta);

    //-- Output functions:
    std::vector<double> getOutput();
    std::vector<Matrix> getWeights();

    //-- Other functions:
    void refresh();	    //-- Updates the output

private:
    Layer *inputLayer;
    std::vector<Layer> hiddenLayer;
    Layer *outputLayer;

    int l;  //-- Number of layers

    std::vector<double> output;

    //-- Hide default constructor
    NeuralNetwork();

};

#endif // NEURALNETWORK_H
