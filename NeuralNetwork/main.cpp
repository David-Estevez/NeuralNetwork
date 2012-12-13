
#include "neuralnetwork.h"
#include "nnfileinput.h"
#include "nnstdoutput.h"
#include "nnfileoutput.h"
#include "nntrainer.h"
#include "terminalmenu.h"
#include "terminaltextedit.h"

#include <iostream>
#include <string>

int main( )
{
    //-- Setting up the neural network:
    //----------------------------------------------------
    //-- Create network:
    std::vector<int> sizeofnetwork;
    sizeofnetwork.push_back(400);
    sizeofnetwork.push_back(25);
    sizeofnetwork.push_back(10);

    NeuralNetwork nn( sizeofnetwork);

    //-- Create communtication modules and trainer:
    NNTrainer trainingMod( nn );
    NNFileInput inputMod( nn , trainingMod);
    NNStdOutput outputMod( nn );
    NNFileOutput outputFileMod( nn);

    //-- Set the default values for the file paths:
    inputMod.addWeightsFile( "../Sample data/Theta1.txt");
    inputMod.addWeightsFile( "../Sample data/Theta2.txt");

    inputMod.setInputFile( "../Sample data/input.txt");

    inputMod.addTrainingSetFile( "../Sample data/examples_input.txt");
    inputMod.addTrainingSetFile( "../Sample data/examples_output_2.txt");

    outputFileMod.setWeightsFile( "../Test/myFile.txt");
    outputFileMod.setInputFile( "../Test/myInput.txt");
    outputFileMod.setGuessFile( "../Test/guess.txt");


    //-- Setting up the terminal interface
    //----------------------------------------------------------------------

    //-- Main menu
    TerminalMenu mainMenu ( "Neural Network in C++" );
    mainMenu.addOption( "Network configuration" );
    mainMenu.addOption( "Guess number" );
    mainMenu.addOption( "Train Neural Network" );
    mainMenu.addOption( "Save" );
    mainMenu.addOption( "Exit" );

    //-- Configuration menu
    TerminalMenu configMenu ( "Configuration" );
    configMenu.addOption( "Edit Weight files path");
    configMenu.addOption( "Edit training set file path");
    configMenu.addOption( "Return");

    //-- Save menu
    TerminalMenu saveMenu ( "Save data to file");
    saveMenu.addOption( "Save weights to file");
    saveMenu.addOption( "Save guess to file");
    saveMenu.addOption( "Save current selected input as ascii image in file");
    saveMenu.addOption( "Return");

    //-- Load default data:
    //--------------------------------------------------------------------------
    inputMod.loadWeights();
    inputMod.loadInput();
    inputMod.loadTrainingExamples();

    //-- Main loop:
    //--------------------------------------------------------------------------
    bool running = true;
    int nextMenu_l1 = -1, nextMenu_l2 = -1, nextMenu_l3 = -1;

    while (running)
    {
	//-- Show main menu:
	if (nextMenu_l1 == -1)
	    nextMenu_l1 = mainMenu.show();

	if (nextMenu_l1 == 0)	//-- Configuration menus
	{
	    //-- Configuration menus:
	    //-----------------------------------------------------------------

	    if (nextMenu_l2 == -1)	//-- Select choice
		nextMenu_l2 = configMenu.show();

	    if (nextMenu_l2 == 0)	//-- Edit weigths files:
	    {
		//-- Create weights menu:
		std::vector<std::string> weightFile = inputMod.getWeightsFile();

		TerminalMenu weightFileMenu( "Select file path to edit: ");

		for (int i = 0; i < (int) weightFile.size(); i++)
		{
		    weightFileMenu.addOption( weightFile.at(i) );
		}

		weightFileMenu.addOption( "Return");

		//-- Select weight file:
		nextMenu_l3 = weightFileMenu.show();

		if (nextMenu_l3 < (int) weightFile.size() )
		{
		    //-- Edit some path:
		    std::string newWeightFile = weightFile.at( nextMenu_l3);
		    TerminalTextEdit weightFileTextEdit( "Edit weight matrix file path", newWeightFile );

		    weightFileTextEdit.show();

		    if (!newWeightFile.empty())
		    {
			inputMod.setWeightsFile(  newWeightFile, nextMenu_l3 );
		    }

		    nextMenu_l3 = -1;
		}
		else
		{
		    nextMenu_l3 = nextMenu_l2 = -1;
		}
	    }
	    else if (nextMenu_l2 == 1) //-- Edit training set files
	    {
		//-- Create menu:
		std::vector<std::string> trainingSetFile = inputMod.getTrainingSetFile();

		TerminalMenu trainingSetFileMenu( "Select file path to edit: ");

		for (int i = 0; i < (int) trainingSetFile.size(); i++)
		{
		    trainingSetFileMenu.addOption( trainingSetFile.at( i ) );
		}

		trainingSetFileMenu.addOption( "Return");

		//-- Get option:
		nextMenu_l3 = trainingSetFileMenu.show();

		if (nextMenu_l3 < (int) trainingSetFile.size() )
		{
		    //-- Edit some path:
		    std::string newTrainingSetFile = trainingSetFile.at( nextMenu_l3);
		    TerminalTextEdit trainingSetFileTextEdit( "Edit training set file path", newTrainingSetFile );

		    trainingSetFileTextEdit.show();

		    if (!newTrainingSetFile.empty())
		    {
			inputMod.setTrainingSetFile( newTrainingSetFile, nextMenu_l3 );
		    }

		    nextMenu_l3 = -1;
		}
		else
		{
		    nextMenu_l3 = nextMenu_l2 = -1;
		}

	    }
	    else if (nextMenu_l2 == 2)	//-- Return to upper level
	    {
		nextMenu_l1 = nextMenu_l2 = -1;
	    }
	    else			//-- Otherwise repeat same menu
	    {
		nextMenu_l2 = -1;
	    }

	}
	else if ( nextMenu_l1 == 1) //-- Guess number
	{
	    //-- Guess number
	    //--------------------------------------------------
	    //-- Show header:
	    TerminalInterface interface( "Input file selection");
	    interface.show();

	    //-- Ask for input file:
	    std::cout << "Choose input file:>";
	    std::string inputFile;
	    std::cin >> inputFile;

	    if ( !inputFile.empty() )
		inputMod.setInputFile( inputFile );

	    inputMod.loadInput();

	    //-- Display input:
	    interface.setTitle("Neural Network guess");
	    interface.show();
	    std::cout << std::endl << "\033[1A";
	    outputMod.outputInput();

	    //-- Display guess:
	    outputMod.setDisplayCursor( 64, 4);
	    outputMod.outputGuess();

	    std::cin.get(); //-- Only one of this does not work
	    std::cin.get();

	    nextMenu_l1 = -1;
	}
	else if ( nextMenu_l1 == 2) //-- Training network
	{
	    //-- Training network
	    //----------------------------------------------------------------------
	    //-- Show header:
	    TerminalInterface header( "Training Neural Network");
	    header.show();

	    std::cout << std::endl;
	    std::cout << "Set number of iteration (default: 1000):>";
	    int aux1;
	    std::cin >> aux1;
	    trainingMod.setIter( aux1);

	    std::cout << "Set gradient descend severity alpha (default: 1):>";
	    double aux2;
	    std::cin >> aux2;
	    trainingMod.setAlpha(aux2);

	    std::cout << "Set regularization coefficient lambda (default: 1):>";
	    std::cin >> aux2;
	    trainingMod.setLambda(aux2);

	    //-- Load training examples:
	    inputMod.loadTrainingExamples();

	    //-- Show header:
	    header.show();
	    std::cout << std::endl;

	    //-- Train:
	    trainingMod.trainNetwork();

	    nextMenu_l1 = -1;
	}
	else if ( nextMenu_l1 == 3) //-- Save data into a file
	{
	    //-- Save data into a file
	    //-----------------------------------------------
	    if (nextMenu_l2 == -1)
		nextMenu_l2 = saveMenu.show();

	    if ( nextMenu_l2 == 0)  //-- Save weights to file
	    {
		//-- Save weights to file
		//----------------------------------------

		//-- Get previous value of file path (without the end of name format)
		std::string newPath = outputFileMod.getWeightsFile().at(0).substr( 0, outputFileMod.getWeightsFile().at(0).find("-0.txt") );
		newPath += ".txt";

		//-- Create menu:
		TerminalTextEdit filePathTextEdit( "Choose file path for weight matrices files:", newPath);

		filePathTextEdit.show();

		//-- Save file:
		if ( !newPath.empty() )
		{
		    outputFileMod.setWeightsFile( newPath);
		    outputFileMod.outputWeights();
		}

		nextMenu_l2 = -1;
	    }
	    else if (nextMenu_l2 == 1) //-- Save guess to file
	    {
		    //-- Save guess to file
		    //----------------------------------------

		    //-- Get previous value of file path
		    std::string newPath = outputFileMod.getGuessFile();

		    //-- Create menu:
		    TerminalTextEdit filePathTextEdit( "Choose file path for guess file:", newPath);

		    filePathTextEdit.show();

		    //-- Save file:
		    if ( !newPath.empty() )
		    {
			outputFileMod.setGuessFile( newPath);
			outputFileMod.outputGuess();
		    }

		    nextMenu_l2 = -1;
	    }
	    else if (nextMenu_l2 == 2) //-- Save ascii image to file
	    {
		//-- Save ascii image to file
		//----------------------------------------

		//-- Get previous value of file path
		std::string newPath = outputFileMod.getInputFile();

		//-- Create menu:
		TerminalTextEdit filePathTextEdit( "Choose file path for ascii image file:", newPath);

		filePathTextEdit.show();

		//-- Save file:
		if ( !newPath.empty() )
		{
		    outputFileMod.setInputFile( newPath);
		    outputFileMod.outputInput();
		}

		nextMenu_l2 = -1;
	    }
	    else if (nextMenu_l2 == 3) //-- Return to upper level
	    {
		//-- Return to upper level:
		nextMenu_l1 = nextMenu_l2 = -1;
	    }
	    else		       //-- Otherwise stay at this level
	    {
		//-- Return to this level:
		nextMenu_l2 = -1;
	    }

	}
	else if ( nextMenu_l1 == 4) //-- Exit
	{
	    running = false;
	}
	else
	{
	    nextMenu_l1 = -1;
	}
    }

    return 0;
}
