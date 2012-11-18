#include "neuron.h"
#include "layer.h"
#include "neuralnetwork.h"
#include "nnfileinput.h"
#include "nnstdoutput.h"

#include "matrix.h"


#include <iostream>


int main( int argc, char *argv[])
{
    if (argc == 2)
    {
    //-- Debuggin' main routine::
    //--------------------------------------------------

    std::vector<int> sizeofnetwork;
    sizeofnetwork.push_back(400);
    sizeofnetwork.push_back(25);
    sizeofnetwork.push_back(10);

    NeuralNetwork nn( sizeofnetwork);

    NNFileInput inputMod( nn );
    inputMod.addWeightsFile( "../Sample data/Theta1.txt");
    inputMod.addWeightsFile( "../Sample data/Theta2.txt");

    inputMod.setInputFile( argv[1] );

    inputMod.loadInput();
    inputMod.loadWeights();

    nn.refresh();

    NNStdOutput outputMod( nn );

    outputMod.outputOutput();

    }
    else
    {
	std::cout << "Error: incorrect number of parameters" << std::cout;
    }
    return 0;
}
