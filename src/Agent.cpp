#include "Agent.h"
#include <vector>
#include <Tree.h>
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

void ContactTracer:: act(Session& session){
    Graph g = session.getGraphForChange();
    int rootLabel = session.dequeueInfected();
    Tree* tree = Tree::createTree(session,rootLabel);
    tree->bfs(session,rootLabel);
    int nodeToQuarantine = tree->traceTree();
    g.quarantineNode(nodeToQuarantine);
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

void Virus:: act(Session& session){
    //push it-self to the infectedQueue if he hse not been there yet.
    if(!(session.getGraph().isSick(nodeInd))){
        session.getGraphForChange().becomeSick(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    bool found = false;
    //looking for the first virus-free neighbour to infect.
    for(int j = 0 ; j < session.getGraph().getEdges().size() & !(found); ++j){
        // find the neighbor of the node number nodeInd.
        if(session.getGraph().getEdges()[nodeInd][j] == 1){
            // find the first virus free neighbor to infect.
            if(!(session.getGraphForChange().isInfected(j))){
                session.setInfected(j);
                found = true;
            }
        }
    }
}