#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// THIS IS PART 1.

class Actor : public GraphObject {
public:
    Actor(const int IID, int sx, int sy)
    : GraphObject(IID, sx, sy, none) // the closest you can get to a generic GraphObject
    { } // may need to put in checks on sx sy
    
    virtual void doSomething() {
        // the actor does something
    }
    virtual ~Actor() {}
    
private:
    
    
};

class Wall : public Actor {
public:
    Wall(int sx, int sy)
    : Actor(IID_WALL, sx, sy)
    {
        // the default direction is already NONE
    }
    
    virtual void doSomething() {
        // that was beautiful.
    }
    virtual ~Wall() {}
    
};


class Player : public Actor {
public:
    Player(int sx, int sy, Direction startDir)
    : Actor(IID_PLAYER, sx, sy), m_dead(0)
    {
        setDirection(startDir);
    }
    
    virtual void doSomething() {
        
    }
    
    
    virtual bool amIDead()
    {
        return m_dead;
    }
    virtual void kill()
    {
        m_dead = true;
    }
    virtual ~Player() {}
    
private:
    bool m_dead;
    
};


#endif // ACTOR_H_