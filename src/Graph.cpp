#include <iostream>
#include "Graph.h"
using namespace std;

//Constructors:
Graph::Graph():edges(vector<vector<int>>()){}

// create a deep copy of the matrix.
Graph::Graph(vector<vector<int>> matrix):edges(matrix){}

//Class functions:
void Graph::infectNode(int nodeInd){
    edges[nodeInd][nodeInd] = 1;
}

bool Graph::isInfected(int nodeInd){
    return edges[nodeInd][nodeInd] != 0;
}
bool Graph::isSick(int nodeInd) const{
    return edges[nodeInd][nodeInd] == 2;
}
void Graph::becomeSick(int nodeInd) {
    edges[nodeInd][nodeInd] = 2;
}

void Graph::quarantineNode(int nodeToQuarantine) {
    for(int i = 0; i < edges.size(); ++i){
        if(i != nodeToQuarantine){
            edges[nodeToQuarantine][i] = edges[i][nodeToQuarantine] = 0;
        }

    }
}

//Getters and setters:
vector<int> Graph::getInfectedNodes(){//TODO change made
    vector<int> output = vector<int>();
    for(int i = 0; i < edges.size(); ++i){
        if(edges[i][i] != 0){
            output.push_back(i);
            edges[i][i] = 0;
        }
    }
    return output;
}

void Graph::setEdge(int nodeInd, int nodeNeib, int status) {
    edges[nodeInd][nodeNeib] = edges[nodeNeib][nodeInd] = status;
}

const vector<vector<int>>& Graph::getEdges() const{
    return edges;
}




