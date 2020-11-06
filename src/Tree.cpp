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

void Tree:: addChild(const Tree& child){
    Tree* tree = child.clone();
    children.push_back(tree);
}

void Tree:: addChild(Tree* child){
    children.push_back(child);
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

Tree* createTree(const Session& session, int rootLabel, int cycle){//TODO complete
    if(session.getTreeType() == MaxRank){
        MaxRankTree tree = MaxRankTree(rootLabel);
        tree.bfs(session.getGraph(),rootLabel,cycle);
    }
    else if(session.getTreeType() == Cycle){
        CycleTree tree = CycleTree(rootLabel,cycle);
    }
    else{
        RootTree tree = RootTree(rootLabel);
    }
}


//---------------------------------------------------------------------------------------------------//
//Class CycleTree:

//Constructor:
CycleTree:: CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

//Class functions:
void CycleTree::setCurrCycle(int cycle) {
    currCycle = cycle;
}

Tree* Tree::bfs(const Graph& g, Tree& tree, int cycle) {
    vector<vector<int>> edges = g.getEdges();
    for(int i = 0; i < edges.size();++i ){
        if(edges[tree.node][i] == 1){

        }
    }
}

//Virtual functions:
Tree* CycleTree::clone() const{
    return new CycleTree(*this);
};
int CycleTree::traceTree() {//TODO complete

}

//---------------------------------------------------------------------------------------------------//
//Class MaxRankTree:

//Constructors:
MaxRankTree:: MaxRankTree(int rootLabel):Tree(rootLabel),ranks(vector<int>()){}

//Virtual functions:
Tree* MaxRankTree::clone() const{
    return new MaxRankTree(*this);
};

int MaxRankTree::traceTree() {//TODO complete

}

//---------------------------------------------------------------------------------------------------//
//Class RootTree:

//Constructor:
RootTree:: RootTree(int rootLabel):Tree(rootLabel){}



//Virtual functions:
Tree* RootTree::clone() const{
    return new RootTree(*this);
};

int RootTree::traceTree() {
    return node;
}