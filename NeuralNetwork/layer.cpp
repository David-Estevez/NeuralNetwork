#include "layer.h"


//-- Constructor
Layer::Layer(int n)
{
    //-- Check input
    if (n > 0)
    {
	//-- Set the number of neurons:
	this->n = n + 1; //-- Bias unit taken into account

	//-- Adding bias unit:
	Neuron biasUnit;
	biasUnit.setOutput( 1.0 ); //-- Bias unit always outputs '1'
	this->neurons.push_back( biasUnit );

	//-- Create the neurons:
	for (int i = 1; i < this->n; i++)
	{
	    //-- Create a new neuron
	    Neuron newNeuron;

	    //-- Add it to the layer
	    this->neurons.push_back( newNeuron);

	    //-- Add an output
	    this->output.push_back(0);
	}
    }
    else
    {
	std::cerr << "Error [Layer]: Layer must have at least one neuron." << std::endl;
    }
}

//-- Input functions:
//--------------------------------------------------------------------------------------------

void Layer::setOutput(std::vector<double> output)
{
    //-- Debug function
    //-- Allows the user to set the output vector by hand:
    this->output = output;

    //-- Neurons output need also to be changed:
    for (int i = 1; i < (int) this->neurons.size() ; i++)
	this->neurons.at(i).setOutput( output.at(i-1) );
}


void Layer::setWeights( Matrix *theta )
{
    //-- Set weights to neurons

    //-- Note: Each neuron's weights are stored in rows
    //-- Bias unit has no weights because it has no connetions to previous layers

    //-- Check the dimensions of the matrix:
    if ( theta->getNumRows() == (int) neurons.size() - 1 && theta->getNumCols() == neurons.at(1).getNumDendrites() )
    {
	for(int i = 1; i < this->n; i++)
	    this->neurons.at(i).setWeight( theta->getRow(i-1) );
    }
    else
    {
	std::cerr << "Error [Layer]: incorrect matrix dimensions. Expected a " << neurons.size() - 1 << "X"
		  << neurons.at(1).getNumDendrites() << " matrix." << std::endl;
    }
}


//-- Ouput functions:
//-----------------------------------------------------------------------------------------------

void Layer::refresh()
{
    //-- Update state of neurons (not bias unit)
    for (int i = 1; i < (int) neurons.size(); i++)
	neurons.at(i).refresh();

    //-- Update vector output
    for (int i = 0; i < (int) neurons.size() - 1; i++)
	output.at(i)= neurons.at(i+1).getOutput();
}


std::vector<double> Layer::getOutput()
{
    return output;
}

int Layer::getN()
{
    return n;
}


Matrix Layer::getWeights()
{
    //-- Returns a matrix containing the weights of all connections of all neurons in
    //-- the layer. Each row corresponds to the weights of a single neuron.
    //-- Bias unit has no connections, so it has no weights

    //-- Create a matrix to store the weights
    Matrix theta( n-1, neurons.at(1).getNumDendrites() );

    for (int i = 1; i < n ; i++)
	theta.setRow( neurons.at(i).getWeight(), i-1 );

    return theta;


}

//-- Connect with previous layer:
//---------------------------------------------------------------------------------------------------
void Layer::connectLayer(Layer& prevLayer)
{
    //-- Connects this layer's neurons to the neurons of the previous layer
    //-- Bias unit cannot be connected to previous layer

    for(int i = 1; i < this->n; i++)
	for(int j = 0; j < prevLayer.getN(); j++)
	    this->neurons.at(i) << prevLayer.neurons.at(j);
}


void Layer::connectLayer(Layer* prevLayer)
{
    //-- Connects this layer's neurons to the neurons of the previous layer
    //-- Bias unit cannot be connected to previous layer

    for(int i = 1; i < this->n; i++)
	for(int j = 0; j < prevLayer->getN(); j++)
	    this->neurons.at(i) << prevLayer->neurons.at(j);
}

void Layer::operator << (Layer& prevLayer)
{
    //-- Same as connectLayer(), but nicer
    connectLayer(prevLayer);
}

void Layer::operator <<( Layer* prevLayer)
{
    connectLayer(prevLayer);
}
