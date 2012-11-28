/*! \file neuralnetworkio.h
 *  \brief Neural network input/output interface
 *
 * Generic input/output interface of a neural network to communicate
 * and exchange data with the outside (std I/O, files, etc).
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 17th, 2012
 *
 */

#ifndef NEURALNETWORKIO_H
#define NEURALNETWORKIO_H

#include "neuralnetwork.h"

/*! \class NeuralNetworkIO
 *  \brief  Generic input/output interface of a neural network to communicate
 * and exchange data with the outside (std I/O, files, etc).
 *
 * All classes that implement I/O interface with the neural network should
 * inherit from this one.
 *
 */
class NeuralNetworkIO
{
protected:
    //-- Constructors
    //----------------------------------------------------------------------
    /*!
     * \brief Default constructor.
     *
     * Just creates a I/O interface, connection with a NeuralNetwork has to
     * be done later.
     */
    NeuralNetworkIO() {}

    /*!
     * \brief Creates a I/O interface and connects it to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    NeuralNetworkIO(NeuralNetwork& nn) { this->nn = &nn;}


    //-- Connection to a neural network:
    //---------------------------------------------------------------------
    /*!
     * \brief Connects a I/O interface to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    void connectToNeuralNetwork(NeuralNetwork& nn) {this->nn = &nn;}

    //-- Atributes:
    //----------------------------------------------------------------------

    /*! \var NeuralNetwork* nn
     * \brief Pointer to a NeuralNetwork to which the I/O interface is
     * connected.
     */
    NeuralNetwork* nn;

};

#endif // NEURALNETWORKIO_H
