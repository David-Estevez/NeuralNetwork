
#include "neuralnetwork.h"
#include "nnfileinput.h"
#include "nnstdoutput.h"
#include "nnfileoutput.h"
#include "nntrainer.h"
#include "terminalmenu.h"

#include <iostream>
#include <string>

void menuSetup( );

int main( int argc, char *argv[])
{
    menuSetup();

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
  // trainingMod.trainNetwork();

    //-- Create std output module:
    NNStdOutput outputMod( nn );

    TerminalInterface interface( "Input");
    interface.show();
    std::cout << std::endl << "\033[1A";
    outputMod.outputInput();
    std::cin.get();

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

void menuSetup( )
{

    TerminalMenu mainMenu ( "Neural Network in C++" );
    mainMenu.addOption( "Network configuration" );
    mainMenu.addOption( "Guess number" );
    mainMenu.addOption( "Train Neural Network" );
    mainMenu.addOption( "Save" );
    mainMenu.addOption( "Exit" );

    int pos = -1;
    do
    {
	mainMenu.setCurrent( pos );
	mainMenu.show();
	std::cin >> pos;
    }
    while (pos != -1);

    TerminalMenu otherMenu ("Other menu");
    otherMenu.show();
}


