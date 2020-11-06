#include "Graph.h"
using namespace std;

//Constructors:
Graph::Graph():edges(vector<vector<int>>()),nodes(vector<int>()){}

// create a deep copy of the matrix.
Graph::Graph(vector<vector<int>> matrix):edges(matrix),nodes(vector<int>(matrix.size())){}

//Class functions:
void Graph::infectNode(int nodeInd){
    nodes[nodeInd] = 1;
}

bool Graph::isInfected(int nodeInd){
    return nodes[nodeInd]!=0;
}


//Getters and setters:

  const vector<int> & Graph::getNodes() const{
     return nodes;
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


