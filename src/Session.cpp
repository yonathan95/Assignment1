#include "Session.h"
#include <vector>

//Constructors:
Session::Session():g(),treeType(0),agents(vector<Agent*>()){

}

Session::Session(const std::string& path):g(),treeType(0),agents(vector<Agent*>()){
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
    for (auto& elem: j["Agents"]){

    }
    //construct graph:
    Graph g(j["graph"]);
}

Session::Session(const Session& other):g(),treeType(other.treeType),agents(vector<Agent*>()){
    for (int i = 0; i < other.agents.size();++i){
        Agent* newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
}


Session::Session():g(),treeType(0),agents(vector<Agent*>()){

}


Session::Session():g(),treeType(0),agents(vector<Agent*>()){

}


Session::Session():g(),treeType(0),agents(vector<Agent*>()){

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