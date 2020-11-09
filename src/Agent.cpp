#include "Agent.h"
#include <vector>

//Class Agent:

//Constructors:
Agent:: Agent(){}

//Destructors:
Agent:: ~Agent()= default;

//---------------------------------------------------------------------------------------------------//
//Class ContactTracer:

//Constructors:
ContactTracer:: ContactTracer():Agent(){}

//Virtual functions:
Agent* ContactTracer:: clone() const{
    // will be deleted in session destructor.
    return new ContactTracer(*this);
}

void ContactTracer:: act(Session& session){
    Graph& g = session.getGraphForChange();
    int rootLabel = session.dequeueInfected();
    if (rootLabel != -1){ //Infected queue is not empty.
        Tree* tree = Tree::createTree(session,rootLabel);
        tree->bfs(session);
        int nodeToQuarantine = tree->traceTree();
        delete tree;
        g.quarantineNode(nodeToQuarantine);
    }
}

//---------------------------------------------------------------------------------------------------//
//Class Virus:

//Constructors:
Virus:: Virus(int nodeInd):Agent(),nodeInd(nodeInd){}

Virus:: Virus(const Virus& other):Agent(),nodeInd(other.nodeInd){}

//Virtual functions:
Agent* Virus:: clone() const{
    return new Virus(*this);
}

void Virus:: act(Session& session){
    Graph& g = session.getGraphForChange();
    if(!(g.isSick(nodeInd))){
        g.becomeSick(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    bool found = false;
    for(int j = 0 ; (j < g.getEdges().size()) & !(found); ++j){
        if((g.getEdges()[nodeInd][j] == 1) & !(g.isInfected(j))){     //Finds the first virus free neighbour.
            session.setInfected(j);
            found = true;
        }
    }
}