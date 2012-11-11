#include "nninput.h"

void NNInput::loadWeights()
{
    nn->setWeights( weights );
}

void NNInput::loadInput()
{
    nn->setInput( input);
}


void NNInput::loadTrainingExamples()
{

}
