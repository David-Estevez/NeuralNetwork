#include "neuralnetwork.h"


//-- Constructors:

NeuralNetwork::NeuralNetwork( std::vector<int> neuronsInLayer)
{
    //-- Check dimensions:
    if ( (int) neuronsInLayer.size() < 2)
    {
	std::cerr<<"Error[Neuralnetwork]: fewer layers than allowed." << std::endl;
    }
    else
    {
	//-- Create first and last layers
	this->inputLayer = new Layer( neuronsInLayer.at(0));
	this->outputLayer = new Layer( neuronsInLayer.back() );

	//-- Create hidden layers
	for (int i = 1; i < (int) neuronsInLayer.size()-1; i++)
	{
	    Layer auxLayer( neuronsInLayer.at(i));
	    this->hiddenLayer.push_back( auxLayer);
	}

	//-- Connect layers (I'm not sure that this works because of pointers)
	if (hiddenLayer.size() > 0)
	{
	    for (int i = 1; i < (int) hiddenLayer.size(); i++)
		hiddenLayer[i] << hiddenLayer.at(i-1);

	    hiddenLayer.at(0) << inputLayer;
	    *outputLayer << hiddenLayer.at(hiddenLayer.size()-1);
	}
	else
	{
	    //-- Connect input with output
	    *outputLayer << inputLayer;
	}

	//-- Create output vector, same dimension as output layer
	for (int i = 0; i < outputLayer->getN(); i++)
	    this->output.push_back( 0);

	//-- Set number of layers
	this->l = (int) neuronsInLayer.size();

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
    if ( (int) input.size() == inputLayer->getN() - 1)
    {
	//-- Set output to be the input vector:
	inputLayer->setOutput( input );

	//-- Update network guess
	refresh();
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

    //-- Check dimensions:
    if ( size == inputLayer->getN()-1)
    {
	std::vector<double> aux;

	for (int i = 0; i < size; i++)
	    aux.push_back( *(input + i) );

	setInput(aux);

	//-- Update network guess
	refresh();
    }
    else
    {
	std::cerr << "Error [NeuralNetwork]: input array dimension does not match number of neurons in input layer."
		  << std::endl;
    }
}

void NeuralNetwork::setWeights(std::vector<Matrix *> theta)
{
    //-- Check number of matrices and dimensions
    if (theta.size() != hiddenLayer.size() + 1) //-- Input layer is not connected to other layer, so it has no weights
	std::cerr << "Error[NeuralNetwork]: number of theta matrices does not match." << std::endl
		  << "Had: " << theta.size() << " Expected: " << hiddenLayer.size() + 1 << std::endl;
    else
    {
	for (int i = 0; i < (int) hiddenLayer.size(); i++)
	{
	    hiddenLayer.at(i).setWeights( theta.at(i));
	}

	outputLayer->setWeights( theta.back());

	//-- Save memory direction of matrices
	weights = theta;
    }
}



//-- Output functions:

std::vector<double> NeuralNetwork::getOutput()
{
    return output;
}


std::vector<Matrix *> NeuralNetwork::getWeights()
{
    //-- Note: input layer does not have a weight matrix assigned, as there is no previous layer.
    //-- Note: in matrices, weights of each neurons are stored in rows.

    return weights;
}

std::vector<double> NeuralNetwork::getInput()
{
    return inputLayer->getOutput();
}

//-- Other functions

void NeuralNetwork::refresh()
{
    //-- Note: Input layer does not need refresh (there is no previous layer)

    //-- Refresh hidden layers
    for (int i = 0; i < (int) hiddenLayer.size() ; i++)
        hiddenLayer.at(i).refresh();

    //-- Refresh output layer
    outputLayer->refresh();

    //-- Set network output:
    output = outputLayer->getOutput();
}

