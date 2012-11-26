#include "nntrainer.h"

//-- Constructors & Destructor
//----------------------------------------------------------------
NNTrainer::NNTrainer()
{
}


//-- Interface with other modules
//-----------------------------------------------------------------

void NNTrainer::getTrainingExamples(std::vector<TrainingExample> &trainingSet)
{
    this->trainingSet = &trainingSet;
}


//-- Cost and gradient calculations
//-------------------------------------------------------------------------

double NNTrainer::costFunction()
{
    //-- Calculates the cost
}

std::vector<double> NNTrainer::gradient()
{
    //-- Calculates the gradient
}


//-- Internal math calculations:
//-----------------------------------------------------------------------------------
double NNTrainer::sigmoid(double n)
{
    return 1/( 1 + exp(-n));
}

double NNTrainer::sigmoidGradient(double n)
{
    return sigmoid(n) * (1-sigmoid(n));
}

double NNTrainer::calculateRandomRange(int layer)
{
    if ( layer > 0 )
    {
	int l_in = nn->getWeights().at(layer-1)->getNumCols();
	int l_out = nn->getWeights().at(layer-1)->getNumRows();

	return sqrt( 6 / (l_in + l_out));
    }
    else
    {
	//-- Error
    }
}
