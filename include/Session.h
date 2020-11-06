#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include <fstream>
#include "json.hpp"
#include "Agent.h"

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

    //Destructors:
    virtual ~Session();

    //Class functions:
    void simulate();
    void clear();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    void setInfected(int);//TODO Elad complete
    int dequeueInfected();
    TreeType getTreeType() const;
    const Graph& getGraph() const;
    Graph& getGraphForChange();
    int getCurrCycle() const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std:: vector<int> infectedQueue;
    int currCycle;
};

#endif
