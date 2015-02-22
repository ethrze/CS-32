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
        if (true) {
            
        }
        
    }
    else
    {
        return; // you're dead
    }
}

bool Player::canMove(Direction dir)
{
    
    return false;
}

Player::~Player() {}