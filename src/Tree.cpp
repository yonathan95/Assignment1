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
const Tree& Tree:: operator=(Tree &&other){
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

Tree* createTree(const Session& session, int rootLabel){
    Tree* pTree;
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

void Tree::bfs(const Session& session, int rootLabel) {
    vector<vector<int>> edges = session.getGraph().getEdges();
    vector<Tree*> queue = vector<Tree*>();
    vector<int> isVisited = vector<int>(edges.size());
    for(int i = 0; i < edges.size();++i ){
        if(edges[node][i] == 1){
            Tree* tree = createTree(session,rootLabel);
            edges[node][i] = edges[i][node] = 0;
            queue.push_back(tree);
            addChild(tree);
        }
    }

    while(!queue.empty()){
        Tree* child = queue[0];
        queue.erase(queue.begin());
        if(isVisited[(child)->node] != 1){
            isVisited[child->node] = 1;
            for(int i = 0; i < edges.size();++i ){
                if(edges[child->node][i] == 1){
                    Tree* tree = createTree(session,rootLabel);
                    edges[child->node][i] = edges[i][child->node] = 0;
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

int Tree::getNode() {
    return node;
}

vector<int>& Tree:: maxRank(int depth){
    vector<int> result = vector<int>(3);
    result[0] = node;
    result[1] = children.size();
    result[2] = depth;
    vector<int> newResult = vector<int>(3);
    for (int i = 0;i < children.size();++i){
        newResult = children[i]->maxRank(depth+1);
        if (newResult[1] > result[1]){
            result = newResult;
        }
        else if(newResult[1] = result[1]){
            if(newResult[2] < result[2]){
                result = newResult;
            }
            else if(newResult[2] = result[2]){
                if(newResult[0] < result[0]){
                    result = newResult;
                }
            }
        }
    }
    return result;
}


//---------------------------------------------------------------------------------------------------//
//Class CycleTree:

//Constructor:
CycleTree:: CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

//Class functions:
void CycleTree::setCurrCycle(int cycle) {
    currCycle = cycle;
}

//Virtual functions:
Tree* CycleTree::clone() const{
    return new CycleTree(*this);
};
int CycleTree::traceTree() {
    if(children.empty()|currCycle == 0){
        return node;
    }
    else{
        Tree* tree = children[0];
        for (int i = 0; i < currCycle -1;++i){
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
    return result[0];
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