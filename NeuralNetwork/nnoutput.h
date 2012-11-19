/*! \file nnoutput.h
 *  \brief NeuralNetwork output interface.
 *
 * Generic output interface of a NeuralNetwork to communicate
 * and send data to the outside (STD output, save files, etc).
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 18th, 2012
 *
 */
#ifndef NNOUTPUT_H
#define NNOUTPUT_H

#include "neuralnetwork.h"
#include "neuralnetworkio.h"

/*! \class NNOutput
 * \brief Generic output interface of a NeuralNetwork to communicate
 * and send data to the outside (STD output, save files, etc).
 *
 * All classes that implement an output interface for the NeuralNetwork
 * should inherit from this one.
 *
 */
class NNOutput : public NeuralNetworkIO
{
protected:
    //-- Constructors:
    //-----------------------------------------------------------------
    /*!
     * \brief Default constructor
     */
    NNOutput() {}

    /*!
     * \brief Creates an output interface and connects it to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    NNOutput( NeuralNetwork& nn): NeuralNetworkIO( nn) {}


    //-- Output interface:
    //------------------------------------------------------------------
    /*!
     * \brief Takes the weights from the NeuralNetwork, sends them to some
     * output.
     *
     * This function should take the weight matrices from the NeuralNetwork,
     * and output their value somehow (STD output, file, etc).
     *
     */
    virtual void outputWeights() = 0;

    /*!
     * \brief Takes output vector data from the NeuralNetwork, and sends it to
     * some output.
     *
     * This function should load the output vector from the NeuralNetwork, and
     * output this value somehow (STD output, file, etc).
     *
     */
    virtual void outputGuess() = 0;


    /*!
     * \brief Takes input vector data from the NeuralNetwork and sends it to some
     * output.
     *
     * This function should load the input vector from the NeuralNetwork, and
     * output this value somehow (STD output, file, etc).
     */
    virtual void outputInput() = 0;
};

#endif // NNOUTPUT_H
