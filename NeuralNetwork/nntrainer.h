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

#include "neuralnetwork.h"
#include "neuralnetworkio.h"

/*! \struct Training Example
 * \brief Description
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
    //--------------------------------------------------
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
    double costFunction();

    std::vector<double> gradient();
    bool checkGradient(); //-- Debugs

    void randomWeights();

private:
    TrainingExample* trainingSet;

    double sigmoid(double n);
    double sigmoidGradient(double n);

    double calculateRandomRange( );

};

#endif // NNTRAINER_H
