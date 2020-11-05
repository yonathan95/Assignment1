#include "Tree.h"
using namespace std;

//Class Tree:

//Constructors:

Tree::Tree():node(),children(vector<Tree*>()){}

Tree::Tree(int rootLabel):node(rootLabel),children(vector<Tree*>()){}

Tree::Tree(const Tree &other):node(other.node),children(vector<Tree*>()){//
    for(int i = 0; i < other.children.size();++i){
        Tree* newTree = other.children[i]->clone();
        children.push_back(newTree);
    }
}
//move constructor
Tree::Tree(Tree &&other):node(other.node),children(other.children){
    for(int i = 0; i < other.children.size();++i){
        other.children[i] = nullptr;
    }
}
//copy assignment
const Tree& Tree:: operator=(const Tree &other){
    if(this != &other){
        node = other.node;
        clear();
        children = vector<Tree*>(other.children.size());
        for(int i = 0; i < other.children.size();++i){
            *children[i] = *other.children[i];
        }
    }
    return *this;
}
//move assignment
const Tree& Tree:: operator=(Tree &&other){//TODO check
    if (this != &other){
        node = other.node;
        clear();
        children = other.children;
        for(int i = 0; i < other.children.size();++i){
            other.children[i] = nullptr;
        }
    }
    return *this;
}

//Destructor:
Tree:: ~Tree(){
    for(int i = 0; i < children.size();++i){
        if (children[i]){
            delete children[i];
            children[i] = nullptr;
        }
    }
}

//Class functions:

void Tree:: addChild(const Tree& child){//TODO complete

}

void Tree:: addChild(Tree* child){//TODO delete child & complete

}

void Tree:: clear(){
    for(int i = 0; i < children.size();++i){
        if (children[i]){
            delete children[i];
            children[i] = nullptr;
        }
    }
}

//Static functions:

Tree* createTree(const Session& session, int rootLabel){
    if(session.getTreeType() == MaxRank){

    }
    else if(session.getTreeType() == Cycle){

    }
    else{

    }
}//TODO complete

//---------------------------------------------------------------------------------------------------//
//Class CycleTree:

//Constructor:
CycleTree:: CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

//Virtual functions:
Tree* CycleTree::clone(){
    return new CycleTree(*this);
};
int CycleTree::traceTree() {//TODO complete

}

//---------------------------------------------------------------------------------------------------//
//Class MaxRankTree:

//Constructors:
MaxRankTree:: MaxRankTree(int rootLabel):Tree(rootLabel){}

//Virtual functions:
Tree* MaxRankTree::clone(){
    return new MaxRankTree(*this);
};

int MaxRankTree::traceTree() {//TODO complete

}

//---------------------------------------------------------------------------------------------------//
//Class RootTree:

//Constructor:
RootTree:: RootTree(int rootLabel):Tree(rootLabel){}



//Virtual functions:
Tree* RootTree::clone(){
    return new RootTree(*this);
};

int RootTree::traceTree() {
    return node;
}