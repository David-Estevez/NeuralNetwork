#include "nninput.h"

NNInput::~NNInput()
{
    //-- If allocated, free variables:

    for (int i = 0; i < (int) weights.size(); i++)
	if ( weights.at( weights.size() - i ) != 0 )
	    delete weights.at( weights.size() - i);

    if (intput != 0)
	delete input;

}
