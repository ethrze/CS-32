#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// THIS IS PART 1.

class Actor : public GraphObject {
public:
    Actor(const int IID, int sx, int sy, GameWorld* world)
    : GraphObject(IID, sx, sy, none), m_homeworld(world), m_dead(0) // the closest you can get to a generic GraphObject
    { } // may need to put in checks on sx sy
    
    virtual void doSomething()
    {
        // it's a generic actor, why would it actually do something?
    }
    
    virtual bool amIDead()
    {
        return m_dead;
    }
    
    virtual void kill()
    {
        m_dead = true;
    }
    
    virtual GameWorld* getWorld()
    {
        return m_homeworld;
    }
    
    virtual ~Actor() {}
    
private:
    GameWorld* m_homeworld;
    bool m_dead;
    
};

class Wall : public Actor {
public:
    Wall(int sx, int sy, GameWorld* world)
    : Actor(IID_WALL, sx, sy, world), m_dead(0)
    {
        setVisible(true); // do we need this on a wall?
        // the default direction is already NONE
    }
    
    virtual void kill() { } // we don't want walls to be killable, this is a failsafe.

    // Actor's doSomething class already does nothing. No need to override.
    
    virtual ~Wall();
private:
    bool m_dead;
    
};


class Player : public Actor {
public:
    Player(int sx, int sy, GameWorld* world, Direction startDir = right)
    : Actor(IID_PLAYER, sx, sy, world), m_dead(0)
    {
        setDirection(startDir);
        // is initialized facing RIGHT
        setVisible(true);
    }
    
    virtual void doSomething();
    
    
    
    bool canMove(Direction dir);
    
    virtual ~Player();
    
private:
    bool m_dead;
    
};


#endif // ACTOR_H_