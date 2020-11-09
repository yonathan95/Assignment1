#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
#include "Graph.h"

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
    void clearChildren();
    void bfs(const Session& session);
    const vector<Tree*>& getChildren() const;
    int getNode() const;

    //Static functions:
    static Tree* createTree(const Session& session, int rootLabel);

    //Pure Virtual functions
    virtual int traceTree()=0;
    virtual Tree* clone() const = 0;

protected:
    //Fields:
    int node;
    vector<Tree*> children;
    vector<int> maxRank(int depth);
};

class CycleTree: public Tree{
public:
    //Constructor:
    CycleTree();
    CycleTree(int rootLabel, int currCycle);
    CycleTree(const CycleTree &other);
    CycleTree(CycleTree &&other);
    const CycleTree& operator=(const CycleTree &other);
    const CycleTree& operator=(CycleTree &&other);

    //Virtual functions:
    virtual int traceTree();
    virtual Tree* clone() const;

private:
    //Fields:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    //Constructor:
    MaxRankTree(int rootLabel);

    //Virtual functions:
    virtual int traceTree();
    virtual Tree* clone() const;
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
