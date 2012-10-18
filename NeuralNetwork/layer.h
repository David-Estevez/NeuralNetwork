#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "neuron.h"
#include "matrix.h"

class Layer
{
public:
    //-- Constructor
    Layer(int n);

    /*-- Adding neurons (future expansion?)
    void addNeuron( Neuron& neuron);
    void operator << (Neuron& neuron);
    --*/

    //-- Getting output
    void refresh();				 //-- Recalculates the output vector
    void setOutput( std::vector<double> output); //-- Just for debugging
    std::vector<double> getOutput();		 //-- Returns a the output vector
    int getN() { return n;}			 //-- Returns the number of neurons in this layer

    //-- Connect with previous layer
    void connectLayer( Layer& );    //-- Connects this layer's neurons to the neurons of the previous layer
    void operator << ( Layer& );    //-- Same as connectLayer(), but nicer

    //-- Set weights to neurons
    void setWeights( Matrix theta);	    //-- Changes the weights of all neurons by the ones stored in theta
					    //-- Note: each neuron's vector is stored in a row of the matrix

private:
    //-- Atributes
    std::vector<Neuron> neurons;    //-- Stores the neurons in this layer
    std::vector<double> output;	    //-- Activation vector of the layer
    int n;			    //-- Number of neurons in this layer

    //-- Default constructor is private, to hide it:
    Layer();
};

#endif // LAYER_H
