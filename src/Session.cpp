#include "Session.h"
#include <vector>
#include <unordered_set>

//Constructors:

//empty constructor
Session::Session():g(),treeType(treeType),agents(vector<Agent*>()),infectedQueue(vector<int>()){

}

//regular constructor
Session::Session(const std::string& path):g(),treeType(treeType),agents(vector<Agent*>()),infectedQueue(vector<int>()){
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
    //construct agent:
    for (auto& elem: j["Agents"]){
            if(elem[0] == "V"){
                Agent* virus = new Virus(elem[1]);
                agents.push_back(virus);
            }
            else{
                Agent* contactTracer= new ContactTracer();
                agents.push_back(contactTracer);
            }
    }
    //construct graph:
    Graph g(j["graph"]);
}

//copy constructor
Session::Session(const Session& other):g(other.g),treeType(other.treeType),agents(vector<Agent*>()),infectedQueue(other.infectedQueue){
    for (int i = 0; i < other.agents.size();++i){
        Agent* newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
}

//move constructor
Session::Session(Session &&other):g(other.g),treeType(other.treeType),agents(vector<Agent*>(other.agents)),infectedQueue(other.infectedQueue){
    for(int i = 0; i < other.agents.size();++i){
        other.agents[i] = nullptr;
    }
}

//copy assignment
const Session& Session:: operator=(const Session &other){
    if(this != &other){
        treeType = other.treeType;
        g = other.g;
        clear();
        agents = vector<Agent*>(other.agents.size());
        for(int i = 0; i < other.agents.size();++i){
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
        clear();
        agents = other.agents;
        for(int i = 0; i < other.agents.size();++i){
            other.agents[i] = nullptr;
        }
    }
    return *this;
}

// Destructors
Session::~Session() {
    for(int i = 0; i< agents.size();++i) {
        delete agents[i];
    }
}
void Session::simulate(){
    //simulate:










    //output:
    json j;
    vector<int> v = g.getInfectedNodes();
    j["infectedNodes"] = v;
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
void Session:: clear(){
    for(int i = 0; i < agents.size();++i){
        if (agents[i]){
            delete agents[i];
            agents[i] = nullptr;
        }
    }
}

void Session:: enqueueInfected(int nodeInd){
    infectedQueue.push_back(nodeInd);
}
int Session::dequeueInfected() {
    int output = infectedQueue[0];
    infectedQueue.erase(infectedQueue.begin());
}
// change vertics to be infected and add it to the agent list.
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
Graph& Session::getGraphForChange() {
    return g;
}

void Session:: setGraph(const Graph& graph){
    g = graph;
}