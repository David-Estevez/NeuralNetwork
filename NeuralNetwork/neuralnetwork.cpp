#include "neuralnetwork.h"


//-- Constructors:

NeuralNetwork::NeuralNetwork(int, int, ...)
{
    //-- I don't know yet how to deal with ... arguments
}

NeuralNetwork::NeuralNetwork( std::vector<int> neuronsInLayer)
{
    //-- Check dimensions:
    if (neuronsInLayer.size() < 2)
    {
	std::cerr<<"Error[Neuralnetwork]: fewer layers than allowed." << std::endl;
    }
    else
    {
	//-- Create first and last layers
	this->inputLayer = new Layer( neuronsInLayer[0]);
	this->outputLayer = new Layer( neuronsInLayer[neuronsInLayer.size()-1]);

	//-- Create hidden layers
	for (int i = 1; i < neuronsInLayer.size()-1; i++)
	{
	    Layer auxLayer( neuronsInLayer[i]);
	    this->hiddenLayer.push_back( auxLayer);
	}

	//-- Connect layers (I'm not sure that this works because of pointers)
	if (hiddenLayer.size() > 0)
	{
	    for (int i = 1; i < hiddenLayer.size(); i++)
		hiddenLayer[i] << hiddenLayer[i-1];

	    hiddenLayer[0] << *inputLayer;
	    *outputLayer << hiddenLayer[hiddenLayer.size()-1];
	}
	else
	{
	    //-- Connect input with output
	    *outputLayer << *inputLayer;
	}

	//-- Create output vector, same dimension as output layer
	for (int i = 0; i < outputLayer->getN(); i++)
	    this->output.push_back( 0);

	//-- Set number of layers
	this->l = neuronsInLayer.size();
    }
}

//-- Destructor

NeuralNetwork::~NeuralNetwork()
{
    delete inputLayer;
    delete outputLayer;
}


//-- Input functions:

void NeuralNetwork::setInput(std::vector<double> input)
{
    //-- Set input vector to input layer

    //-- Check dimensions:
    if ( input.size() == inputLayer->getN())
    {
	//-- Set output to be the input vector:
	inputLayer->setOutput( input );
    }
    else
    {
	std::cerr << "Error [NeuralNetwork]: input vector does not match number of neurons in input layer."
		  << std::endl;
    }
}

void NeuralNetwork::setInput(double *input, int size)
{
    //-- Set an array of double to be input vector of input layer

    std::vector<double> aux;

    for (int i = 0; i < size; i++)
	aux.push_back( *(input + i) );

    setInput(aux);
}

void NeuralNetwork::setWeights(std::vector<Matrix> theta)
{
    //-- Check number of matrices
    if (theta.size() != hiddenLayer.size() + 1) //-- Input layer is not connected to other layer, so it has no weights
	std::cerr << "Error[NeuralNetwork]: number of theta matrices does not match." << std::endl
		  << "Had: " << theta.size() << " Expected: " << hiddenLayer.size() + 1 << std::endl;
    else
    {
	//-- This part has to be made with a paper in front of me, if not is impossible
	//if (theta[0].getNumRows)
    }
}



//-- Output functions:

std::vector<double> NeuralNetwork::getOutput()
{
    return output;
}


std::vector<Matrix> NeuralNetwork::getWeights()
{
    //-- Create the vector to store the matrices:
    std::vector<Matrix> theta;

    //-- Note: input layer does not have a weight matrix assigned, as there is no previous layer.
    //-- Note: in matrices, weights of each neurons are stored in rows.

    //-- Store the hidden layers weight matrices
    for (int i = 0; i < hiddenLayer.size(); i++)
	theta.push_back( hiddenLayer[i].getWeights() );

    //-- Store the output layer weight matrix
    theta.push_back( outputLayer->getWeights() );

    return theta;
}



//-- Other functions

void NeuralNetwork::refresh()
{
    //-- Note: Input layer does not need refresh (there is no previous layer)

    //-- Refresh hidden layers
    for (int i = 0; i < hiddenLayer.size() ; i++)
	hiddenLayer[i].refresh();

    //-- Refresh output layer
    outputLayer->refresh();

    //-- Set network output:
    output = outputLayer->getOutput();
}

