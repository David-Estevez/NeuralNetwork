#include "nninput.h"

NNInput::~NNInput()
{
    //-- If allocated, free variables:

    for (int i = 0; i < (int) weights.size(); i++)
	if ( weights.at( i ) != 0 )
	    delete weights.at(i);

    if (input != 0)
	delete input;

}
