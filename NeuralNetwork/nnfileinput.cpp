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
    nn->setInput( input->unroll() );

}

void NNFileInput::loadTrainingExamples()
{
    //-- Check number of input files:
    if ( trainingSetFile.size() != 2 )
    {
	std::cerr << "Error [NNFileInput]: number of training set files different from 2."
		  << std::endl;
    }
    else
    {
	//-- Load both files as matrices:
	Matrix* matrix1 = loadMatrix( trainingSetFile.at(0) );
	Matrix* matrix2 = loadMatrix( trainingSetFile.at(1) );

	//-- Get dimensions of matrices:
	int dimx1 = matrix1->getNumCols();
	int dimy1 = matrix1->getNumRows();
	int dimx2 = matrix2->getNumCols();
	int dimy2 = matrix2->getNumRows();

	//-- Get dimensions of Neural Network:
	int inputSize = nn->getDimensions().at(0);
	int outputSize = nn->getDimensions().back();

	//-- Find orientation of matrices:
	bool inputAsRows, outputAsRows;
	int numExamples = 0;

	if ( dimx1 == inputSize || dimy1 == inputSize)
	{
	    if (dimx1 == inputSize)
		inputAsRows = true;
	    else
		inputAsRows = false;
	}
	else
	{
	    std::cerr << "Error [NNFileInput]: input matrix nonconsistent with neural network input size."
		      << std::endl;
	}

	if (dimx2 == outputSize || dimy2 == outputSize )
	{
	    if (dimx2 == outputSize)
		outputAsRows = true;
	    else
		outputAsRows = false;
	}
	else
	{
	    std::cerr << "Error [NNFileInput]: input matrix nonconsistent with neural network output size."
		      << std::endl;
	}

	//-- Get number of training examples:
	if (  ( inputAsRows &&  outputAsRows && dimy1 == dimy2 ) ||
	      ( inputAsRows && !outputAsRows && dimy1 == dimx2 )    )
	{
	    numExamples = dimy1;
	}
	else if ( ( !inputAsRows &&  outputAsRows && dimx1 == dimy2 ) ||
		  ( !inputAsRows && !outputAsRows && dimx1 == dimx2 ) )
	{
	    numExamples = dimx1;
	}
	else
	{
	    std::cerr << "Error [NNFileInput]: number of examples is not the same in both files."
		      << std::endl;
	}

	//-- Store data:
	for (int i = 0; i < numExamples; i++)
	{
	    //-- Create temporal vectors
	    std::vector<double> inputVector, outputVector;

	    //-- Load input data into vector
	    if (inputAsRows)
		inputVector = matrix1->getRowValues( i );
	    else
		inputVector = matrix1->getColValues( i );

	    //-- Load output data into vector
	    if (outputAsRows)
		outputVector = matrix2->getRowValues( i );
	    else
		outputVector = matrix2->getColValues( i );

	    //-- Create a new training example:
	    TrainingExample ts;
	    ts.x = inputVector;
	    ts.y = outputVector;

	    //-- Append it to the training set
	    trainingSet.push_back( ts );
	}

	//-- Deallocate memory
	delete matrix1;
	delete matrix2;

	//-- Set training set of training module:
	trainingModule->getTrainingExamples( trainingSet );
    }
}

Matrix* NNFileInput::loadMatrix(const std::string filePath)
{
    //--Variables to store:
    int rows = 0, cols = 0;	   //-- Matrix dimensions
    const int BUFFER_SIZE = 32;    //-- Characters to store in number

    char ch;			    //-- Current character read
    char number[BUFFER_SIZE];	    //-- Number stored as characters

    std::vector<double> data;	    //-- Vector containing data


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
        //-- Read next character:
        inputFile.get(ch);

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

	//-- New line detection / number of columns
	if (ch == '\n' && !inputFile.eof())
	{
	    //-- For first row
	    if ( rows == 0)
		cols = data.size(); //-- Obtain the number of columns

	    rows++;
	}
    }

    //-- Close the file:
    inputFile.close();


    //-- Create a new matrix:
    Matrix *dataMatrix = new Matrix(data, rows, cols);

    return dataMatrix;
    }
    else
    {
	std::cerr <<"[NNFileInput]Error: File \"" << filePath << "\"" << std::endl
		  <<"[NNFileInput]Error: File could not be opened!" << std::endl;

        return 0;
    }
}

//-- Functions for storing the file path
//-----------------------------------------------------------------------------------------

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

//-- Data interface
//------------------------------------------------------------------------------------------
std::vector<std::string> NNFileInput::getWeightsFile( )
{
    return weightsFile;
}

std::string NNFileInput::getInputFile()
{
    return inputFile;
}


std::vector<std::string> NNFileInput::getTrainingSetFile()
{
    return trainingSetFile;
}
