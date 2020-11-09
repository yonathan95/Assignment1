#include <iostream>
#include "Tree.h"
using namespace std;

//Class Tree:

//Constructors:

//Empty constructor
Tree::Tree():node(),children(vector<Tree*>()){}

//Regular constructor
Tree::Tree(int rootLabel):node(rootLabel),children(vector<Tree*>()){}

//Copy constructor
Tree::Tree(const Tree &other):node(other.node),children(vector<Tree*>()){//
    for(auto i : other.children){
        Tree* newTree = i->clone();
        children.push_back(newTree);
    }
}

//Move constructor
Tree::Tree(Tree &&other):node(other.node),children(other.children){
    for(auto & i : other.children){
        i = nullptr;
    }
}

//Copy assignment
const Tree& Tree:: operator=(const Tree &other){
    if(this != &other){
        node = other.node;
        clearChildren();
        children = vector<Tree*>(other.children.size());
        for(unsigned int i = 0; i < other.children.size();++i){
            *children[i] = *other.children[i];
        }
    }
    return *this;
}

//Move assignment
const Tree& Tree:: operator=(Tree &&other){
    if (this != &other){
        node = other.node;
        clearChildren();
        children = other.children;
        for(auto & child : other.children){
            child = nullptr;
        }
    }
    return *this;
}

//Destructor:
Tree:: ~Tree(){
    clearChildren();
}

//Class functions:

void Tree:: addChild(const Tree& child){
    Tree* tree = child.clone();
    children.push_back(tree);
}

void Tree:: addChild(Tree* child){
    children.push_back(child);
}

void Tree:: clearChildren(){
    for(auto & child : children){
        if (child){
            delete child;
            child = nullptr;
        }
    }
}

//Static functions:

Tree* Tree::createTree(const Session& session, int rootLabel){
    if(session.getTreeType() == MaxRank){
        return new MaxRankTree(rootLabel);
    }
    else if(session.getTreeType() == Cycle){
        return new CycleTree(rootLabel, session.getCurrCycle());
    }
    else{
        return new RootTree(rootLabel);
    }
}

void Tree::bfs(const Session& session) {
    const vector<vector<int>> *pEdges = &(session.getGraph().getEdges());
    vector<Tree*> queue = vector<Tree*>();
    vector<int> isVisited = vector<int>(pEdges->size());
    isVisited[node] = 2;
    for(unsigned int i = 0; i < pEdges->size(); ++i ){
        if((i != node) & ((*pEdges)[node][i] == 1) ){
            isVisited[i] = 1;
            Tree *tree = createTree(session, i);
            queue.push_back(tree);
            addChild(tree);
        }
    }
    while(!queue.empty()){
        Tree* child = queue[0];
        queue.erase(queue.begin());
        if(isVisited[(child)->node] != 2){
            isVisited[child->node] = 2;
            for(int i = 0; i < pEdges->size(); ++i ){
                if((i != child->node) & (isVisited[i] == 0) & ((*pEdges)[child->node][i] == 1)){
                    Tree* tree = createTree(session,i);
                    isVisited[i] = 1;
                    queue.push_back(tree);
                    child->addChild(tree);
                }
            }
        }
    }
}

const vector<Tree*>& Tree::getChildren() const {
    return children;
}

int Tree::getNode() const{
    return node;
}

vector<int> Tree:: maxRank(int depth){
    vector<int> result = vector<int>(3);
    result[0] = node;
    result[1] = children.size();
    result[2] = depth;
    vector<int> newResult = vector<int>(3);
    for (auto & i : children){
        newResult = i->maxRank(depth+1);
        if (newResult[1] > result[1]){
            result = newResult;
        }
        else if(newResult[1] == result[1]){
            if(newResult[2] < result[2]){
                result = newResult;
            }
            else if((newResult[2] == result[2]) & (newResult[0] < result[0])){
                result = newResult;
            }
        }
    }
    return result;
}


//---------------------------------------------------------------------------------------------------//
//Class CycleTree:

//Constructors:

//Empty constructor:
CycleTree::CycleTree():Tree(),currCycle(0){}

//Regular constructor:
CycleTree:: CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

//Copy constructor:
CycleTree:: CycleTree(const CycleTree &other):Tree(other),currCycle(other.currCycle){}

//Move constructor:
CycleTree:: CycleTree(CycleTree &&other):Tree(other),currCycle(other.currCycle){}

//Copy assignment:
const CycleTree& CycleTree:: operator=(const CycleTree &other){
    if(this != &other){
        *this = other;
        currCycle = other.currCycle;
    }
    return *this;
}

//Move assignment:
const CycleTree& CycleTree:: operator=(CycleTree &&other){
    if(this != &other){
        *this = other;
        currCycle = other.currCycle;
    }
    return *this;
}

//Virtual functions:
Tree* CycleTree::clone() const{
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    if(children.empty()|(currCycle == 0)){
        return node;
    }
    else{
        Tree* tree = children[0];
        for (int i = 0; i < currCycle - 1;++i){
            if(!tree->getChildren().empty()){
                tree = tree->getChildren()[0];
            }
            else{
                return tree->getNode();
            }
        }
        return tree->getNode();
    }
}

//---------------------------------------------------------------------------------------------------//
//Class MaxRankTree:

//Constructors:
MaxRankTree:: MaxRankTree(int rootLabel):Tree(rootLabel){}

//Virtual functions:
Tree* MaxRankTree::clone() const{
    return new MaxRankTree(*this);
}

int MaxRankTree::traceTree() {
    vector<int> result = maxRank(0);
    return result[0]; //Node number.
}

//---------------------------------------------------------------------------------------------------//
//Class RootTree:

//Constructor:
RootTree:: RootTree(int rootLabel):Tree(rootLabel){}

//Virtual functions:
Tree* RootTree::clone() const{
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return node;
}