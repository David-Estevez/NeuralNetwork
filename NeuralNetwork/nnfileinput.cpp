#include "nnfileinput.h"

void NNFileInput::loadWeights()
{

}

void NNFileInput::loadInput()
{

}

void NNFileInput::loadTrainingExamples()
{

}

Matrix& NNFileInput::loadMatrix(const char *filePath)
{
    //--Variables to store:
    int rows = 0, cols = 0; //-- Matrix dimensions
    const int BUFFER_SIZE = 32;    //-- Characters to store in number

    char ch;		    //-- Current character read
    char number[BUFFER_SIZE];	    //-- Number stored as characters

    std::vector<double> data; //-- Vector containing data


    //-- Open the file
    std::fstream inputFile(filePath);

    if (inputFile == 0)
	std::cerr << "ERROR";

    //-- Erase the buffer:
    for (int i = 0; i < BUFFER_SIZE; i++)
	number[i] = '\0';

    //-- Extracting data from file:
    while (!inputFile.eof())
    {
	inputFile.get(ch);  	//-- Get a character

	//-- Ignore comments
	if (ch == '#')
	{
	    //-- Ignore data until next line:
	    while( !inputFile.eof() && ch != '\n')
		inputFile.get(ch);

	    continue;
	}

	//-- Check if it is a number:
	if (ch == '-')
	{
	    //-- For Negative numbers:
	    if ( ch >= '0' && ch <= '9' )
	    {
		number[0] = '-';
		number[1] = ch;

		int i = 2;

		//-- Store the number in 'number'
		while( !inputFile.eof() && ch != '\n' && ch != ' ' && i < BUFFER_SIZE)
		{
		    inputFile.get(ch);
		    if ( ( ch >= '0' && ch <= '9' ) || ch == 'e' || ch == '.' || ch == '-')
			number[i] = ch;
		    i++;
		}

		//-- Convert the string to a double and store it in vector 'data'
		data.push_back( atof(number) );

		//-- Erase the buffer:
		for (int i = 0; i < BUFFER_SIZE; i++)
		    number[i] = '\0';
	    }
	}
	else
	{
		//-- For positive numbers:
		if ( ch >= '0' && ch <= '9' )
		{
		    number[0] = ch;

		    int i = 1;

		    //-- Store the number in 'number'
		    while( !inputFile.eof() && ch != '\n' && ch != ' ' && i < BUFFER_SIZE)
		    {
			inputFile.get(ch);
			if ( ( ch >= '0' && ch <= '9' ) || ch == 'e' || ch == '.' || ch == '-')
			    number[i] = ch;
			i++;
		    }

		    //-- Convert the string to a double and store it in vector 'data'
		    data.push_back( atof(number) );

		    //-- Erase the buffer:
		    for (int i = 0; i < BUFFER_SIZE; i++)
			number[i] = '\0';
		 }
	}

	//-- New line detection
	if (ch == '\n' && !inputFile.eof())
	    rows++;
    }

    //-- Close the file:
    inputFile.close();


    //-- Create a new matrix:
    Matrix *dataMatrix = new Matrix(data, rows, cols);

    return *dataMatrix;
}
