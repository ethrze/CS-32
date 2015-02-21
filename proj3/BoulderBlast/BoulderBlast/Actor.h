#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// THIS IS PART 1.

class Actor : public GraphObject {
public:
    Actor()
    : GraphObject(IID_WALL, 0, 0, none)
    { }
    virtual void doSomething() {
        // the actor does something
    }
    virtual ~Actor() {}
private:
    
    
};




#endif // ACTOR_H_