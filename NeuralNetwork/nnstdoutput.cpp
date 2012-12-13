#include "nnstdoutput.h"

//-- Data interface
//------------------------------------------------------------------------
void NNStdOutput::setDisplayCursor(int col, int row)
{
    displayColumn = col;
    displayRow = row;
}

//-- Std Output interface:
//------------------------------------------------------------------------
void NNStdOutput::outputWeights()
{
    //-- Set precision to 2, forcing to output float numbers:
    std::cout.precision(2);
    std::cout.setf( std::ios::fixed );

    for (int i = 0; i < (int) nn->getWeights().size(); i++)
    {
	std::cout << "Weight matrix for layer " << i+1 << ":" << std::endl;
	std::cout << *nn->getWeights().at(i) << std::endl;
    }
}

void NNStdOutput::outputGuess()
{
    //-- Set precision to 2, forcing to output float numbers:
    std::cout.precision(2);
    std::cout.setf( std::ios::fixed );

    //-- Set position to output the text:
    std::string escapeSetCursor, escapeRelMovement;

    if ( displayColumn == -1 || displayRow == -1)
    {
	escapeSetCursor = escapeRelMovement == "";
    }
    else
    {
	//-- Num to char conversion:
	char charDisplayCol[3], charDisplayRow[3];

	sprintf( charDisplayCol, "%d", displayColumn);
	sprintf( charDisplayRow, "%d", displayRow);

	escapeSetCursor = "\033[" + std::string(charDisplayRow) +
			    ";" + std::string( charDisplayCol) + "H";

	sprintf( charDisplayCol, "%d", displayColumn-1);
	escapeRelMovement = "\033[" + std::string( charDisplayCol ) + "C";
    }


    //-- Display complete statistics while looking for highest:
    std::cout << escapeSetCursor;
    std::cout << "Results (%): " << std::endl;
    std::cout << escapeRelMovement;
    std::cout << "-----------------" << std::endl;

    //-- Store the highest at each step:
    double highest = nn->getOutput().at(0);
    int highest_pos = 0;

    for (int i = 0; i < (int) nn->getOutput().size(); i++)
    {
	//-- Display element:
	std::cout << escapeRelMovement;
	std::cout << "Category " << (i != nn->getOutput().size()-1?i+1:0) ;
	std::cout << ": "
		 << nn->getOutput().at(i) * 100<< std::endl;

	//-- Look for highest
	if ( nn->getOutput().at(i) > highest)
	{
	    highest = nn->getOutput().at(i);
	    highest_pos = i;
	}
    }

    // -- Output results:

    std::cout << escapeRelMovement;
    std::cout << "-----------------" << std::endl;
    std::cout << escapeRelMovement << "Guess:" << std::endl;
    std::cout << escapeRelMovement << std::endl;
    std::cout << escapeRelMovement;
    std::cout << "Category " << ( highest_pos != nn->getOutput().size()-1?highest_pos+1:0)
	      << std::endl;
    std::cout << escapeRelMovement << std::endl;
    std::cout << escapeRelMovement;
}

void NNStdOutput::outputInput()
{
    const int cols = 20; //-- Number of columns if input is displayed as a matrix.

    //-- Get input vector:
    std::vector<double> input = nn->getInput();

    //-- Show input:
    //std::cout << "Neural network input:" << std::endl;

    //-- Upper frame:
    for (int i = 0; i < (3 * cols + 2); i++)
	std::cout << '#';

    std::cout << std::endl << '#';

    //-- Input data itself:
    for (int i = 0; i < input.size(); i++)
	{
	    //-- Character selection:
	    if ( input.at(i) > 0 && input.at(i) < 0.33)
		std::cout << " · ";
	    else if (input.at(i) > 0 && input.at(i) < 0.66)
		std::cout << " % ";
	    else if (input.at(i) > 0.66 )
		std::cout << " # ";
	    else if (input.at(i) < 0)
		std::cout << " - ";
	    else
		std::cout << "   ";

	    //-- Line break:
	    if ( i != 0 && (i+1) % cols == 0)
		std::cout << '#' << std::endl << '#';
    }

    //-- Lower frame
    for (int i = 0; i < 3 * cols + 1; i++)
	std::cout << '#';

   // std::cout << std::endl;
}
