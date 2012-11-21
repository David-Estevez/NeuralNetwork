/*! \file layer.h
 *  \brief Defines layers of the neural network, composed by several neurons, and their interactions.
 *
 *
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 17th, 2012
 *
 */

#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <iostream>

#include "neuron.h"
#include "matrix.h"



/*!
 * \class Layer
 * \brief Group of neurons sharing the same level.
 *
 */
class Layer
{
public:
    //-- Constructors
    //---------------------------------------------------------------------------
    /*!
     * \brief Creates a Layer composed by n neurons plus a bias unit (n+1 neurons)
     *
     * \param n Number of neurons in this Layer (Excluding bias unit).
     */
    Layer(int n);


    //-- Input functions:
    //---------------------------------------------------------------------------

    /*!
     * \brief Sets the output vector of the layer.
     *
     * This is used in the input layer, to place the input of the network in a
     * Layer.
     *
     * \param output Vector to set as output of this Layer.
     *
     */
    void setOutput( std::vector<double> output);

    /*!
     * \brief Sets the weights of all neurons in the layer to be the ones stored
     * in Matrix theta.
     *
     * \note Each neuron's vector is stored in a row of the matrix. The bias unit
     * does not have any weights, as no previous neuron connects with it.
     *
     * \param theta Pointer to a Matrix storing the weights of the Layer.
     */
    void setWeights( Matrix * theta);



    //-- Output functions:
    //-----------------------------------------------------------------------------

    /*!
     * \brief Recalulates the output vector.
     *
     * Refreshes each one of the neurons in the layer, except the bias unit.
     */
    void refresh();

    /*!
     * \brief Returns the output vector for this layer.
     *
     * As calculations within the network are carried out by neurons and not by
     * layers, this function as only debug purposes.
     *
     * \return Vector containing the output of the Layer.
     */
    std::vector<double> getOutput();

    /*!
     * \brief Return the number of neurons in this Layer (including bias unit).
     *
     * \return Number of neurons in this Layer (including bias unit).
     */
    int getN();

    /*!
     * \brief Returns the weights of all neurons in the layer.
     *
     * Returns a matrix containing the weights of all connections of all neurons
     * in the layer. Each row corresponds to the weights of a single neuron.
     * Bias unit has no connections, so it has no weights.
     *
     * \return Matrix containing weights of all neurons in layer.
     */
    Matrix getWeights();

    //-- Connecting layers:
    //-----------------------------------------------------------------------------
    /*!
     * \brief Connect this layer's neurons to the neurons of the previous layer.
     *
     * \param prevLayer Layer to which this Layer will be connected.
     */
    void connectLayer(Layer& prevLayer);

    /*!
     * \brief Connect this layer's neurons to the neurons of the previous layer.
     *
     * \param prevLayer Layer to which this Layer will be connected.
     */
    void operator << (Layer& prevLayer);

    /*!
     * \brief Connect this layer's neurons to the neurons of the previous layer.
     *
     * \param prevLayer Pointer to Layer to which this Layer will be connected.
     */
    void connectLayer(Layer* prevLayer);

    /*!
     * \brief Connect this layer's neurons to the neurons of the previous layer.
     *
     * \param prevLayer Pointer to Layer to which this Layer will be connected.
     */
    void operator << (Layer* prevLAyer);


private:
    /*!
     * \var std::vector<Neuron> neurons
     * \brief Stores the neurons in this Layer
     */
    std::vector<Neuron> neurons;

    /*!
     * \var std::vector<double> output
     * \brief Stores output vector of the Layer.
     */
    std::vector<double> output;

    /*!
     * \var int n
     * \brief Number of neurons in this Layer (including bias unit).
     */
    int n;

    /*!
     * \brief Default constructor
     */
    Layer();
};

#endif // LAYER_H
