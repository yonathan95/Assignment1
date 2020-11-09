#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"
#include "Graph.h"
#include "Tree.h"

class Session;

class Agent{
public:
    //Constructors:
    Agent();

    //Destructor:
    virtual ~Agent();

    //Virtual functions:
    virtual Agent* clone() const = 0;
    virtual void act(Session& session)=0;
};

class ContactTracer: public Agent{
public:
    //Constructors:
    ContactTracer();

    //Virtual functions:
    virtual Agent* clone() const;
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    //Constructors:
    Virus(int nodeInd);
    Virus(const Virus& other);

    //Virtual functions:
    virtual Agent* clone() const;
    virtual void act(Session& session);
private:
    //Fields:
    const int nodeInd;
};

#endif
