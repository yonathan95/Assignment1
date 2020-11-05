#include "Agent.h"
#include <vector>

//Class Agent:

//Constructors:
Agent:: Agent(){}

//---------------------------------------------------------------------------------------------------//
//Class ContactTracer:

//Constructors:
ContactTracer:: ContactTracer():Agent(){}

//Virtual functions:
Agent* ContactTracer:: clone() const{//TODO delete in session
    return new ContactTracer(*this);
}

void ContactTracer:: act(Session& session){//TODO complete

}


//---------------------------------------------------------------------------------------------------//
//Class Virus:

//Constructors:
Virus:: Virus(int nodeInd):Agent(),nodeInd(nodeInd){}

Virus:: Virus(const Virus& other):Agent(),nodeInd(other.nodeInd){}

//Virtual functions:
Agent* Virus:: clone() const{//TODO delete in session
    return new Virus(*this);
}

void Virus:: act(Session& session){//TODO complete

}