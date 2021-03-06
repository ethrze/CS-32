#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <list>

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
    
    virtual Actor* getPlayer()
    {
        return m_player;
    }
    
    virtual list<Actor*> getStage()
    {
        return m_stage;
    }
    
    virtual void endLevel(); 
    
    virtual int getCurrentScore() { return m_score; }
    virtual int getCurrentGameLevel() { return getLevel(); }
    virtual int getCurrentLevelBonus() { return levBonus; }
    virtual int getNumberOfLivesThePlayerHasLeft() { return m_lives; }
    
    void diagnostics(); 
    
    void updateDisplayText(); 
    
    virtual void incScore(int plus) { m_score+=plus; }
    virtual void decScore(int minu)
    {
        if (m_score - minu >= 0)
            m_score-=minu;
        m_score = 0;
    }
    virtual void decLevBonus()
    {
        if (levBonus != 0)
            levBonus--;
    }
    virtual int getLevBonus() { return levBonus; }
    virtual void resetBonus() { levBonus = 1000; }
    
    virtual void addActor(Actor* act); 
    
    virtual void removeDeadGameObjects();

//    virtual void updateDisplayText();
    
    virtual int levelLoader();

private:
    StudentWorld* world = this;

    std::string assDir;
    
    std::list<Actor*> m_stage;
    
    Actor* m_player;
    
    int m_score;
    int levBonus;
    int m_lives;
    
    bool m_endLevel;
};

#endif // STUDENTWORLD_H_
