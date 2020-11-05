#include "Agent.h"
#include <vector>

//Class Agent:

//Constructors:

//Virtual functions:

//---------------------------------------------------------------------------------------------------
//Class ContactTracer:

//Constructors:

//Virtual functions:
Agent* ContactTracer:: clone() const{
    return new ContactTracer(*this);
}


//---------------------------------------------------------------------------------------------------
//Class Virus:

//Constructors:

//Virtual functions:
Agent* Virus:: clone() const{
    return new Virus(*this);
}