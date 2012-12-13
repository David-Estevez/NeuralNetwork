/*! \file nnstdoutput.h
 *  \brief NeuralNetwork output interface.
 *
 * Generic output interface of a NeuralNetwork to communicate
 * and send data to the outside using std output.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Dec 13th, 2012
 *
 */
#ifndef NNSTDOUTPUT_H
#define NNSTDOUTPUT_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>

#include "nnoutput.h"
#include "neuralnetwork.h"
#include "matrix.h"

/*! \class NNStdOutput
 * \brief  Show NeuralNetwork data using std output.
 *
 * Displays the weights and output vector of a NeuralNetwork using the
 * standard output.
 *
 */
class NNStdOutput : public NNOutput
{
public:
    //-- Constructors:
    //----------------------------------------------------------------------
    /*!
     * \brief Default constructor
     */
    NNStdOutput() { displayColumn = -1; }

    /*!
     * \brief Creates an std output interface and connects it to a NeuralNetwork.
     *
     * \param nn NeuralNetwork to connect to.
     */
    NNStdOutput( NeuralNetwork& nn): NNOutput( nn) { displayColumn = -1;}


    //-- Data interface:
    //------------------------------------------------------------------------
    /*!
     * \brief Sets the position where the guess output will be drawn in terminal.
     *
     * \param col Column of terminal where the output will start.
     * \param row Row of terminal where the output will start.
     */
    void setDisplayCursor( int col, int row );

    //-- Std Output interface:
    //------------------------------------------------------------------------
    /*!
     * \brief Takes the weights from the NeuralNetwork, and displays them on the
     * std output.
     *
     */
    virtual void outputWeights();

    /*!
     * \brief Takes output vector data from the NeuralNetwork, and displays it on
     * the std output.
     *
     */
    virtual void outputGuess();

    /*!
     * \brief Takes input vector data from the NeuralNetwork and displays it on
     * the std output.
     */
    virtual void outputInput();

private:
    /*! \var int displayColumn
     * \brief Stores the starting column of guess output.
     */

    /*! \var int displayRow
      * \brief Stores the starting row of guess output.
      */
    int displayColumn, displayRow;
};

#endif // NNSTDOUTPUT_H
