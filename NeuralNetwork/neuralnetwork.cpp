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

    //-- Create first and last layers
    this->inputLayer = new Layer( neuronsInLayer[0]);
    this->outputLayer = new Layer( neuronsInLayer[neuronsInLayer.size()-1]);

    //-- Create hidden layers
    for (int i = 1; i < neuronsInLayer.size()-1; i++)
    {
	Layer auxLayer( neuronsInLayer[i]);
	this->hiddenLayer.push_back( auxLayer);
    }

    //-- Connect layers (I'm not sure that this works)
    if (hiddenLayer.size() > 0)
    {
	for (int i = 1; i < hiddenLayer.size(); i++)
	    hiddenLayer[i] << hiddenLayer[i-1];

	hiddenLayer[0] << *inputLayer;
	*outputLayer << hiddenLayer[hiddenLayer.size()-1];
    }
    else
    {
	//-- Connect output with input
	*outputLayer << *inputLayer;
    }

    //-- Create output vector, same dimension as output layer
    for (int i = 0; i < outputLayer->getN(); i++)
	this->output.push_back( 0);
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
	//if (theta[0].getRows)
    }
}



//-- Output functions:

std::vector<double> NeuralNetwork::getOutput()
{
    return output;
}


std::vector<Matrix> NeuralNetwork::getWeights()
{
    //-- This should return all the weights structured in a vector of matrices
}



//-- Other functions

void NeuralNetwork::refresh()
{
    //-- This should refresh the output of the network
}

