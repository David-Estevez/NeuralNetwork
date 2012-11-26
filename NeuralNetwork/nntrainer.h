/*! \file nntrainer.h
 *  \brief Neural network training module
 *
 * Trains the weights of a neural network, and provides a base
 * for developing other trainers with other algorithms.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 25th, 2012
 *
 */

#ifndef NNTRAINER_H
#define NNTRAINER_H

#include <vector>
#include <iostream>
#include <cmath>

#include "neuralnetwork.h"
#include "neuralnetworkio.h"

/*! \struct TrainingExample
 * \brief A given input for the network and the expected output for
 * that input.
 */
struct TrainingExample
{
    //! Input for the network.
    std::vector<double> x;

    //! Expected output of the network with input x.
    std::vector<double> y;
};

/*! \class NNTrainer
 *  \brief Trains the weights of a neural network given a training set.
 *
 * It also provides a costFunction and a gradient that serve as a base for
 * other NNTrainer with different training algorithms.
 *
 */
class NNTrainer : NeuralNetworkIO
{
public:
    //-- Constructors & Destructor
    //--------------------------------------------------
    /*!
     * \brief Default constructor.
     */
    NNTrainer();

    /*!
     * \brief Creates a NNTrainer and connects it to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    NNTrainer( NeuralNetwork& nn): NeuralNetworkIO( nn ) {}

    /*!
     * \brief Default destructor.
     */
    ~NNTrainer();

    //-- Interface with other modules
    //-------------------------------------------------------------------------
    /*!
     * \brief Obtain the training set for training the NeuralNetwork
     */
    void getTrainingExamples( std::vector<TrainingExample>& trainingSet );

    /*!
     * \brief Trains the weigths of the NeuralNetwork
     *
     */
    virtual void trainNetwork() = 0;

protected:
    //-- Cost and gradient calculations
    //-------------------------------------------------------------------------
    /*!
     * \brief Returns the cost of all the examples with the current weight set.
     *
     * \return Cost of all the training examples with current weight set
     */
    double costFunction();

    /*!
     * \brief Returns the gradient of the cost function with the current weight set.
     *
     * \return Gradient of cost function given the current weight set.
     */
    std::vector<double> gradient();

    /*!
     * \brief Calculates the numerical gradient to check the gradient implementation.
     *
     * This function is used for debugging.
     *
     * \warning This way of calculating the gradient is expensive computationally. It
     * should be used only in small test networks for testing the backpropagation
     * implementation, not for optimization of weight set.
     */
    bool checkGradient();

    /*!
     * \brief Generates a new random weight set for training.
     *
     * Generates an appropiate random weights set before training, taking into account
     * the network dimensions.
     */
    void randomWeights();

private:
    /*!
     * \var std::vector<TrainingExample>* trainingSet;
     * \brief Pointer to the training set loaded into memory.
     */
    std::vector<TrainingExample>* trainingSet;

    /*!
     * \var std::vector<double> weightSet
     * \brief Unrolled vector containing all the weights of the neural network.
     */
    std::vector<double> weightSet;


    //-- Internal math calculations:
    //-----------------------------------------------------------------------------------
    /*!
     * \brief Calculates the sigmoid function of a number.
     */
    double sigmoid(double n);

    /*!
     * \brief Calculates the derivative of the sigmoid function at point n.
     */
    double sigmoidGradient(double n);

    /*!
     * \brief Calculates the range of the random weights taking into account the network
     * dimensions.
     *
     * \param layer Index of the current layer. Index starts at 0. Input layer is not a valid
     * layer as it has no weights associated.
     *
     */
    double calculateRandomRange(int layer );

};

#endif // NNTRAINER_H
