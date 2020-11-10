#include "Session.h"
#include <vector>
#include "Agent.h"

//Constructors:

//empty constructor
Session::Session():g(),treeType(Root),agents(vector<Agent*>()),infectedQueue(vector<int>()),currCycle(0){

}

//regular constructor
Session::Session(const std::string& path):g(vector<std::vector<int>>()),treeType(Root),agents(vector<Agent*>()),infectedQueue(vector<int>()),currCycle(0){
    //input
    ifstream i (path);
    json j;
    j << i;

    //construct treeType:
    if (j["tree"] == "M"){
        treeType = MaxRank;
    }
    else if (j["tree"] == "C"){
        treeType = Cycle;
    }
    else{
        treeType = Root;
    }
    g = Graph(j["graph"]);
    for (auto& elem: j["agents"]){
            if(elem[0] == "V"){
                Agent* virus = new Virus(elem[1]);
                agents.push_back(virus);
                g.infectNode(elem[1]);
            }
            else{
                Agent* contactTracer= new ContactTracer();
                agents.push_back(contactTracer);
            }
    }
    //construct graph:

}

//copy constructor
Session::Session(const Session& other):g(other.g),treeType(other.treeType),agents(vector<Agent*>()),infectedQueue(other.infectedQueue),currCycle(other.currCycle){
    for (auto agent : other.agents){
        Agent* newAgent = agent->clone();
        agents.push_back(newAgent);
    }
}

//move constructor
Session::Session(Session &&other):g(other.g),treeType(other.treeType),agents(vector<Agent*>(other.agents)),infectedQueue(other.infectedQueue),currCycle(other.currCycle){
    for(auto & agent : other.agents){
        agent = nullptr;
    }
}

//copy assignment
const Session& Session:: operator=(const Session &other){
    if(this != &other){
        treeType = other.treeType;
        g = other.g;
        infectedQueue = other.infectedQueue;
        currCycle = other.currCycle;
        clearAgents();
        agents = vector<Agent*>(other.agents.size());
        for(unsigned int i = 0; i < other.agents.size();++i){
            *agents[i] = *other.agents[i];
        }
    }
    return *this;
}

//move assignment
const Session& Session:: operator=(Session &&other){
    if (this != &other){
        treeType = other.treeType;
        g = other.g;
        infectedQueue = other.infectedQueue;
        currCycle = other.currCycle;
        clearAgents();
        agents = other.agents;
        for(auto & agent : other.agents){
            agent = nullptr;
        }
    }
    return *this;
}

// Destructor
Session::~Session() {
    clearAgents();
}

void Session::simulate(){
    unsigned int numberOfAgentsAfterIter;
    unsigned int numberOfAgents;
    bool finished = false;
    while(!finished){
        numberOfAgents = agents.size();
        for(unsigned int i = 0; i < numberOfAgents; ++i){
            agents[i]->act(*this);
        }
        numberOfAgentsAfterIter = agents.size();
        finished = (numberOfAgents == numberOfAgentsAfterIter);
        ++currCycle;
    }
    json j;
    vector<int> v = g.getInfectedNodes();
    j["infected"] = v;
    j["graph"] = g.getEdges();
    ofstream i("output.json");
    j >> i;
}

// allocate new memory on the heap for a new agent and add t the the agent list.
void Session:: addAgent(const Agent& agent){
    Agent* clone = agent.clone();
    agents.push_back(clone);
}

//delete the agents vector from the heap.
void Session:: clearAgents(){
    for(auto & agent : agents){
        if (agent){
            delete agent;
            agent = nullptr;
        }
    }
}

void Session:: enqueueInfected(int nodeInd){
    infectedQueue.push_back(nodeInd);
}

int Session::dequeueInfected() {
    if (infectedQueue.empty()){
        return -1;
    }
    int output = infectedQueue[0];
    infectedQueue.erase(infectedQueue.begin());
    return output;
}

// change vertices to be infected and add it to the agent list.
void Session::setInfected(int nodeInd) {
    g.infectNode(nodeInd);
    Virus newVirus(nodeInd);
    addAgent(newVirus);
}

TreeType Session::getTreeType() const {
    return treeType;
}

const Graph& Session::getGraph() const {
    return g;
}

void Session:: setGraph(const Graph& graph){
    g = graph;
}

int Session::getCurrCycle() const {
    return currCycle;
}

void Session::quarantineNode(int nodeToQuarantine) {
    g.graphQuarantineNode(nodeToQuarantine);
}

void Session::becomeSick(int nodeInd){
    g.graphBecomeSick(nodeInd);
}

bool Session::isNodeInfected(int nodeInd){
    return g.isInfected(nodeInd);

}