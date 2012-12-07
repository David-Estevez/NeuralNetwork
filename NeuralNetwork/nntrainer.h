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

//-- Random numbers:
#include <cstdlib>
#include <ctime>

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
    NNTrainer( NeuralNetwork& nn);

    /*!
     * \brief Default destructor.
     *
     * \todo Implement or remove.
     */
    ~NNTrainer() {}

    //-- Interface with other modules
    //-------------------------------------------------------------------------
    /*!
     * \brief Obtain the training set for training the NeuralNetwork.
     */
    void getTrainingExamples( std::vector<TrainingExample>& trainingSet );

    /*!
     * \brief Trains the weigths of the NeuralNetwork.
     *
     * \todo Document this
     */
    void trainNetwork();

    /*!
     * \brief Shows the ability of the current weights to fit a given training set.
     *
     * \return A value between 0 and 1.
     */
    double accuracy();

    //-- Cost and gradient calculations
    //-------------------------------------------------------------------------
    /*!
     * \brief Returns the cost of all the examples with the current weight set.
     *
     * \param lambda Regularization coefficient to avoid overfitting.
     * \return Cost of all the training examples with current weight set
     */
    double costFunction( const double lambda = 0);

    /*!
     * \brief Returns the cost of all the examples with the current weight set.
     *
     * \param theta Vector containing all the unrolled weights.
     * \param lambda Regularization coefficient to avoid overfitting.
     * \return Cost of all the training examples with current weight set
     */
    double costFunction( const std::vector<double> theta,  const double lambda = 0 );

    /*!
     * \brief Returns the gradient of the cost function with the current weight set.
     *
     *
     * \param theta Vector containing all the unrolled weights.
     * \param lambda Regularization coefficient to avoid overfitting.
     * \return Gradient of cost function given the current weight set.
     */
    std::vector<double> gradient( const double lambda = 0);

    /*!
     * \brief Returns the gradient of the cost function with the current weight set.
     *
     *
     * \param theta Vector containing all the unrolled weights.
     * \param lambda Regularization coefficient to avoid overfitting.
     * \return Gradient of cost function given the current weight set.
     */
    std::vector<double> gradient( const std::vector<double> theta,  const double lambda = 0);

protected:
    /*!
     * \brief Calculates the numerical gradient to check the gradient implementation.
     *
     * This function is used for debugging.
     *
     * \param lambda Regularization coefficient to avoid overfitting.
     * \param epsilon Increment to use when calculating the gradient.
     *
     * \warning This way of calculating the gradient is expensive computationally. It
     * should be used only in small test networks for testing the backpropagation
     * implementation, not for optimization of weight set.
     */
   std::vector<double> numericalGradient(const double lambda = 0, const double epsilon = 1e-4);

   /*!
    * \brief Checks the computation of gradients with backprop in a small neural network.
    *
    * \param lambda Regularization coefficient to avoid overfitting.
    *
    * This funciont is used for debugging.
    */
   bool checkGradient(const double lambda = 0);

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
     *
     * \todo Erase it if not used
     */
    std::vector<double> weightSet;


    //-- Convert unrolled weights to matrices vector:
    //----------------------------------------------------------------------------------
    /*!
     * \brief Converts unrolled weights into a suitable matrix vector to set in the network.
     *
     * \warning This function reserves memory for the matrices that has to be deallocated
     * manually later.
     *
     * \param theta Unrolled vector of weights.
     * \return Matrix vector containing weights.
     */
    std::vector<Matrix *> unrolledToMatrices( std::vector< double> theta);

    //-- Internal math calculations:
    //-----------------------------------------------------------------------------------
    /*!
     * \brief Calculates the derivative of the sigmoid function at point n.
     *
     * \note This is not the actual derivative, only works if the input is the output
     * of the sigmoid function, i.e. the input is output of the activation function.
     */
    double sigmoidGradient(double n);


    //-- Random number generation:
    //-------------------------------------------------------------------------------------
    /*!
     * \brief Calculates the range of the random weights taking into account the network
     * dimensions.
     *
     * \param layer Index of the current layer. Index starts at 0. Input layer is not a valid
     * layer as it has no weights associated.
     *
     */
    double calculateRandomRange(int layer );

    /*!
      * \brief Uses the current time to initialize a seed for random numbers.
      */
    void initializeRandomSeed();

};

#endif // NNTRAINER_H
