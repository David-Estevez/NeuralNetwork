#include "nninput.h"

//-- Constructors:
//------------------------------------------------------------------------------------------

NNInput::NNInput(NeuralNetwork& nn): NeuralNetworkIO(nn)
{
    //-- Initialize input vector pointer:
    input = 0;

    //-- Initialize weights matrix pointers vector:
    for (int i = 0; i < (int) nn.getDimensions().size() - 1; i++ )
	weights.push_back(0);
 }

NNInput::NNInput(NeuralNetwork& nn, NNTrainer& trainingModule) : NeuralNetworkIO(nn)
{
    //-- Initialize input vector pointer:
    input = 0;

    //-- Initialize weights matrix pointers vector:
    for (int i = 0; i < (int) nn.getDimensions().size() - 1; i++ )
	weights.push_back(0);

    this->trainingModule = &trainingModule;
}

//-- Destructor:
//-------------------------------------------------------------------------------------------
NNInput::~NNInput()
{
    //-- If allocated, free variables:

    for (int i = 0; i < (int) weights.size(); i++)
	if ( weights.at( i ) != 0 )
	    delete weights.at(i);

    if (input != 0)
	delete input;

}

//-- Connectivity:
//---------------------------------------------------------------------------
void NNInput::connectToTrainingModule( NNTrainer& trainingModule)
{
    this->trainingModule = &trainingModule;
}

