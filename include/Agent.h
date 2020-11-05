#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Session;

class Agent{
public:
    //Constructors:
    Agent();
    Agent(Session& session);

    //Virtual functions:
    virtual Agent* clone() const = 0;
    virtual void act() = 0;

protected:
    //Fields:
    Session& session;
};

class ContactTracer: public Agent{
public:
    //Constructors:
    ContactTracer(Session& session);
    ContactTracer(const ContactTracer& other);

    //Virtual functions:
    virtual void act();
    virtual Agent* clone() const;
};


class Virus: public Agent{
public:
    //Constructors:
    Virus(int nodeInd, Session& session);
    Virus(const Virus& other);

    //Virtual functions:
    virtual void act();
    virtual Agent* clone() const;

private:
    //Fields:
    const int nodeInd;
};

#endif
