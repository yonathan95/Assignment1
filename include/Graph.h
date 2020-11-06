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
    bool isSick(int nodeInd) const;
    vector<int> getInfectedNodes();
    void becomeSick(int nodeInd);
    int numberOfsick();
    //Getters and setters:
    const vector <int> & getNodes() const;
    const vector<vector<int>>& getEdges() const;

    
private:
    //Fields:
    vector<vector<int>> edges;
    vector<int> nodes;
};

#endif
