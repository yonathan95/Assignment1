#include "Tree.h"
using namespace std;

//Class Tree:

//Constructors:

Tree::Tree():node(),children(vector<Tree*>()){//TODO complete

}

Tree::Tree(int rootLabel):node(rootLabel),children(vector<Tree*>()){//TODO complete

}

Tree::Tree(const Tree &other):node(),children(vector<Tree*>()){//TODO complete

}

Tree::Tree(Tree &&other):node(),children(vector<Tree*>()){//TODO complete

}

const Tree& Tree:: operator=(const Tree &other):node(),children(vector<Tree*>()){//TODO complete

}

const Tree& Tree:: operator=(Tree &&other):node(),children(vector<Tree*>()){//TODO complete

}

Tree::Tree():node(),children(vector<Tree*>()){//TODO complete

}

//Destructors:



//Class functions:

void Tree:: addChild(const Tree& child){

}

void Tree:: addChild(Tree* child){//TODO delete child

}

//Getters and Setters:

//Static functions:

Tree* createTree(const Session& session, int rootLabel){
    if(session.getTreeType() == MaxRank){

    }
    else if(session.getTreeType() == Cycle){

    }
    else{

    }
}

//Pure Virtual functions:

//---------------------------------------------------------------------------------------------------
//Class CycleTree:



//---------------------------------------------------------------------------------------------------
//Class MaxRankTree:

//---------------------------------------------------------------------------------------------------
//Class RootTree: