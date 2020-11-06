#include "Session.h"
#include <vector>
#include <unordered_set>

//Constructors:

//empty constructor
Session::Session():g(),treeType(Root),agents(vector<Agent*>()),infectedQueue(vector<int>()),currCycle(0){

}

//regular constructor
Session::Session(const std::string& path):g(),treeType(Root),agents(vector<Agent*>()),infectedQueue(vector<int>()),currCycle(0){
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
    Graph* pG = new Graph(j["graph"]);//TODO change made
    g = *pG;//TODO change made
}

//copy constructor
Session::Session(const Session& other):g(other.g),treeType(other.treeType),agents(vector<Agent*>()),infectedQueue(other.infectedQueue),currCycle(other.currCycle){
    for (int i = 0; i < other.agents.size();++i){
        Agent* newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
}

//move constructor
Session::Session(Session &&other):g(other.g),treeType(other.treeType),agents(vector<Agent*>(other.agents)),infectedQueue(other.infectedQueue),currCycle(other.currCycle){
    for(int i = 0; i < other.agents.size();++i){
        other.agents[i] = nullptr;
    }
}

//copy assignment
const Session& Session:: operator=(const Session &other){
    if(this != &other){
        treeType = other.treeType;
        g = other.g;
        currCycle = other.currCycle;
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
        currCycle = other.currCycle;
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
int numberOfAgent = 0;
int numberOfAgentAfterIter  = 0;
bool initialized = true;
while((numberOfAgent != numberOfAgentAfterIter) | initialized ){
    initialized = false;
    int numberOfAgent = agents.size();
    for(int i = 0; i < numberOfAgent; ++i){
        agents[i]->act(*this);
    }
    numberOfAgentAfterIter = agents.size();
}
//output:
json j;
vector<int>* pIE = g.getInfectedNodes();
vector<int> v = *pIE;//TODO changes made
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
Graph& Session::getGraphForChange() {
    return g;
}

void Session:: setGraph(const Graph& graph){
    g = graph;
}

int Session::getCurrCycle() const {
    return currCycle;
}