#include "neuron.h"
#include "layer.h"
#include "neuralnetwork.h"
#include "nnfileinput.h"

#include "matrix.h"



#include <iostream>


int main()
{

    //-- Debuggin' main routine::
    //--------------------------------------------------

    std::vector<int> sizeofnetwork;
    sizeofnetwork.push_back(400);
    sizeofnetwork.push_back(25);
    sizeofnetwork.push_back(10);

    NeuralNetwork nn( sizeofnetwork);

    NNFileInput inputMod( nn );
    inputMod.addWeightsFile( "../sample data/Theta1.txt");
    inputMod.addWeightsFile( "../sample data/Theta2.txt");

    inputMod.setInputFile( "./input.txt");

    inputMod.loadInput();
    inputMod.loadWeights();

    nn.refresh();

    std::cout << nn.getOutput();


}
