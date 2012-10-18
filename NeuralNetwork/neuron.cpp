#include "neuron.h"


//--------------------------------------------------------
void Neuron::setOutput(double value)
{
    this->axon = value;
}
//-------------------------------------------------------

Neuron::Neuron()
{
    //-- Prepare random numbers:
    //------------------------------------------------------------
    //-- Declare variable to hold seconds on clock.
    time_t seconds;

    //-- Get value from system clock and place in seconds variable.
    time(&seconds);

    //--Convert seconds to a unsigned integer.
    srand((unsigned int) seconds);
}

//-- Return current activation value:
double Neuron::getOutput()  {	return axon; }


//-- Update the state of the neuron:
void Neuron::refresh()
{
    //-- Container for the result
    double sum = 0;

    //-- Sum up the activation of all the connected neurons times
    //-- their correspondent weight
    for (int i = 0; i < dendrite.size(); i++)
	sum += dendrite[i].weight * dendrite[i].connection->getOutput();


    //-- The value of the output is given by the activation function
    axon = activation(sum);
}


//-- Creates a link (dendrite) between this neuron and another one.
void Neuron::addConnection(Neuron& neuronToBeAdded)
{
    //-- Create a temporal dendrite to store the connection
    Dendrite newConnection;
    newConnection.connection = &neuronToBeAdded; //-- Assign direction of the neuron
    newConnection.weight = randomWeight( RAND_WEIGHT_LIMIT );	 //-- Assign weight to that connection

    //-- Add that dendrite to the dendrite vector of our neuron
    this->dendrite.push_back( newConnection);
}


void Neuron::operator <<(Neuron& neuronToBeAdded)
{
    addConnection(neuronToBeAdded);
}



//-- Returns a vector containing all the weights of the connections
std::vector<double> Neuron::getWeight()
{
    std::vector<double> weights;

    for (int i = 0; i < dendrite.size(); i++)
	weights.push_back(dendrite[i].weight);

    return weights;
}

//-- Returns the current value of the connection # index
double Neuron::getWeight(int index)
{
    if (index < dendrite.size())
	return dendrite[index].weight;
    else
    {
	std::cerr << "Error: index not valid." << std::endl;
	return 0;
    }
}

//-- Changes the weight of all connections at a time
void Neuron::changeWeight( std::vector<double> newWeights)
{
    //-- Check if the same number of weights as connection have been given
    if ( newWeights.size() == dendrite.size() )
    {
	for (int i = 0; i < dendrite.size(); i++)
	    dendrite[i].weight = newWeights[i];
    }
    else
    {
	std::cerr << "Error: vector passed to function "
		     "has no the same dimension as the connections vector." << std::endl;
    }
}



//-- Changes the weight associated with a connection
void Neuron::changeWeight(int index, double newWeight)
{
    if (index < dendrite.size())
	dendrite[index].weight = newWeight;

}


//-- Activation function of the neuron:
double Neuron::activation(double n)
{
    //-- This function is called 'sigmoid function'
    return 1/(1+exp(-n));
}


double Neuron::randomWeight(double limit)
{
    //-- This function generates a random value for a weight
    //-- taking n as a limit bound.

    return 2*limit*((rand()/(float)RAND_MAX)-0.5);
}
