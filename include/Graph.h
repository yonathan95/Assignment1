#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

class Graph{
public:
    //Constructors:
    Graph();
    Graph(vector<std::vector<int>> matrix);

    //Class functions:
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    bool isSick(int nodeInd) const;
    void becomeSick(int nodeInd);
    void quarantineNode(int nodeToQuarantine );

    //Getters and setters:
    const vector<vector<int>>& getEdges() const;
    vector<int> getInfectedNodes();
    void setEdge(int nodeInd, int nodeNeib , int status);

    
private:
    //Fields:
    vector<vector<int>> edges;
};

#endif
