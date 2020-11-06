#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
#include "Graph.h"
#include "Agent.h"


class Session;

class Tree{
public:
    //Constructors:
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
    void clear();
    void bfs(const Session& session, int rootLabel);

    //Static functions:
    static Tree* createTree(const Session& session, int rootLabel);

    //Pure Virtual functions
    virtual int traceTree()=0;
    virtual Tree* clone() const = 0;

protected:
    //Fields:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    //Constructor:TODO rule of 5
    CycleTree(int rootLabel, int currCycle);

    //Class functions:
    void setCurrCycle(int cycle);

    //Virtual functions:
    virtual int traceTree();
    virtual Tree* clone() const;

private:
    //Fields:
    int currCycle;
};

class MaxRankTree: public Tree{//TODO rule of 5
public:
    //Constructor:
    MaxRankTree(int rootLabel);

    //Virtual functions:
    virtual int traceTree();
    virtual Tree* clone() const;

private:
    //Field:
    vector<int> ranks;
};

class RootTree: public Tree{
public:
    //Constructor:
    RootTree(int rootLabel);

    //Virtual functions:
    virtual int traceTree();
    virtual Tree* clone() const;
};



#endif
