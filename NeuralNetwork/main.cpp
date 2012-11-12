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

    std::vector<int> sizeofnetwork = { 400, 25, 10 };
    NeuralNetwork nn( sizeofnetwork);

    NNFileInput inputMod( nn );
    inputMod.addWeightsFile( "../sample data/Theta1.txt");
    inputMod.addWeightsFile( "../sample data/Theta2.txt");

    inputMod.setInputFile( "./input.txt");


}
