#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

////////////////
//    ACTOR   //
////////////////



////////////////
//    WALL    //
////////////////

Wall::~Wall() {}


////////////////
//   PLAYER   //
////////////////
void Player::doSomething()
{
    if (amIDead() != true)
    {
        int ch;
        if (getWorld()->getKey(ch))
        {
            switch(ch)
            {
                case KEY_PRESS_LEFT:
                    
                    
                    
                    
                    setDirection(left);
                    break;
                case KEY_PRESS_RIGHT:
                    
                    break;
                case KEY_PRESS_UP:
                    
                    break;
                case KEY_PRESS_DOWN:
                    
                    break;
                case KEY_PRESS_ESCAPE:
                    
                    break;
                case KEY_PRESS_SPACE:
                    
                    break;
            }
            
        }
    }
    else
    {
        return; // you're dead
    }
}

bool Player::canMove(int dx, int dy)
{
    int count = 0;
    vector<Actor*> thisStage = getWorld()->getStage();
    for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++) // all actors loop
    {
        if ((*q)->who() == IID_WALL)
            count++;
    }
    if (count != 0)
        return false;
    else
        return true;
}

Player::~Player() {}















