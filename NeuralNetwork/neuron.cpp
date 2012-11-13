#include "neuron.h"


//--------------------------------------------------------
void Neuron::setOutput(double value)
{
    this->axon = value;
}
//-------------------------------------------------------

Neuron::Neuron()
{
    /*** NOT NEEDED ANYmORE ***
    //-- Prepare random numbers:
    //------------------------------------------------------------
    //-- Declare variable to hold seconds on clock.
    time_t seconds;

    //-- Get value from system clock and place in seconds variable.
    time(&seconds);

    //--Convert seconds to a unsigned integer.
    srand((unsigned int) seconds); */
}

//-- Return current activation value:
double Neuron::getOutput()  {	return axon; }


//-- Update the state of the neuron:
void Neuron::refresh()
{
    //-- Container for the result
    double sum = 0;

    //-- Sum up the activation of all the connected neurons times
    //-- their correspondent weight:
    for (int i = 0; i < (int) dendrite.size(); i++)
	sum += *(this->dendrite.at(i).weight) * dendrite.at(i).connection->getOutput();

    //-- The value of the output is given by the activation function
    axon = activation(sum);
}


//-- Creates a link (dendrite) between this neuron and another one.
void Neuron::addConnection(Neuron& neuronToBeAdded)
{
    //-- Create a temporal dendrite to store the connection:
    Dendrite newConnection;
    newConnection.connection = &neuronToBeAdded;		 //-- Assign direction of the neuron
    newConnection.weight = 0;					 //-- While no weight matrix has been asigned,
								 //-- value for connection is undefined (pointer to NULL)

    //-- Add that dendrite to the dendrite vector of our neuron:
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

    for (int i = 0; i < (int) dendrite.size(); i++)
	weights.push_back( *(dendrite[i].weight) );

    return weights;
}

//-- Returns the current value of the connection # index
double Neuron::getWeight(int index)
{
    if (index >= 0 && index < (int) dendrite.size())
	return *(dendrite[index].weight);
    else
    {
	std::cerr << "Error [Neuron]: index not valid." << std::endl;
	return 0;
    }
}

//-- Returns the number of connections of the neuron
int Neuron::getNumDendrites()
{
    return dendrite.size();
}

//-- Changes the weight of all connections at a time
void Neuron::setWeight( std::vector<double *> newWeights)
{
    //-- Check if the same number of weights as connections have been given
    if ( newWeights.size() == dendrite.size() )
    {
    for (int i = 0; i < (int) dendrite.size(); i++)
	    this->dendrite.at(i).weight = newWeights.at(i);
    }
    else
    {
	std::cerr << "Error [Neuron]: vector passed to function "
		     "has not the same dimension as the connections vector." << std::endl;
    }
}



//-- Changes the weight associated with a connection
void Neuron::setWeight(int index, double newWeight)
{
    if (index >= 0 && index < (int) dendrite.size())
	*(dendrite[index].weight) = newWeight;
    else
	std::cerr << "Error [Neuron]: neuron with index "
		  << index << "does not exist" << std::endl;

}

//-- Changes the weight associated with a connection
void Neuron::setWeight(int index, double * newWeight)
{
    if (index >= 0 && index < (int) dendrite.size())
	dendrite[index].weight = newWeight;
    else
	std::cerr << "Error [Neuron]: neuron with index "
		  << index << "does not exist" << std::endl;

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
