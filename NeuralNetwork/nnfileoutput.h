/*! \file fileoutput.h
 *  \brief File support for NeuralNetwork data output.
 *
 * Saves weights, output vector and input data displayed graphically to
 * a file.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 19th, 2012
 *
 */
#ifndef NNFILEOUTPUT_H
#define NNFILEOUTPUT_H

#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>

#include "nnoutput.h"
#include "neuralnetwork.h"
#include "matrix.h"

/*! \class NNFileOutput
 * \brief  File support for data output from NeuralNetwork.
 *
 * Saves weights, output vector and input data displayed graphically to
 * a file.
 *
 */
class NNFileOutput : public NNOutput
{
public:
    //-- Constructors:
    //---------------------------------------------------------------------------
    /*!
     * \brief Default constructor
     */
    NNFileOutput();

    /*!
     * \brief Creates a file output interface and connects it to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    NNFileOutput(NeuralNetwork& nn): NNOutput(nn) {}


    //-- Store the files path:
    //---------------------------------------------------------------------------
    /*!
     * \brief Adds one path to store weight matrix data.
     *
     * \param filePath String containing the path to the file.
     */
    void addWeightsFile( const std::string filePath);

    /*!
     * \brief Selects the path to store the nth weight matrix data.
     *
     * \param filePath String containing the path to the file.
     * \param n Index of path to change.
     */
    void setWeightsFile( const std::string filePath, const int n);

    /*!
     * \brief Generates filenames for the matrix data from given file path.
     *
     * \param filePath String containing the path to the file.
     */
    void setWeightsFile(const std::string filePath);

    /*!
     * \brief Selects the path to store the guess vector of the network.
     *
     * \param filePath String containing the path to the file.
     *
     */
    void setGuessFile( const std::string filePath);


    /*!
     * \brief Selects the path to store the input data.
     *
     * \param filePath String containing the path to the file.
     *
     */
    void setInputFile( const std::string filePath);


    //! \todo Document this and make it nice:
    std::vector<std::string> getWeightsFile() { return weightsFile; }
    std::string getGuessFile( ) { return guessFile; }
    std::string getInputFile( ) { return inputFile; }

    //-- File Output interface:
    //------------------------------------------------------------------
    /*!
     * \brief Takes the weights from the NeuralNetwork, and saves them to a
     * file.
     *
     */
    virtual void outputWeights();

    /*!
     * \brief Takes output vector data from the NeuralNetwork, and saves it to
     * a file.
     *
     */
    virtual void outputGuess();


    /*!
     * \brief Takes input vector data from the NeuralNetwork and saves it to a file.
     *
     * The input data will be stored as a picture composed of characters.
     * Only useful for data visualization.
     */
    virtual void outputInput();

private:
    //-- Variables storing files path:
    //---------------------------------------------------------------------------
    /*! \var std::string weightsFile
     * \brief Vector containing the paths to the files to store the NeuralNetwork
     * weights.
     */
    std::vector<std::string> weightsFile;

    /*! \var std::string guessFile
     * \brief String containing the path to the file that will store the
     * network guess.
     */
   std::string guessFile;

    /*! \var std::string inputFile
     * \brief String containing the path to the input file.
     */
    std::string inputFile;




};

#endif // NNFILEOUTPUT_H
