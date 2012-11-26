#include "neuron.h"
#include "layer.h"
#include "neuralnetwork.h"
#include "nnfileinput.h"
#include "nnstdoutput.h"
#include "nnfileoutput.h"

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

    //-- Create input module
    NNFileInput inputMod( nn );
    inputMod.addWeightsFile( "../Sample data/Theta1.txt");
    inputMod.addWeightsFile( "../Sample data/Theta2.txt");

    inputMod.setInputFile( argv[1] );

    inputMod.addTrainingSetFile( "../Sample data/examples_input.txt");
    inputMod.addTrainingSetFile( "../Sample data/examples_output_2.txt");

    //-- Load data
    inputMod.loadInput();
    inputMod.loadWeights();
    inputMod.loadTrainingExamples();

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
    outputMod2.outputGuess();

    for( int i = 0; i < 5000; i+=500)
std::cout << inputMod.trainingSet.at(i).y << std::endl;

    }
    else
    {
	std::cout << "Error: incorrect number of parameters" << std::endl;
    }
    return 0;
}
