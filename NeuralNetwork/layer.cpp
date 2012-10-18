#include "layer.h"


//-- Constructor
Layer::Layer(int n)
{
    //-- Set the number of neurons:
    this->n = n;

    //-- Create the neurons:
    for (int i = 0; i < n; i++)
    {
	//-- Create a new neuron
	Neuron newNeuron;

	//-- Add it to layer
	this->neurons.push_back( newNeuron);

	//-- Add an output
	this->output.push_back(0);
    }
}



void Layer::refresh()
{
    //-- Update state of neurons
    for (int i = 0; i < neurons.size(); i++)
	neurons[i].refresh();

    //-- Update vector output
    for (int i = 0; i < neurons.size(); i++)
	output[i] = neurons[i].getOutput();
}


std::vector<double> Layer::getOutput()
{
    //-- Getting output
    return output;
}

void Layer::setOutput(std::vector<double> output)
{
    //-- Debug function
    //-- Allows the user to set the output vector by hand:
    this->output = output;
}

void Layer::connectLayer( Layer& prevLayer)
{
    //-- Connects this layer's neurons to the neurons of the previous layer
    for(int i = 0; i < n; i++)
	for(int j = 0; j < prevLayer.getN(); j++)
	    this->neurons[i] << prevLayer.neurons[j];
}


void Layer::operator << ( Layer& prevLayer)
{
    //-- Same as connectLayer(), but nicer
    connectLayer(prevLayer);
}

//-- Set weights to neurons
void Layer::setWeights( std::vector<double> )
{
    //-- Actually it needs a vector of vectors (matrix)
}
