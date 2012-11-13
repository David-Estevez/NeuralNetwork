#include "nninput.h"

NNInput::~NNInput()
{
    //-- Free variables:

    for (int i = 0; i < (int) weights.size(); i++)
    {
	delete weights.at( weights.size() - i);
    }

}
