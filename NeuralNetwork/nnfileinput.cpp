#include "nnfileinput.h"

void NNFileInput::loadWeights()
{
    //-- Load weight matrices:
    for (int i = 0; i < (int) weightsFile.size(); i++)
	weights.push_back( loadMatrix( weightsFile.at(i) ));

    //-- Pass the matrices to the NeuralNetwork:
    nn->setWeights( weights );
}

void NNFileInput::loadInput()
{   
    //-- Load input vector
    input = loadMatrix( inputFile ) ;

    //-- Extract the vector from input and pass it to the NeuralNetwork:
    nn->setInput( input->getColValues(0) );

}

void NNFileInput::loadTrainingExamples()
{
    //-- Does not do anything right now
}

Matrix* NNFileInput::loadMatrix(const std::string filePath)
{
    //--Variables to store:
    int rows = 0, cols = 0; //-- Matrix dimensions
    const int BUFFER_SIZE = 32;    //-- Characters to store in number

    char ch;		    //-- Current character read
    char number[BUFFER_SIZE];	    //-- Number stored as characters

    std::vector<double> data; //-- Vector containing data


    //-- Open the file
    std::ifstream inputFile( filePath.c_str() );

    if (inputFile.is_open())
    {
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

    return dataMatrix;
    }
    else
    {
        std::cerr << "ERROR" << std::endl;

        return 0;
    }
}

void loadVector(const std::string filePath , std::vector<double>& vector)
{
    //-- Stores (toDo)
    //-- Open file:
    std::ifstream file( filePath.c_str() );

    double buffer;
    vector.clear();

    if (file.is_open())
    {
	while( file.good() )
	{
	    file >> buffer;
	    vector.push_back( buffer );
	}
    file.close();
    }
    else
    {
	std::cerr << "[NNFileInput]Error: File could not be opened!" << std::endl;
    }

}

//-- Functions for storing the file path
void NNFileInput::addWeightsFile(const std::string filePath)
{
    weightsFile.push_back(filePath);
}

void NNFileInput::setWeightsFile(const std::string filePath, const int n)
{
    weightsFile.at( n) = filePath;
}

void NNFileInput::setInputFile(const std::string filePath)
{
    inputFile = filePath;
}

void NNFileInput::addTrainingSetFile(const std::string filePath)
{
    trainingSetFile.push_back( filePath);
}

void NNFileInput::setTrainingSetFile(const std::string filePath, const int n)
{
    trainingSetFile.at(n) = filePath;
}
