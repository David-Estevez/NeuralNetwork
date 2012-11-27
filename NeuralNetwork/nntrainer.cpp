#include "nntrainer.h"


//-- Constructors & Destructor
//----------------------------------------------------------------
NNTrainer::NNTrainer()
{
    initializeRandomSeed();
}

NNTrainer::NNTrainer(NeuralNetwork &nn) : NeuralNetworkIO( nn )
{
    initializeRandomSeed();
}

//-- Interface with other modules
//-----------------------------------------------------------------

void NNTrainer::getTrainingExamples(std::vector<TrainingExample> &trainingSet)
{
    this->trainingSet = &trainingSet;
}

//-- Training
 void NNTrainer::trainNetwork()
 {
     std::cout <<"Current cost: " <<  costFunction() << std::endl;
 }

//-- Cost and gradient calculations
//-------------------------------------------------------------------------

double NNTrainer::costFunction()
{
   double cost = 0;
   int numExamples = trainingSet->size();
   int numLabels =  trainingSet->at(0).y.size();

   for (int i = 0; i < numExamples ; i++)
   {
       //-- Set the input to the network:
       nn->setInput( trainingSet->at(i).x );

       for (int j = 0; j < numLabels; j++)
	   cost+=  ( -trainingSet->at(i).y.at(j) )*log( nn->getOutput().at(j) ) - (1 - trainingSet->at(i).y.at(j))*log( 1 - nn->getOutput().at(j) );
    }

   cost /= numExamples;

   //-- Add regularization terms:

   return cost;
}

std::vector<double> NNTrainer::gradient()
{
    //-- Calculates the gradient
}

void NNTrainer::randomWeights()
{
    double limit;
    2*limit*((rand()/(float)RAND_MAX)-0.5);
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

//-- Random numbers
void NNTrainer::initializeRandomSeed()
{
	//-- Prepare random numbers:
	//------------------------------------------------------------
	//-- Declare variable to hold seconds on clock.
	time_t seconds;

	//-- Get value from system clock and place in seconds variable.
	time(&seconds);

	//--Convert seconds to a unsigned integer.
	srand((unsigned int) seconds);
}
