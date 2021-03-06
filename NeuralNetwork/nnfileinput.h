/*! \file nnfileinput.h
 *  \brief File support for NeuralNetwork data input.
 *
 * Loads the data for the input, weights and training examples from
 * different files.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Dec 12th, 2012
 *
 */
#ifndef NNFILEINPUT_H
#define NNFILEINPUT_H

#include <fstream>
#include <vector>
#include <cstdlib>

#include "nninput.h"
#include "neuralnetwork.h"
#include "matrix.h"

/*! \class NNFileInput
 * \brief  File support for data input to NeuralNetwork.
 *
 * Loads the data for the input, weights and training examples from
 * different files.
 *
 */
class NNFileInput : public NNInput
{
public:
    //-- Constructors:
    //---------------------------------------------------------------------------
    /*!
     * \brief Creates a file input interface and connects it to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    NNFileInput(NeuralNetwork& nn);

    /*!
     * \brief Creates a file input interface and connects it to a NeuralNetwork and NNTrainer.
     *
     * \param nn NeuralNetwork to connect to.
     * \param traininModule NNTrainer to connect to.
     */
    NNFileInput(NeuralNetwork& nn, NNTrainer& trainingModule);


    //-- Store the files path:
    //---------------------------------------------------------------------------
    /*!
     * \brief Edits the path containing the nth weight matrix data.
     *
     * \param filePath String containing the path to the file.
     * \param n Index of path to change.
     */
    void setWeightsFile( const std::string filePath, const int n);


    /*!
     * \brief Selects the path containing the input data.
     *
     * The input data can be loaded from a file containing a row vector (all data
     * in a row, separed by spaces), a column vector (each number in a row) or as
     * a Matrix, that will be converted to a vector.
     *
     * \param filePath String containing the path to the file.
     *
     */
    void setInputFile( const std::string filePath);

    /*!
     * \brief Edits the path containing the nth training set data.
     *
     * The position with index 0 is for the inputs of the network, and the
     * position with index 1 is for the expected outputs of the network.
     *
     * \param filePath String containing the path to the file.
     * \param n Index of path to change.
     */
    void setTrainingSetFile( const std::string filePath, const int n);

    //-- Data interface
    //---------------------------------------------------------------------------
    /*!
     * \brief Return all file paths for weights files.
     *
     * \return Vector of strings containing all file paths for weights files.
     */
    std::vector<std::string> getWeightsFile( );

    /*!
     * \brief Return file path for input file.
     *
     * \return String containing file path for input file.
     */
    std::string getInputFile();

    /*!
     * \brief Return all file paths for the training set.
     *
     * \return Vector of strings containing all file paths for the training set.
     */
    std::vector<std::string> getTrainingSetFile();

private:    
    //-- Load data from files:
    //---------------------------------------------------------------------------
    /*!
     * \brief Loads the input data of the NeuralNetwork from a file, and sends it
     * to the network.
     */
    virtual void loadWeights();

    /*!
     * \brief Loads the weights of the NeuralNetwork from a file, and sends them
     * to the network.
     *
     * \todo If dimensions are nonconsistent, it stills tries to load the data.
     */
    virtual void loadTrainingExamples();

    /*!
     * \brief Loads the training examples data for the NeuralNetwork from a file,
     * and sends it to the network.
     */
    virtual void loadInput();


    //-- Variables storing files path:
    //---------------------------------------------------------------------------
    /*! \var std::vector<std::string> weightsFile
     * \brief Vector containing the paths to the files containing the NeuralNetwork
     * weights.
     */
    std::vector<std::string> weightsFile;

    /*! \var std::string inputFile
     * \brief String containing the path to the input file.
     */
    std::string inputFile;

    /*! \var std::vector<std::string> trainingSetFile
     * \brief Vector containing the paths to the training set data.
     */
    std::vector<std::string> trainingSetFile;

    //-- Load a matrix from a file:
    //--------------------------------------------------------------------------
    /*!
     * \brief Loads a new Matrix from a file.
     *
     * \warning Matrices created with this function have to be deallocated later.
     *
     * \param filePath String containing the path to the file.
     */
    Matrix* loadMatrix( const std::string filePath);

    //! Default constructor is private
    NNFileInput();


};

#endif // NNFILEINPUT_H
