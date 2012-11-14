#include "neuron.h"
#include "layer.h"
#include "neuralnetwork.h"
#include "nnfileinput.h"

#include "matrix.h"

#include "data.h"


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

    NNFileInput inputMod( nn );/*
    inputMod.addWeightsFile( "../Sample data/Theta1.txt");
    inputMod.addWeightsFile( "../Sample data/Theta2.txt");

    inputMod.setInputFile( argv[1] );

    inputMod.loadInput();
    inputMod.loadWeights();
    */

    //-- Matrices loaded from file:
    Matrix * Theta11 = inputMod.loadMatrix( "../Sample data/Theta1.txt" );
    Matrix * Theta22 = inputMod.loadMatrix( "../Sample data/Theta2.txt" );

    Matrix Theta1 = returnTheta1();
    Matrix Theta2 = returnTheta2();


    std::vector<Matrix *> myWeights;
    myWeights.push_back( &Theta1);
    myWeights.push_back( &Theta2);

    nn.setWeights( myWeights);

    std::vector<double> mV1 = returnInput1();
    std::vector<double> mV2 = returnInput2();

    nn.setInput( mV1 );

    nn.refresh();

    std::cout << (*Theta11 == Theta1) << " " << (*Theta22 == Theta2) << std::endl;

    std::cout << "System output for input file: " << std::endl
	      << nn.getOutput() << std::endl;

    }
    else
    {
	std::cout << "Error: incorrect number of parameters" << std::cout;
    }
    return 0;
}
