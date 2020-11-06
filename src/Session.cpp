#include "Session.h"
#include <vector>
#include <unordered_set>

//Constructors:

//empty constructor
Session::Session():g(),treeType(treeType),agents(vector<Agent*>()){

}

//regular constructor
Session::Session(const std::string& path):g(),treeType(treeType),agents(vector<Agent*>()){
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
    vector<Agent*> newAgents;
    for (auto& elem: j["Agents"]){//TODO complete

    }
    //construct graph:
    Graph g(j["graph"]);
}

//copy constructor
Session::Session(const Session& other):g(other.g),treeType(other.treeType),agents(vector<Agent*>()){
    for (int i = 0; i < other.agents.size();++i){
        Agent* newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
}

//move constructor
Session::Session(Session &&other):g(other.g),treeType(other.treeType),agents(vector<Agent*>(other.agents)){
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
        clear();
        agents = other.agents;
        for(int i = 0; i < other.agents.size();++i){
            other.agents[i] = nullptr;
        }
    }
    return *this;
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

void Session:: addAgent(const Agent& agent){
    Agent* clone = agent.clone();//
}

void Session:: clear(){
    for(int i = 0; i < agents.size();++i){
        if (agents[i]){
            delete agents[i];
            agents[i] = nullptr;
        }
    }
}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session:: setGraph(const Graph& graph){
    g = graph;
}