#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// THIS IS PART 1.

class Actor : public GraphObject {
public:
    Actor(const int IID, int sx, int sy)
    : GraphObject(IID, sx, sy, none) // the closest you can get to a generic GraphObject
    { } // may need to put in checks on sx sy
    
    virtual void doSomething() {
        // it's a generic actor, why would it actually do something?
    }
    
    GameWorld* getWorld()
    {
        return StudentWorld::getWorld();
    }
    
    virtual ~Actor() {}
    
private:
    
    
};

class Wall : public Actor {
public:
    Wall(int sx, int sy)
    : Actor(IID_WALL, sx, sy)
    {
        //setVisible(true); // do we need this on a wall?
        // the default direction is already NONE
        
    }

    // Actor's doSomething class already does nothing.
    
    virtual ~Wall();
    
};


class Player : public Actor {
public:
    Player(int sx, int sy, Direction startDir = right)
    : Actor(IID_PLAYER, sx, sy), m_dead(0)
    {
        setDirection(startDir);
        // is initialized facing RIGHT
        setVisible(true);
    }
    
    virtual void doSomething();
    
    virtual bool amIDead() {
        return m_dead;
    }
    
    virtual void kill() {
        m_dead = true;
    }
    
    bool canMove(Direction dir);
    
    virtual ~Player();
    
private:
    bool m_dead;
    
};


#endif // ACTOR_H_