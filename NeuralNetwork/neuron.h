#ifndef NEURON_H
#define NEURON_H

//-- General libraries:
#include <vector>
#include <math.h>
#include <iostream> //-- Error messages

//-- Random numbers:
#include <cstdlib>
#include <time.h>

static const int RAND_WEIGHT_LIMIT = 10;

//-- Class definition:

class Dendrite;

class Neuron
{
public:
    //-- Constructor
    Neuron();					    //-- Default constructor

    //-- Output functions
    void setOutput(double); //-- Mainly for debug
    virtual double getOutput();		    //-- Returns the current value at the output
    void refresh();				    //-- Calculates the new output of the neuron given the input

    std::vector<double> getWeight();		    //-- Returns a vector containing the weights of the neuron
    double getWeight( int i);			    //-- Returns the value of the weight of the ith dendrite

    int getNumDendrites();			    //-- Returns the number of connections of the neuron

    //-- Connection with other neurons
    void addConnection(Neuron& neuronToBeAdded);    //-- Adds a connection to another neuron in the network
    void operator << (Neuron& neuronToBeAdded);	    //-- Same as addConnection, but shorter to write (and more visual)

    //-- Insert / modify neuron's data
    void setWeight( std::vector<double *> weights);   //-- Changes the vale of all the weights of the neuron
    void setWeight(int i, double newWeight);	    //-- Changes the value of the weight of the ith dendrite
    void setWeight(int i, double * newWeight);	    //-- Changes the value of the weight of the ith dendrite




private:
    double axon;			//-- An axon is the part that sends the output in a real neuron
    std::vector<Dendrite> dendrite;	//-- A dendrite is an input from other neurons to one neuron


    double activation( double n);	//-- Calculates the activation function of the neuron
    double randomWeight (double limit);	//-- Returns a random value to be assigned as a weight
};

struct Dendrite
{
    Neuron* connection;
    double* weight;
};

//-- This is supposed to be a TEMPORAL solution
class BiasUnit : public Neuron {
    public:
	BiasUnit() {}
	virtual double getOutput() { return 1.0; }

};


#endif // NEURON_H
