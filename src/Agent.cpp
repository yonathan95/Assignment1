#include "Agent.h"
#include <vector>
#include <iostream>



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
    cout <<"1"<<endl;
    Graph g = session.getGraphForChange();
    cout <<"2"<<endl;
    int rootLabel = session.dequeueInfected();
    if (rootLabel != -1){
        cout <<"3"<<endl;
        Tree* tree = Tree::createTree(session,rootLabel);
        cout <<"4"<<endl;
        tree->bfs(session,rootLabel);
        cout <<"5"<<endl;
        int nodeToQuarantine = tree->traceTree();
        cout <<"6"<<endl;
        g.quarantineNode(nodeToQuarantine);
        cout <<"7"<<endl;
    }
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
    Graph& g = session.getGraphForChange();
    //push it-self to the infectedQueue if he hse not been there yet.
    if(!(g.isSick(nodeInd))){
        g.becomeSick(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    bool found = false;
    //looking for the first virus-free neighbour to infect.
    for(int j = 0 ; (j < g.getEdges().size()) & !(found); ++j){
        // find the neighbor of the node number nodeInd.
        if(g.getEdges()[nodeInd][j] == 1){
            // find the first virus free neighbor to infect.
            if(!(g.isInfected(j))){
                session.setInfected(j);
                found = true;
            }
        }
    }
}