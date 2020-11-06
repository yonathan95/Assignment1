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
    void becomeSick(int nodeInd);
    int numberOfsick();
    void quarantineNode(int nodeToQuarantine );

    //Getters and setters:
    const vector <int> & getNodes() const;
    const vector<vector<int>>& getEdges() const;
    vector<int> getInfectedNodes();

    
private:
    //Fields:
    vector<vector<int>> edges;
    vector<int> nodes;
};

#endif
