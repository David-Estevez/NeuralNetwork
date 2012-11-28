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
     std::cout <<"Current cost: (with regularization)" <<  costFunction(1) << std::endl;
     std::cout << "Accuracy: " << accuracy() << std::endl;
 }

//-- Cost and gradient calculations
//-------------------------------------------------------------------------

double NNTrainer::costFunction( double lambda)
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

   //-- Regularization
   //------------------------------------------------------------------------
   if (lambda != 0)
   {
       //-- Don't do calculations if lambda is not set
       double regCost = 0;

       for (int i = 1; i <  nn->getL(); i++)					//-- Input layer has no weight matrix associated
	   for (int j = 0; j < nn->getDimensions().at(i); j++)
	       for (int k = 1; k < nn->getDimensions().at(i-1) + 1; k++ )	//-- We don't regularize bias units
		   regCost += pow( nn->getWeights().at(i-1)->get( j, k), 2);


       regCost *= (lambda / (2 * numExamples ) );

       cost+=regCost;
   }

   return cost;
}

std::vector<double> NNTrainer::gradient()
{
    //-- Create n matrices with the dimensions of the weight matrices:
    std::vector<Matrix> Delta;

    for (int i = 0; i < (int) nn->getWeights().size(); i++)
	Delta.push_back( Matrix( nn->getWeights().at(i)->getNumRows(), nn->getWeights().at(i)->getNumCols() ));

    //-- Iterate over all training examples
    for (int i = 0; i < (int) trainingSet->size(); i++)
    {
	//-- First layer

	//-- Intermediate layer

	//-- Last layer
    }

    //-- Divide by m the matrix


}

void NNTrainer::randomWeights()
{
    for (int i = 1; i <  nn->getL(); i++)					//-- Input layer has no weight matrix associated
    {
	  double limit = calculateRandomRange( i );
	  for (int j = 0; j < nn->getDimensions().at(i); j++)
	    for (int k = 0; k < nn->getDimensions().at(i-1) + 1; k++ )
		nn->getWeights().at(i-1)->set( j, k, 2*limit*((rand()/(float)RAND_MAX)-0.5) );
    }

}

double NNTrainer::accuracy()
{
    int guessedOk = 0;
    int numExamples = trainingSet->size();

    for (int i = 0; i < numExamples ; i++)
    {
	//-- Set the input to the network:
	nn->setInput( trainingSet->at(i).x );

	//-- Look for the highest value:
	int highest = 0;
	double highestValue = nn->getOutput().at(0);

	for (int j = 1; j < (int) nn->getOutput().size() ; j++)
	    if ( nn->getOutput().at(j) > highestValue)
	    {
		highest = j;
		highestValue = nn->getOutput().at(j);
	    }

	int j = 0;
	while( true )
	{
	    if (( j == highest && trainingSet->at(i).y.at(j) != 1) || ( j != highest && trainingSet->at(i).y.at(j) != 0))
	    {
		break;
	    }
	    else
	    {
		if ( (j == trainingSet->at(i).y.size() -1  ) && ( ( j == highest && trainingSet->at(i).y.at(j) == 1) || ( j != highest && trainingSet->at(i).y.at(j) == 0)) )
		{
		    guessedOk++;
		    break;
		}
		else
		{
		    if ( j == trainingSet->at(i).y.size() - 1 )
			break;
		}
		j++;
	    }
	}
    }

    return guessedOk / (double) numExamples;
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
    if ( layer > 0 && layer <= nn->getWeights().size() )
    {
	int l_in = nn->getWeights().at(layer-1)->getNumCols();
	int l_out = nn->getWeights().at(layer-1)->getNumRows();

	return sqrt( 6 / (double) (l_in + l_out));
    }
    else
    {
	std::cerr << "Error [NNTrainer]: layer selected is out of range [1 , "
		  << nn->getWeights().size() << ")" << std::endl;
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
