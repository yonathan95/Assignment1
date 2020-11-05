#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Session;

class Agent{
public:
    //Constructors:
    Agent();

    //Virtual functions:
    virtual Agent* clone() const = 0;
    virtual void act(Session& session)=0;
};

class ContactTracer: public Agent{
public:
    //Constructors:
    ContactTracer();

    //Virtual functions:
    virtual void act(Session& session);
    virtual Agent* clone() const;
};


class Virus: public Agent{
public:
    //Constructors:
    Virus(int nodeInd);
    Virus(const Virus& other);

    //Virtual functions:
    virtual void act(Session& session);
    virtual Agent* clone() const;

private:
    //Fields:
    const int nodeInd;
};

#endif
