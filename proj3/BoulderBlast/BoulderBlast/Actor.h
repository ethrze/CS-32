#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
using namespace std;

//    ________  __    __  ________        __       __   ______   ______  __    __
//   /        |/  |  /  |/        |      /  \     /  | /      \ /      |/  \  /  |
//   $$$$$$$$/ $$ |  $$ |$$$$$$$$/       $$  \   /$$ |/$$$$$$  |$$$$$$/ $$  \ $$ |
//      $$ |   $$ |__$$ |$$ |__          $$$  \ /$$$ |$$ |__$$ |  $$ |  $$$  \$$ |
//      $$ |   $$    $$ |$$    |         $$$$  /$$$$ |$$    $$ |  $$ |  $$$$  $$ |
//      $$ |   $$$$$$$$ |$$$$$/          $$ $$ $$/$$ |$$$$$$$$ |  $$ |  $$ $$ $$ |
//      $$ |   $$ |  $$ |$$ |_____       $$ |$$$/ $$ |$$ |  $$ | _$$ |_ $$ |$$$$ |
//      $$ |   $$ |  $$ |$$       |      $$ | $/  $$ |$$ |  $$ |/ $$   |$$ | $$$ |
//      $$/    $$/   $$/ $$$$$$$$/       $$/      $$/ $$/   $$/ $$$$$$/ $$/   $$/
//


class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// THIS IS PART 1.

class Actor : public GraphObject {
public:
    Actor(const int IID, int sx, int sy, StudentWorld* world)
    : GraphObject(IID, sx, sy, none), m_homeworld(world), m_dead(0), m_IID(IID) // the closest you can get to a generic GraphObject
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
    
    virtual StudentWorld* getWorld()
    {
        return m_homeworld;
    }
    
    virtual int who()
    {
        return m_IID;
    }
    
    virtual bool canMove(Direction dir);
    
    virtual void moveUp();
    
    virtual void moveDown();
    
    virtual void moveLeft();
    
    virtual void moveRight();
    
    virtual int getHealth() { return 0; }
    virtual void setHealth(int num) { }
    virtual int getAmmo() { return 0; }
    virtual void setAmmo(int num) {}
    virtual void addAmmo(int num) {}
    virtual void decAmmo() {}
    
    virtual ~Actor() {}
    
private:
    StudentWorld* m_homeworld;
    bool m_dead;
    int m_IID;
    
};


class Player : public Actor {
public:
    Player(int sx, int sy, StudentWorld* world, Direction startDir = right)
    : Actor(IID_PLAYER, sx, sy, world), m_dead(0), m_ammo(20), m_health(20)
    {
        setDirection(startDir);
        // is initialized facing RIGHT
        setVisible(true);
    }
    
    virtual void doSomething();
    
    virtual void getDirection()
    {
        return this->getDirection();
    }
    
    virtual int getHealth() { return m_health; }
    virtual void setHealth(int num) { m_health = num; }
    
    virtual int getAmmo() { return m_ammo; }
    void setAmmo(int num) { m_ammo = num; }
    void addAmmo(int num) { m_ammo += num; }
    void decAmmo()
    {
        if (m_ammo != 0)
            m_ammo--;
    }

    virtual bool canMove(Direction dir); 
    
    virtual ~Player();
    
private:
    bool m_dead;
    int m_health;
    int m_ammo;
    
};





/*  / / / / / / / / / / / / /
        INANIMATE OBJECTS
    / / / / / / / / / / / / /  */


// / / / / / / / / / / //
//         WALL        //
// / / / / / / / / / / //
class Wall : public Actor {
public:
    Wall(int sx, int sy, StudentWorld* world)
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


// / / / / / / / / / / //
//       BOULDER       //
// / / / / / / / / / / //
class Boulder : public Actor {
public:
    Boulder(int sx, int sy, StudentWorld* world)
    : Actor(IID_BOULDER, sx, sy, world), m_dead(0), hitPts(10)
    {
        setVisible(true);
    }
    
    virtual void kill() { m_dead = 1; }
    
    virtual void doSomething();
    
    virtual bool canMove(Direction dir);
    
    virtual bool amIDead() { return m_dead; }
    
    virtual ~Boulder();
private:
    bool m_dead;
    int hitPts;
};
// / / / / / / / / / / //
//        BULLET       //
// / / / / / / / / / / //
class Bullet : public Actor {
public:
    Bullet(int sx, int sy, StudentWorld* world, Direction dir)
    : Actor(IID_BULLET, sx, sy, world), m_dead(0)
    {
        setVisible(true);
        setDirection(dir);
    }
    
    virtual void kill() { m_dead = 1; }
    
    virtual void doSomething();
    
    virtual ~Bullet();
    
private:
    bool m_dead;
};
// / / / / / / / / / / //
//         HOLE        //  isn't even a great band...
// / / / / / / / / / / //
class Hole : public Actor {
public:
    Hole(int sx, int sy, StudentWorld* world)
    : Actor(IID_HOLE, sx, sy, world), m_dead(0)
    {
        setVisible(true);
    }
    
    virtual void kill() { m_dead = true; }
    
    virtual void doSomething();
    
    virtual bool amIDead() { return m_dead; }
    
    virtual ~Hole();
private:
    bool m_dead;
};
// / / / / / / / / / / //
//         EXIT        //
// / / / / / / / / / / //
class Exit : public Actor {
public:
    Exit(int sx, int sy, StudentWorld* world)
    : Actor(IID_EXIT, sx, sy, world), m_dead(0), m_active(0)
    {
        
    }
    
    virtual void kill() { m_dead = true; }
    virtual bool amIDead() { return m_dead; }
    
    virtual void doSomething();
    
    virtual void setActive() { m_active = true; setVisible(true); }
    
    
    
    virtual ~Exit();
private:
    bool m_dead;
    bool m_active;
};

// / / / / / / / / / / //
//      GEN GOODIE     //
// / / / / / / / / / / //
class Goodie : public Actor {
public:
    Goodie(int sx, int sy, StudentWorld* world, const int goodID)
    : Actor(goodID, sx, sy, world), m_dead(0)
    {
        setVisible(true);
        setDirection(none);
    }
    
    virtual void doSomething();
    
    virtual void givePoints();
    
    virtual void goodieSpec() {}
    virtual int getPoints() { return m_points; }
    
    virtual void kill() { m_dead = true; }
    virtual bool amIDead() { return m_dead; }
    
    ~Goodie() { }
private:
    bool m_dead;
    int m_points;
    
};

// / / / / / / / / / / //
//        JEWEL        //
// / / / / / / / / / / //
class Jewel : public Goodie {
public:
    Jewel(int sx, int sy, StudentWorld* world)
    : Goodie(sx, sy, world, IID_JEWEL), m_dead(0)
    {
        setVisible(true);
        setDirection(none);
    }
    
    void goodieSpec();
    int getPoints() { return m_points; }
    
    virtual int who() { return IID_JEWEL; }
    
    virtual void kill() { m_dead = true; }
    virtual bool amIDead() { return m_dead; }
    
    ~Jewel() {}
private:
    int m_points = 50;
    bool m_dead;
};

// / / / / / / / / / / //
//    X LIFE GOODIE    //
// / / / / / / / / / / //
class ExtraLifeGoodie : public Goodie {
public:
    ExtraLifeGoodie(int sx, int sy, StudentWorld* world)
    : Goodie(sx, sy, world, IID_EXTRA_LIFE), m_dead(0)
    {
        setVisible(true);
        setDirection(none);
    }
    
    void goodieSpec();
    int getPoints() { return m_points; }
    
    virtual void kill() { m_dead = true; }
    virtual bool amIDead() { return m_dead; }
    
    ~ExtraLifeGoodie() {}
private:
    int m_points = 1000;
    bool m_dead;
};

// / / / / / / / / / / //
//    HEALTH GOODIE    //
// / / / / / / / / / / //
class RestoreHealthGoodie : public Goodie {
public:
    RestoreHealthGoodie(int sx, int sy, StudentWorld* world)
    : Goodie(sx, sy, world, IID_RESTORE_HEALTH), m_dead(0)
    {
        setVisible(true);
        setDirection(none);
    }
    
    void goodieSpec();
    int getPoints() { return m_points;}
    
    virtual void kill() { m_dead = true; }
    virtual bool amIDead() { return m_dead; }
    
    ~RestoreHealthGoodie() {}
private:
    int m_points = 500;
    bool m_dead;
};

// / / / / / / / / / / //
//     AMMO GOODIE     //
// / / / / / / / / / / //
class Ammo : public Goodie {
public:
    Ammo(int sx, int sy, StudentWorld* world)
    : Goodie(sx, sy, world, IID_AMMO), m_dead(0)
    {
        setVisible(true);
        setDirection(none);
    }
    
    void goodieSpec();
    int getPoints() { return m_points;}
    
    virtual void kill() { m_dead = true; }
    virtual bool amIDead() { return m_dead; }
    
    ~Ammo() {}
private:
    int m_points = 100;
    bool m_dead;
};







#endif // ACTOR_H_