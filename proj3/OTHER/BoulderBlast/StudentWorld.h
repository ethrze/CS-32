#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>

using namespace std;

class Actor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);

    virtual int init();

    virtual int move(); // basically the 'tick' method

    virtual void cleanUp();
    
    virtual GameWorld* getWorld()
    { return world; }
    
    virtual vector<Actor*> getStage()
    {
        return m_stage;
    }

//    virtual void updateDisplayText();
    
    virtual int levelLoader();

private:
    StudentWorld* world = this;

    std::string assDir;
    
    std::vector<Actor*> m_stage;
    
    Actor* m_player;
};






#endif // STUDENTWORLD_H_
