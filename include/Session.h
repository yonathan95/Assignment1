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
    Session(const std::string& path);//TODO Elad complete
    Session(const Session& other);
    Session(Session &&other);
    const Session& operator=(const Session &other);
    const Session& operator=(Session &&other);

    //Destructors:
    virtual ~Session();//TODO delete all agents in the vector //TODO Elad complete

    //Class functions:
    void simulate();
    void clear();
    void addAgent(const Agent& agent);//TODO Elad complete
    void setGraph(const Graph& graph);
    void enqueueInfected(int);//TODO Elad complete
    void setInfected(int);//TODO Elad complete
    int dequeueInfected();//TODO Elad complete
    TreeType getTreeType() const;
    const Graph getGraph() const;//TODO Elad complete

    
private:
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
};

#endif
