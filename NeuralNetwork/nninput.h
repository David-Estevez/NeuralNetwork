/*! \file nninput.h
 *  \brief NeuralNetwork input interface.
 *
 * Generic input interface of a NeuralNetwork to communicate
 * and get data from the outside (STD input, input files, etc).
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 17th, 2012
 */
#ifndef NNINPUT_H
#define NNINPUT_H

#include <vector>

#include "neuralnetworkio.h"
#include "neuralnetwork.h"
#include "nntrainer.h"
#include "matrix.h"


/*! \class NNInput
 *  \brief  Generic input interface of a NeuralNetwork to communicate
 * and exchange data with the outside (STD input, input files, etc).
 *
 * All classes that implement an input interface with the NeuralNetwork
 * should inherit from this one.
 *
 */
class NNInput: public NeuralNetworkIO
{
protected:
    //-- Constructors:
    //----------------------------------------------------------------
    /*!
     * \brief Creates an input interface and connects it to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    NNInput(NeuralNetwork& nn);

    /*!
     * \brief Creates a input interface and connects it to a NeuralNetwork and NNTrainer.
     *
     * \param nn NeuralNetwork to connect to.
     * \param traininModule NNTrainer to connect to.
     */
    NNInput(NeuralNetwork& nn, NNTrainer& trainingModule);

    //-- Destructor:
    //------------------------------------------------------------------
    /*!
     * \brief Default destructor
     */
    virtual ~NNInput();

    //-- Connectivity:
    //---------------------------------------------------------------------------
    void connectToTrainingModule( NNTrainer& trainingModule);

    //-- Input interface:
    //------------------------------------------------------------------
    /*!
     * \brief Loads the input data of the NeuralNetwork, and sends it to
     * the network.
     *
     * This function should load the input Matrix from some source,
     * store it in the variable input and set this input in the NeuralNetwork.
     *
     */
    virtual void loadInput() = 0;

    /*!
     * \brief Loads the weights of the NeuralNetwork, and sends them to
     * the network.
     *
     * This function should load the weight matrices from some source,
     * store it in the variable weights and send them to the NeuralNetwork.
     *
     */
    virtual void loadWeights() = 0;

    /*!
     * \brief Loads the training examples data for the NeuralNetwork, and
     * sends them to the network.
     *
     * This function should load the training examples from some source,
     * store it in the variable trainingExample and call the training routine
     * of the NeuralNetwork.
     *
     */
    virtual void loadTrainingExamples() = 0;

    //-- Data storage:
    //------------------------------------------------------------------
    /*! \var std::vector<Matrix *> weights
     * \brief Vector containing the weights that will be passed to the
     * NeuralNetwork.
     */
    std::vector<Matrix *> weights;

    /*! \var Matrix *input
     * \brief Input vector that will be passed to the NeuralNetwork, stored
     * as a Matrix.
     */
    Matrix *input;

    /*! \var std::vector<TrainingExample> trainingSet
     * \brief Vector containing the training examples that will be passed to
     * the NeuralNetwork
     */
    std::vector<TrainingExample> trainingSet;

    /*! \var NNTrainer *trainingModule
     * \brief Pointer to the training module to use the training examples:
     */
    NNTrainer *trainingModule;

private:
    //! Default constructor is private
    NNInput();
};

#endif // NNINPUT_H
