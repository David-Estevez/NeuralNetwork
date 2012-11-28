#include "neuron.h"
#include "layer.h"
#include "neuralnetwork.h"
//#include "nnfileinput.h"
//#include "nnstdoutput.h"
//#include "nnfileoutput.h"

#include "matrix.h"


#include <iostream>


int main( int argc, char *argv[])
{
    if (argc == 2)
    {
    //-- Debuggin' main routine::
    //--------------------------------------------------

    //-- Create network:
    std::vector<int> sizeofnetwork;
    sizeofnetwork.push_back(400);
    sizeofnetwork.push_back(25);
    sizeofnetwork.push_back(10);

    NeuralNetwork nn( sizeofnetwork);

 /*  //-- Create input module
    NNFileInput inputMod( nn );
    inputMod.addWeightsFile( "../Sample data/Theta1.txt");
    inputMod.addWeightsFile( "../Sample data/Theta2.txt");

    inputMod.setInputFile( argv[1] );

    //-- Load data
    inputMod.loadInput();
    inputMod.loadWeights();

    nn.refresh();

    //-- Create std output module:
    NNStdOutput outputMod( nn );

    outputMod.outputInput();
    outputMod.outputGuess();

    NNFileOutput outputMod2( nn);
    outputMod2.setWeightsFile( "../Test/myFile.txt");
    outputMod2.setInputFile( "../Test/myInput.txt");
    outputMod2.setGuessFile( "../Test/guess.txt");

    outputMod2.outputWeights();
    outputMod2.outputInput();
    outputMod2.outputGuess();*/

    Matrix mat1( 2, 3);
    mat1.set( 0, 0, 1);
    mat1.set( 0, 1, 2);
    mat1.set( 0, 2, 6);
    mat1.set( 1, 0, 3);
    mat1.set( 1, 1, 4);
    mat1.set( 1, 2, 5);

    std::cout << mat1 << std::endl;
    Matrix mat2 = mat1.transpose();
    std::cout << mat2 << std::endl;
    Matrix mat3 = mat1*mat2;
    std::cout << mat3 << std::endl;
    }
    else
    {
	std::cout << "Error: incorrect number of parameters" << std::endl;
    }
    return 0;
}
