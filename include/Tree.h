#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
#include "Graph.h"
#include "Agent.h"


class Session;

class Tree{
public:
    //Constructors:TODO rule of 5
    Tree();
    Tree(int rootLabel);
    Tree(const Tree &other);
    Tree(Tree &&other);
    const Tree& operator=(const Tree &other);
    const Tree& operator=(Tree &&other);

    //Destructor:
    virtual ~Tree();

    //Class functions:
    void addChild(const Tree& child);
    void addChild(Tree* child); 
    
    //Getters and Setters:
    int getNode() const;
    std::vector<Tree*> getChildren() const;
    void setNode(int num);
    void setChildren(std::vector<Tree*>); 
    

    //Static functions:
    static Tree* createTree(const Session& session, int rootLabel);

    //Pure Virtual functions
    virtual int traceTree()=0;
    virtual Tree* clone(const Tree& child)=0;

private:
    //Fields:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();

private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};



#endif
