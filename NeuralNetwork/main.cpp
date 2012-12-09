
#include "neuralnetwork.h"
#include "nnfileinput.h"
#include "nnstdoutput.h"
#include "nnfileoutput.h"
#include "nntrainer.h"

#include <iostream>
#include <string>

//-- ANSI terminal escape sequences:
static const std::string CLEAR_SCREEN = "\033[2J";
static const std::string HOME_SCREEN = "\033[0;0H";
static const std::string RESET_FORMAT = "\033[0m";
static const std::string BOLD = "\033[1m";
static const std::string PURPLE = "\033[0;35m";


void showMainMenu( int selPos = -1 );

int main( int argc, char *argv[])
{
    int pos = -1;
    do
    {
	showMainMenu( pos );
	std::cin >> pos;
    }
    while (pos != -1);

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
    NNTrainer trainingMod( nn );
    NNFileInput inputMod( nn , trainingMod);

    //-- Add file paths
    inputMod.addWeightsFile( "../Sample data/Theta1.txt");
    inputMod.addWeightsFile( "../Sample data/Theta2.txt");

    inputMod.setInputFile( argv[1] );

    inputMod.addTrainingSetFile( "../Sample data/examples_input.txt");
    inputMod.addTrainingSetFile( "../Sample data/examples_output_2.txt");

    //-- Load data
    inputMod.loadWeights();
    inputMod.loadInput();
    inputMod.loadTrainingExamples();

    //-- Train network
    trainingMod.trainNetwork();

    //-- Create std output module:
    NNStdOutput outputMod( nn );

    outputMod.outputInput();
    outputMod.outputGuess();

    NNFileOutput outputMod2( nn);
    outputMod2.setWeightsFile( "../Test/myFile.txt");
    outputMod2.setInputFile( "../Test/myInput.txt");
    outputMod2.setGuessFile( "../Test/guess.txt");

   // outputMod2.outputWeights();
   // outputMod2.outputInput();
   // outputMod2.outputGuess();




    }
    else
    {
	std::cout << "Error: incorrect number of parameters" << std::endl;
    }
    return 0;
}

void showMainMenu( int selPos )
{
    //-- Clear terminal:
    std::cout << CLEAR_SCREEN;
    std::cout << HOME_SCREEN;
    std::cout << RESET_FORMAT;

    //-- Display menu:
    for (int i = 0; i < 80 ; i++)
	std::cout << '#';

    std::cout << std::endl << PURPLE << BOLD <<  "Neural Network in C++" << RESET_FORMAT << std::endl;

    for (int i = 0; i < 80 ; i++)
	std::cout << '#';

    //-- Choices:
    std::cout << std::endl;
    if (selPos == 0)	{ std::cout << '>' << BOLD; } else { std::cout << RESET_FORMAT; }
    std::cout << "Network configuration" << std::endl;

    if (selPos == 1)	{ std::cout << '>' << BOLD; } else { std::cout << RESET_FORMAT; }
    std::cout << "Guess number" << std::endl;

    if (selPos == 2)	{ std::cout << '>' << BOLD; } else { std::cout << RESET_FORMAT; }
    std::cout << "Train Neural Network" << std::endl;

    if (selPos == 3)	{ std::cout << '>' << BOLD; } else { std::cout << RESET_FORMAT; }
    std::cout << "Save" << std::endl;

    if (selPos == 4)	{ std::cout << '>' << BOLD; } else { std::cout << RESET_FORMAT; }
    std::cout << "Exit" << std::endl;

}
