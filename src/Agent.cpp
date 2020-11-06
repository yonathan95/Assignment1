#include "Agent.h"
#include <vector>
#include "Session.h"

//Class Agent:

//Constructors:
Agent:: Agent(){}

//---------------------------------------------------------------------------------------------------//
//Class ContactTracer:

//Constructors:
ContactTracer:: ContactTracer():Agent(){}

//Virtual functions:
Agent* ContactTracer:: clone() const{
    // will be deleted in session destructor.
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
Agent* Virus:: clone() const{
    // will be deleted in session destructor.
    return new Virus(*this);
}

void Virus:: act(Session& session){//TODO complete
    //push it-self to the infectedQueue
    session.enqueueInfected(nodeInd);
    Graph temGraph = session.getGraph();
    bool found = false;
    //looking for the first virus-free neighbour to infect.
    for(int j = 0 ; j < temGraph.getEdges().size() & !(found); ++j){
        if(temGraph.getEdges()[nodeInd][j] == 1){ // find the neighbor of the node number nodeInd.
            if(!(temGraph.isInfected(j))){ // find the first virus free neighbor to infect.
                session.setInfected(j);
                found = true;
            }
        }
    }
}