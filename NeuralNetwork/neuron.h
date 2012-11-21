/*! \file neuron.h
 *  \brief Defines a neuron and its functions
 *
 *
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 16th, 2012
 *
 */
#ifndef NEURON_H
#define NEURON_H

//-- General libraries:
#include <vector>
#include <math.h>
#include <iostream> //-- For error messages



class Dendrite;

/*!
 * \class Neuron
 * \brief Basic unit of a neural network.
 *
 * The neuron is the basic unit of a neural network. It is composed
 * of some inputs called "dendrites", that connect to other neurons in
 * the network and an output called "axon".
 *
 * The value of the output of the neuron is the sum of the values of
 * the previous neurons multiplied by each weight, and then this sum
 * is passed to an activation function that calculates the output.
 *
 */
class Neuron
{

public:

    //-- Constructors
    //---------------------------------------------------------------------

    //! Default constructor.
    Neuron();



    //-- Output functions
    //---------------------------------------------------------------------

    /*!
    \brief Calculates the new output of the neuron given the input.
     */
    void refresh();

    /*!
     * \brief  Returns the current value at the output.
     *
     * \return Current value at the output.
     */
    virtual double getOutput();

    /*!
     * \brief Returns a vector containing the weights of the neuron.
     *
     * \return Vector containing the weights of the neuron.
     */
    std::vector<double> getWeight();

    /*!
     * \brief Returns the value of the weight of the ith dendrite.
     *
     * \param i Index of the dendrite selected.
     * \return Value of the weight of the ith dendrite.
     */
    double getWeight( int i);

    /*!
     * \brief Returns the number of connections of the neuron.
     *
     * \return Number of connections of the neuron.
     */
    int getNumDendrites();



    //-- Connection with other neurons
    //---------------------------------------------------------------------

    /*!
     * \brief Adds a connection to another neuron in the network.
     *
     * \param neuronToBeAdded Neuron to be connected with this neuron.
     */
    void addConnection(Neuron& neuronToBeAdded);

    /*!
     * \brief Adds a connection to another neuron in the network.
     *
     * \param neuronToBeAdded Neuron to be connected with this neuron.
     */
    void operator << (Neuron& neuronToBeAdded);



    //-- Insert / modify neuron's data
    //---------------------------------------------------------------------

    /*!
     * \brief Manually set the output of the neuron.
     *
     * This is used to build the input layer, as well
     * as to implement the "Bias unit" of the layer,
     * and for debugging purposes.
     *
     * \param value Value that the neuron will output.
     */
    void setOutput(double);

    /*!
     * \brief Changes all the variables storing the weights of the dendrites.
     *
     * \param weights Vector of pointers to the new variables to store the weights
	of the dendrites.
     */
    void setWeight( std::vector<double *> weights);

    /*!
     * \brief Changes the value of the weight of the ith dendrite.
     *
     * \param i Index of the dendrite to modify.
     * \param newWeight New value for the weight of the dendrite.
     */
    void setWeight(int i, double newWeight);

    /*!
     * \brief Changes the variable storing the weight of the ith dendrite.
     *
     * \param i Index of the dendrite to modify.
     * \param newWeight Pointer to the new weight of the dendrite.
     */
    void setWeight(int i, double * newWeight);



private:

    /*!	\var double axon
     * \brief Stores the value of the output of the neuron.
     *
     * "Axon" is name of the part that sends the output in a real neuron.
     */
    double axon;

    /*! \var std::vector<Dendrites> dendrite
     * \brief Stores the data of the neuron connections and their weights.
     *
     * "Dendrite" is the name of the input from other neurons to one neuron
     * in real neurons.
     */
    std::vector<Dendrite> dendrite;

    /*!
     * \brief Calculates the activation function of the neuron.
     *
     * Currently it uses the 'sigmoid function' to calculate the output
     * value of the network, but there are some other function that could
     * be also used.
     *
     * \param n Sum of the product of outputs of previous neurons times
     * their weights.
     */
    double activation( double n);
};



/*! \struct Dendrite
 * \brief Weighted connection between two neurons.
 *
 * "Dendrite" is the scientific name for the connections between real neurons.
 *
 */
struct Dendrite
{
    /*! \var Neuron* connection
     * \brief Pointer to the neuron connected to the neuron containing this Dendrite.
     */
    Neuron* connection;

    /*! \var double* weight
     * \brief Pointer to a variable containing the value of the weight for this Dendrite.
     */
    double* weight;
};

#endif // NEURON_H
