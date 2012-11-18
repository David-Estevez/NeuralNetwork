#include "nnstdoutput.h"

//-- Std Output interface:
//------------------------------------------------------------------------
void NNStdOutput::outputWeights()
{

}

void NNStdOutput::outputOutput()
{
    //-- Set precision to 2, forcing to output float numbers:
    std::cout.precision(2);
    std::cout.setf( std::ios::fixed );

    //-- Display complete statistics while looking for highest:
    std::cout << "Neural Network results: " << std::endl;

    //-- Store the highest at each step:
    double highest = nn->getOutput().at(0);
    int highest_pos = 0;

    for (int i = 0; i < (int) nn->getOutput().size(); i++)
    {
	//-- Display element:
	std::cout << "Category " << i+1 << ": "
		 << nn->getOutput().at(i) * 100 << std::endl;

	//-- Look for highest
	if ( nn->getOutput().at(i) > highest)
	{
	    highest = nn->getOutput().at(i);
	    highest_pos = i;
	}
    }

    // -- Output results:
    std::cout << "Neural Network guess:" << std::endl
	      << "Input data belongs to category ";
    std::cout << highest_pos+1 << ", with " << highest * 100 << "% confidence." << std::endl;

}
