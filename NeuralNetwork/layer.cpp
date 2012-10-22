#include "layer.h"


//-- Constructor
Layer::Layer(int n)
{
    //-- Check input
    if (n > 0)
    {
	//-- Set the number of neurons:
	this->n = n;

	//-- Create the neurons:
	for (int i = 0; i < n; i++)
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
}

//-- Set weights to neurons
void Layer::setWeights( Matrix theta )
{
    //-- Note: Each neuron's weights are stored in rows

    //-- Check the dimensions of the matrix:
    if ( theta.getNumRows() == neurons.size() && theta.getNumCols() == neurons[0].getNumDendrites() )
    {
	for(int i = 0; i < this->n; i++)
	    this->neurons[i].setWeight( theta.getRowValues(i));
    }
    else
    {
	std::cerr << "Error [Layer]: incorrect matrix dimensions. Expected a " << neurons.size() << "X"
		  << neurons[0].getNumDendrites() << " matrix." << std::endl;
    }
}


//-- Ouput functions:
//-----------------------------------------------------------------------------------------------

void Layer::refresh()
{
    //-- Update state of neurons
    for (int i = 0; i < neurons.size(); i++)
	neurons[i].refresh();

    //-- Update vector output
    for (int i = 0; i < neurons.size(); i++)
	output[i] = neurons[i].getOutput();
}


std::vector<double> Layer::getOutput()	{   return output; }

int Layer::getN()   {	return n;}


Matrix Layer::getWeights()
{
    //-- Returns a matrix containing the weights of all connections of all neurons in
    //-- the layer. Each row corresponds to the weights of a single neuron.

    //-- Create a matrix to store the weights
    Matrix theta( n, neurons[0].getNumDendrites() );

    for (int i = 0; i < n ; i++)
	theta.setRow( neurons[i].getWeight(), i );

    return theta;


}

//-- Connect with previous layer:
//---------------------------------------------------------------------------------------------------
void Layer::connectLayer(Layer& prevLayer)
{
    //-- Connects this layer's neurons to the neurons of the previous layer
    for(int i = 0; i < n; i++)
	for(int j = 0; j < prevLayer.getN(); j++)
	    this->neurons[i] << prevLayer.neurons[j];
}


void Layer::operator << (Layer& prevLayer)
{
    //-- Same as connectLayer(), but nicer
    connectLayer(prevLayer);
}

