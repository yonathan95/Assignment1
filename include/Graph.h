#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

class Graph{
public:
    //Constructors:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);

    //Class functions:
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    vector<int> getInfectedNodes();

    //Getters and setters:
    const vector <int> & getNodes() const;
    void becomeSick(vector<int> & node,int nodeInt);
    const vector<vector<int>>& getEdges() const;
    const Graph getGraph() const;//TODO Elad complete
    
private:
    //Fields:
    vector<vector<int>> edges;
    vector<int> nodes;
};

#endif
