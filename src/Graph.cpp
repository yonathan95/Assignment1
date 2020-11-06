#include "Graph.h"
using namespace std;

//Constructors:
Graph::Graph():edges(vector<vector<int>>()),nodes(vector<int>()){}

// create a deep copy of the matrix.
Graph::Graph(vector<vector<int>> matrix):edges(matrix),nodes(vector<int>(matrix.size())){}

//Class functions:
void Graph::infectNode(int nodeInd){
    bool found = false;
    for(int j = 0 ; j < edges[nodeInd].size()& !(found); ++j){
        if(edges[nodeInd][j] == 1){ // find the neighbor of the node number nodeInd.  
            if(nodes[j]==0){ // find the first virus free neighbor to infect.
                nodes[j] = 1;
                found = true;
            }
        }
    }
}

bool Graph::isInfected(int nodeInd){
    return nodes[nodeInd]!=0;
}


//Getters and setters:

  const vector<int> & Graph::getNodes() const{
     return nodes;
 }
 void Graph::becomeSick(vector<int> &node,int nodeInt) {
    node[nodeInt] = 2;
}
vector<int> Graph::getInfectedNodes(){
    vector <int> output;
    for(int i = 0; i < nodes.size() ; ++i){
        if(nodes[i] != 0){
            output.push_back(i);
        }
    }
    return output;
}
const vector<vector<int>>& Graph::getEdges() const{
    return edges;
}


