#ifndef NNFILEINPUT_H
#define NNFILEINPUT_H

#include "nninput.h"
#include "neuralnetwork.h"
#include "matrix.h"

class NNFileInput : public NNInput
{
public:
    NNFileInput() {}
    NNFileInput(NeuralNetwork& nn): NNInput(nn) {}

    virtual void loadWeights();
    virtual void loadTrainingExamples();
    virtual void loadInput();

    //-- Funciones que cargan matrices desde ficheros

    //-- Funciones para guardar la ruta de los ficheros
private:
    //-- Variables que guardan la ruta de los ficheros
};

#endif // NNFILEINPUT_H
