#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    //Constructors:
    Session();
    Session(const std::string& path);
    Session(const Session& other);
    Session(Session &&other);
    const Session& operator=(const Session &other);
    const Session& operator=(Session &&other);

    //Destructor:
    virtual ~Session();

    //Class functions:
    void simulate();
    void clearAgents();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    void setInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    const Graph& getGraph() const;
    int getCurrCycle() const;
    void quarantineNode(int nodeToQuarantine );
    void becomeSick(int nodeInd);
    bool isNodeInfected(int nodeInd);

private:
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
    vector<int> infectedQueue;
    int currCycle;
};

#endif
