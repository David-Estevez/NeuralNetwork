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
//------------------------------------------------------------------
void NNTrainer::trainNetwork()
{
    //-- Training parameters:
    static const double alpha = 1;
    static const int iter = 1000;
    static const double lambda = 0;

    std::cout << std::endl << "Training network:" << std::endl;

    //-- Randomize weights
    std::cout << "Randomize weights...";
    randomWeights();
    std::cout << "[ok]" << std::endl << "Starting Gradient Descend: " << std::endl;

    //-- Start gradient descend:
    for (int i = 0; i < iter; i++)
    {

	//-- Calculate gradient:
	std::vector<double> grad = gradient( lambda );

	//-- Convert the gradient in matrices:
	std::vector<Matrix *> matGrad = unrolledToMatrices( grad );
	Matrix aux = ( *matGrad.at(0) * 2);
	//std::cout << "Increment: " << aux.get(0,0) << std::endl;

	//-- Operate matrices
	for (int l = 0; l < (int) nn->getWeights().size(); l++)
	{
	    //-- Debug
	   // std::cout << "Layer(" << l << "), value before: " << nn->getWeights().at(l)->get( 0,0) << std::ends;
	    *nn->getWeights().at(l) = ( *nn->getWeights().at(l) ) - *matGrad.at(l)  ;
	   // std::cout << " value after: " << nn->getWeights().at(l)->get( 0,0) << std::ends;
	   // std::cout << " increment: " << (*matGrad.at(l) * alpha).get(0,0) << std::endl;
	}

	//-- Deallocate memory:
	for (int l = (int) matGrad.size() - 1; l >= 0; l--)
	    delete matGrad.at(l);

	//-- Periodically, show percentage completed and accuracy:
	if ( (double) (i % 10) == 0)
	{
	    std::cout << "Completed: " <<  ( i / (double) iter ) * 100 << "% Current accuracy: "
		      << accuracy() * 100 << "%" << " Current cost: " << costFunction(lambda)  << std::endl;
	}
    }
}

//-- Cost and gradient calculations
//-------------------------------------------------------------------------

double NNTrainer::costFunction(const double lambda)
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

double NNTrainer::costFunction(  const std::vector<double> theta,  const double lambda)
{
    std::vector<Matrix *> prevWeights = nn->getWeights();
    std::vector<Matrix *> newWeights = unrolledToMatrices( theta );
    double cost = 0;

    if ( !newWeights.empty() )
    {
	//-- Assign new weights to neural network:
	nn->setWeights( newWeights);


	//-- Actually calculate the cost:
	cost = costFunction( lambda );

    }

   //-- Restore old weights:
   nn->setWeights( prevWeights);

   //-- Deallocate memory:
   for (int i =  nn->getL() - 1; i >= 0; i--)
   {
       delete newWeights.at(i);
   }

   return cost;
}

std::vector<double> NNTrainer::gradient( const double lambda)
{
    int numExamples = trainingSet->size();
    //-- Create n matrices with the dimensions of the weight matrices:
    std::vector<Matrix> Delta;

    for (int i = 0; i < (int) nn->getWeights().size(); i++)
	Delta.push_back( Matrix( nn->getWeights().at(i)->getNumRows(), nn->getWeights().at(i)->getNumCols() ));

    //-- Iterate over all training examples
    for (int i = 0; i < numExamples; i++)
    {
	//-- Forward-propagate the network:
	nn->setInput( trainingSet->at(i).x );

	//-- Create vector to store the increments:
	//-- Increments will be stored in reverse order (i.e. the last increment first)
	std::vector<Matrix> inc;

	//-- Increment for output layer
	Matrix output = Matrix(nn->getOutput(), nn->getOutput().size(), 1);
	Matrix y = Matrix(trainingSet->at(i).y , trainingSet->at(i).y.size(), 1);

	inc.push_back( output - y);

	//-- Increment for hidden layers
	for (int l = nn->getL() - 2; l > 0; l--)
	{

	    Matrix aux1 = nn->getWeights().at(l)->transpose() * inc.back();
	    Matrix aux2( aux1.getNumRows()-1, aux1.getNumCols());

	    for (int j = 0; j < aux2.getNumCols(); j++)
		for (int k = 0; k < aux2.getNumRows(); k++)
		    aux2.set( k, j, aux1.get(k+1, j) * sigmoidGradient( nn->getActivation(l).at(k)) );

	    inc.push_back( aux2 );
	}

	//-- Input layer has no error associated (has no weights associated)

	//-- Accumulate error:
	for (int l = 0; l < (int) Delta.size(); l++)
	{
	    Matrix aux1( Delta.at(l).getNumRows(), Delta.at(l).getNumCols() );

	    for (int j = 0; j < aux1.getNumRows(); j++)
		aux1.set( j, 0, inc.at( inc.size()- l -1).get( j, 0) );

	    for (int j = 0; j < aux1.getNumRows(); j++)
		for (int k = 1; k < aux1.getNumCols(); k++)
		    aux1.set( j, k, inc.at( inc.size()- l -1).get( j, 0) * nn->getActivation(l).at(k-1));

	    Delta.at(l) += aux1;
	}


    }

    //-- Divide by number of training examples:
    for (int l = 0; l < (int) Delta.size(); l++)
	Delta.at(l) /= numExamples;

    //-- Regularization
    //------------------------------------------------------------------------
    if (lambda != 0)
    {
	for (int l = 0; l < (int) Delta.size(); l++)
	{
	    Matrix aux(nn->getWeights().at(l)->getNumRows(), nn->getWeights().at(l)->getNumCols() );

	    for (int j = 0; j < aux.getNumRows(); j++)
		for (int k = 1; k < aux.getNumCols(); k++)
		    aux.set( j, k, nn->getWeights().at(l)->get(j, k) * lambda / numExamples);

	    Delta.at(l) += aux;
	}
    }


    //-- Unroll gradient:
    //---------------------------------------------------------------------------
    std::vector<double> unrolled = Delta.front().unroll();

    for (int l = 1; l < (int) Delta.size(); l++)
	for (int j = 0; j < Delta.at(l).getNumRows(); j++)
	    for (int k = 0; k < Delta.at(l).getNumCols(); k++)
		unrolled.push_back( Delta.at(l).get(j, k));


    return unrolled;
}

std::vector<double> NNTrainer::gradient( const std::vector<double> theta, const double lambda)
{
    std::vector<Matrix *> prevWeights = nn->getWeights();
    std::vector<Matrix *> newWeights = unrolledToMatrices( theta );
    std::vector<double> unrolled ;

    if ( !newWeights.empty() )
    {
	//-- Assign new weights to neural network:
	nn->setWeights( newWeights);

	unrolled = gradient(lambda);

    }

    //-- Restore old weights:
    nn->setWeights( prevWeights);

    //-- Deallocate memory:
    for (int i =  nn->getL() - 1; i >= 0; i--)
    {
	delete newWeights.at(i);
    }



    return unrolled;

}

std::vector<double> NNTrainer::numericalGradient(const double lambda, const double epsilon)
{
    //-- Gradient vector
    std::vector<double> gradient;

    //-- Calculate gradient numerically:
    for (int i = 0; i < (int) nn->getWeights().size(); i++)
	for (int j = 0; j < nn->getWeights().at(i)->getNumRows(); j++  )
	    for (int k = 0; k < nn->getWeights().at(i)->getNumCols(); k++  )
	    {
		//-- Copy weights matrices:
		std::vector<Matrix *> thetaPlus, thetaMinus;

		for (int ind = 0; ind < (int) nn->getWeights().size(); ind++)
		{
		    Matrix * aux1 = new Matrix( nn->getWeights().at(ind)->getNumRows(), nn->getWeights().at(ind)->getNumCols() );
		    Matrix * aux2 = new Matrix( nn->getWeights().at(ind)->getNumRows(), nn->getWeights().at(ind)->getNumCols() );

		    *aux1 = *nn->getWeights().at(ind);
		    *aux2 = *nn->getWeights().at(ind);

		    thetaPlus.push_back(  aux1 );
		    thetaMinus.push_back( aux2 );
		}

		//-- Add/substract epsilon
		thetaPlus.at(i)->set( j, k, thetaPlus.at(i)->get( j, k) + epsilon );
		thetaPlus.at(i)->set( j, k, thetaPlus.at(i)->get( j, k) + epsilon );

		//-- Store previous weights:
		std::vector<Matrix *> prevWeights = nn->getWeights();

		//-- Calulate costs of thetaPlus:
		nn->setWeights( thetaPlus );
		double costPlus = costFunction( lambda );

		nn->setWeights( thetaMinus );
		double costMinus = costFunction( lambda );

		//-- Restore original weights:
		nn->setWeights( prevWeights );

		//-- Calculate element:
		gradient.push_back( (  costPlus - costMinus )/ ( 2* epsilon) );

		//-- Delete vectors:
		for (int ind = nn->getWeights().size()-1; ind >= 0; ind--)
		{
		    delete thetaPlus.at(ind);
		    delete thetaMinus.at(ind);
		}

	    }
    return gradient;
}

bool NNTrainer::checkGradient( const double lambda)
{
    //-- Routine to check the gradient
    //------------------------------------------------------------------------------------
    //-- Store the previous configuration:
    NeuralNetwork* prevNN = nn;
    std::vector<Matrix *> prevWeights = nn->getWeights();
    std::vector<TrainingExample> *prevTraining = trainingSet;

    //-- New configuration:

    //--New neural network:
    int array[] = {3, 5, 3};
    std::vector<int> newDim(array, array+sizeof(array)/sizeof(int));

    NeuralNetwork newNN( newDim );

    //-- New weight matrices:
    Matrix mat1( 5, 4), mat2( 3, 6);
    std::vector< Matrix *> newWeights;
    newWeights.push_back( &mat1);
    newWeights.push_back( &mat2);

    //-- Set new configuration:
    newNN.setWeights( newWeights);
    nn = &newNN;


    //-- New training set (random, of course)
    std::vector<TrainingExample> newTS;

    for (int i = 0; i < 5; i++)
    {
	//-- Construct input
	std::vector<double> x;

	for(int j = 0; j < 3; j++)
	{
	    x.push_back( 2* 0.14 *((rand()/(float)RAND_MAX)-0.5) );
	}

	//-- Construct expected output:
	std::vector<double> y;
	for(int j = 0; j < 3; j++)
	{
	    if ( j == i )
		y.push_back(1);
	    else if ( i > j && i-3 == j)
		y.push_back(1);
	    else
		y.push_back(0);
	}

	//-- Construct training example:
	TrainingExample aux;
	aux.x = x;
	aux.y = y;

	//-- Append example:
	newTS.push_back( aux);
    }
    //-- Set new training set
    trainingSet = &newTS;

    //-- Randomize weights:
    randomWeights();

       //-- Calculate gradients:
    std::vector<double> backprop = gradient( lambda );
    std::vector<double> numerical = numericalGradient( lambda );

    std::cout << "Backprop gradient:" << std::endl;
    std::cout << backprop << std::endl;
    std::cout << "Numerical gradient:" << std::endl;
    std::cout << numerical << std::endl;

    //-- Calculate relative deviation:
    std::vector<double> sum, difference;

    for (int i= 0; i < (int) backprop.size(); i++)
    {
	sum.push_back( pow( ( numerical.at(i)) + backprop.at(i)  , 2)  );
	difference.push_back( pow( ( numerical.at(i) - backprop.at(i)) , 2) );
    }

    double modSum = 0, modDif = 0;
    for (int i= 0; i < (int) backprop.size(); i++)
    {
	modSum+=sum.at(i);
	modDif+=difference.at(i);
    }

    std::cout << "Relative difference is: " << sqrt(modDif) / sqrt(modSum) << std::endl;

    //--Restore the previous configuration:
    nn = prevNN;
    nn->setWeights( prevWeights );
    trainingSet = prevTraining;

    //-- Return if passed the test or not:
    if ( sqrt(modDif) / sqrt(modSum) < 1e-4 )
	return true;
    else
	return false;
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



//-- Convert unrolled weights to matrices vector:
//----------------------------------------------------------------------------------
std::vector<Matrix *> NNTrainer::unrolledToMatrices( std::vector< double> theta)
{

   std::vector<Matrix *> newWeights;

   int numWeights = 0;

   //-- Calculate number of weights:
   for (int i = 1; i < nn->getL(); i++)
       numWeights += (nn->getDimensions().at(i-1) + 1) * nn->getDimensions().at(i);

   if ( !theta.empty() && theta.size() == numWeights )
   {
       //-- Create weight matrices
       int lastPos = 0;

       for (int i = 1; i < nn->getL(); i++)
       {
	   int nextPos = lastPos + (nn->getDimensions().at(i-1) + 1) * nn->getDimensions().at(i);
	   Matrix * mat = new Matrix( std::vector<double>( theta.begin()+lastPos, theta.begin()+ nextPos ), nn->getDimensions().at(i) , nn->getDimensions().at(i-1) + 1 );
	   lastPos = nextPos;
	   newWeights.push_back( mat );
       }
    }

    return newWeights;
}


//-- Internal math calculations:
//-----------------------------------------------------------------------------------
double NNTrainer::sigmoidGradient(double n)
{
    return n * (1 - n);
}


double NNTrainer::calculateRandomRange(int layer)
{
    if ( layer > 0 && layer <= (int) nn->getWeights().size() )
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

    return 0;
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
