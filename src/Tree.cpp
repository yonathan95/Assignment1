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

Tree::Tree(Tree &&other):node(other.node),children(other.children){
    for(int i = 0; i < other.children.size();++i){
        other.children[i] = nullptr;
    }
}

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

const Tree& Tree:: operator=(Tree &&other){
    if (this != &other){
        node = other.node;
        clear();
        children = vector<Tree*>(other.children.size());
        for(int i = 0; i < other.children.size();++i){
            other.children[i] = nullptr;
        }
    }
    return *this;
}

//Destructor: TODO delete clones
Tree:: ~Tree(){
    for(int i = 0; i < children.size();++i){
        if (children[i]){
            delete children[i];
            children[i] = nullptr;
        }
    }
}


//Class functions:

void Tree:: addChild(const Tree& child){

}

void Tree:: addChild(Tree* child){//TODO delete child

}

void Tree:: clear(){
    for(int i = 0; i < children.size();++i){
        if (children[i]){
            delete children[i];
            children[i] = nullptr;
        }
    }
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