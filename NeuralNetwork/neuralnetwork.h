/*! \file neuralnetwork.h
 *  \brief A Neural Network implementation in C++
 *
 * Generic implementation of a neural network. Once trained, it can recognize patterns
 * and classify data.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 17th, 2012
 *
 */
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <iostream>

#include "layer.h"
#include "matrix.h"

/*! \class NeuralNetwork
 * \brief Generic implementation of a neural network for data classification.
 *
 * Several architectures of neural network can be created with this class.
 *
 * \todo Refresh network automatically when input changes (refresh does not need to
 * be explicitely called from outside).
 */
class NeuralNetwork
{
public:
    //-- Constructors:
    //----------------------------------------------------------------------------------

    /*!
     * \brief Constructor that creates the neural network architecture.
     *
     * Neural network is created from a vector containing l elements, where l is the number
     * of layers composing the network and each element is the number of neurons of each
     * layer (not including the bias unit).
     *
     * For instance, if input vector is {8,4,1}, a network of 3 layers, with an input layer
     * with 8 + 1 neurons, a hidden layer of 4 + 1 neurons and an output layer of 1 neuron
     * (output layer does not need a bias unit) is created.
     *
     * \param neuronsInLayer Vector containing l elements, where l is the number of layers
     * composing the network and each element is the number of neurons of each layer (not
     * including the bias unit).
     */
    NeuralNetwork( std::vector<int> neuronsInLayer);

    //-- Destructor:
    //----------------------------------------------------------------------------------
    //! Default destructor
    ~NeuralNetwork();

    //-- Input functions:
    //----------------------------------------------------------------------------------
    /*!
     * \brief Sets a vector to be the input of the network, and stores it in the input layer.
     *
     *	\param input Vector to set as the input of the network.
     */
    void setInput( std::vector<double> input);

    /*!
     * \brief Sets an array to be the input of the network, and stores it in the input layer.
     *
     * \param input Pointer to the array containing the input data.
     * \param size Size of the input data array.
     */
    void setInput( double * input, int size);

    /*!
     * \brief Sets the weights of the network.
     *
     * The weights are stored in matrices, and there is a matrix for each layer that connects
     * with a previous one (i.e. the input layer has no weights associated).
     *
     * Each neuron weights are stored in rows, and the dimensions of the matrix should be n x m,
     * where n is the number of neurons in the current layer (not including bias unit) and m is
     * the number of neurons in the previous layer (including bias unit).
     *
     * The neural network does not store the values of the weights, only the direction of the
     * memory where those values are stored, so that big matrices are not copied several times
     * in the computer's memory.
     *
     * \param theta Vector containing the directions of the weight matrices.
     */
    void setWeights( std::vector<Matrix *> theta);

    //-- Output functions:
    //----------------------------------------------------------------------------------

    /*! \brief Returns the output of the network.
     *
     * The output of the network is a vector containing the probability, between 0 and 1, that
     * the input data belongs to the category represented by each output neuron.
     *
     * \return Vector containing the probability of input data belonging to each category, with
     * values between 0 and 1.
     */
    std::vector<double> getOutput();

    /*! \brief Get a vector containing several matrices with the values of all weights of
     * all neurons of the network.
     *
     * The weights are stored in matrices, and there is a matrix for each layer that connects
     * with a previous one (i.e. the input layer has no weights associated).
     *
     * Each neuron weights are stored in rows, and the dimensions of the matrix should be n x m,
     * where n is the number of neurons in the current layer (not including bias unit) and m is
     * the number of neurons in the previous layer (including bias unit).
     *
     * \return Vector containing the weight matrices.
     */
    std::vector<Matrix> getWeights();

    /*! \brief Returns the input of the network.
     *
     * \return Current input vector of the network.
     */
    std::vector<double> getInput();

    /*!
     * \brief Updates the output of the network.
     *
     */
    void refresh();

    /*!
     * \brief Return number of layers.
     *
     * \return Number of layers, l.
     */
    int getL()
    {
	return l;
    }

private:
    /*! \var std::vector<double> output
     * \brief Vector containing the output data.
     *
     * The output of the network is a vector containing the probability, between 0 and 1, that
     * the input data belongs to the category represented by each output neuron.
     */
    std::vector<double> output;

    //! Default constructor
    NeuralNetwork();

    //-- Layers:
    //---------------------------------------------------------------------------------

    /*! \var Layer *inputLayer
     *  \brief First layer of the network, whose function is to store the input data.
     */
    Layer *inputLayer;

    /*! \var std::vector<Layer> hiddenLayer
     * \brief Vector containing all the hidden layers.
     */
    std::vector<Layer> hiddenLayer;

    /*! \var Layer *outputLayer
     *  \brief Last layer of the network, calculates and stores the output data.
     */
    Layer *outputLayer;

    /*! \var int l
     * \brief Number of layer in the network.
     */
    int l;

};

#endif // NEURALNETWORK_H
