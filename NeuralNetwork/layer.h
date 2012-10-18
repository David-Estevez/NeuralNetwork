#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "neuron.h"

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
    void refresh();
    void setOutput( std::vector<double> output); //-- Just for debugging
    std::vector<double> getOutput();
    int getN() { return n;}

    //-- Connect with previous layer
    void connectLayer( Layer& );    //-- Connects this layer's neurons to the neurons of the previous layer
    void operator << ( Layer& );    //-- Same as connectLayer(), but nicer

    //-- Set weights to neurons
    void setWeights( std::vector<double>); //-- Actually it need a vector of vectors (matrix)

private:
    //-- Atributes
    std::vector<Neuron> neurons;    //-- Stores the neurons in this layer
    std::vector<double> output;	    //-- Activation vector of the layer
    int n;			    //-- Number of neurons in this layer

    //-- Default constructor is private, to hide it:
    Layer();
};

#endif // LAYER_H
