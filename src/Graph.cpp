#include "Graph.h"
using namespace std;

//Constructors:

//Empty constructor
Graph::Graph():edges(vector<vector<int>>()){}

//Regular constructor
Graph::Graph(vector<vector<int>> matrix):edges(matrix){}

//Class functions:
void Graph::infectNode(int nodeInd){
    edges[nodeInd][nodeInd] = 1;
}

bool Graph::isInfected(int nodeInd){
    return edges[nodeInd][nodeInd] != 0;
}

bool Graph::isSick(int nodeInd) const{
    return (edges[nodeInd][nodeInd] == 2);
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
vector<int> Graph::getInfectedNodes(){
    vector<int> output = vector<int>();
    for(unsigned int i = 0; i < edges.size(); ++i){
        if(edges[i][i] != 0){
            output.push_back(i);
            edges[i][i] = 0;
        }
    }
    return output;
}

const vector<vector<int>>& Graph::getEdges() const{
    return edges;
}




