#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//    ________  __    __  ________        __       __   ______   ______  __    __
//   /        |/  |  /  |/        |      /  \     /  | /      \ /      |/  \  /  |
//   $$$$$$$$/ $$ |  $$ |$$$$$$$$/       $$  \   /$$ |/$$$$$$  |$$$$$$/ $$  \ $$ |
//      $$ |   $$ |__$$ |$$ |__          $$$  \ /$$$ |$$ |__$$ |  $$ |  $$$  \$$ |
//      $$ |   $$    $$ |$$    |         $$$$  /$$$$ |$$    $$ |  $$ |  $$$$  $$ |
//      $$ |   $$$$$$$$ |$$$$$/          $$ $$ $$/$$ |$$$$$$$$ |  $$ |  $$ $$ $$ |
//      $$ |   $$ |  $$ |$$ |_____       $$ |$$$/ $$ |$$ |  $$ | _$$ |_ $$ |$$$$ |
//      $$ |   $$ |  $$ |$$       |      $$ | $/  $$ |$$ |  $$ |/ $$   |$$ | $$$ |
//      $$/    $$/   $$/ $$$$$$$$/       $$/      $$/ $$/   $$/ $$$$$$/ $$/   $$/
// Giant ASCII art makes sure I know which file I'm in. The other file says "the other file." Very adept.


////////////////
//    ACTOR   //
////////////////

bool Actor::canMove()
{
    return false;
}

// MOVE FUNCTIONS
// Only to be used if canMove
void Actor::moveUp()
{
    this->moveTo(this->getX()+1, this->getY());
}

void Actor::moveDown()
{
    this->moveTo(this->getX()-1, this->getY());
}

void Actor::moveLeft()
{
    this->moveTo(this->getX(), this->getY()-1);
}

void Actor::moveRight()
{
    this->moveTo(this->getX(), this->getY()+1);
}


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
                    if (canMove(this->getX()-1, this->getY()))
                    {
                        this->moveTo(this->getX()-1, this->getY());
                    }
                    break;
                case KEY_PRESS_RIGHT:
                    setDirection(right);
                    if (canMove(this->getX()+1, this->getY()))
                    {
                        this->moveTo(this->getX()+1, this->getY());
                    }
                    break;
                case KEY_PRESS_UP:
                    setDirection(up);
                    if (canMove(this->getX(), this->getY()+1))
                    {
                        this->moveTo(this->getX(), this->getY()+1);
                    }
                    break;
                case KEY_PRESS_DOWN:
                    setDirection(down);
                    if (canMove(this->getX(), this->getY()-1))
                    {
                        this->moveTo(this->getX(), this->getY()-1);
                    }
                    
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
    if (dx > VIEW_WIDTH || dx < 0)
        count++;
    if (dy > VIEW_HEIGHT || dy < 0)
        count++;
    for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++) // all actors loop
    {
        if ((*q)->who() == IID_BOULDER && !(*q)->canMove() && (*q)->getX() == dx && (*q)->getY() == dy)
            count++;
        
        // no running through WALL or BOULDER
        if ((*q)->who() == IID_WALL && (*q)->getX() == dx && (*q)->getY() == dy)
            count++;
    }
    
    if (count != 0)
    {
        return false;
    }
    else {
        return true;
    }
}

Player::~Player() {}


void Jewel::doSomething()
{
    if (getWorld()->getPlayer()->getX() == this->getX() && getWorld()->getPlayer()->getY() == this->getY())
    {
        this->kill();
        setVisible(false); // this should probably be temporary
        // you'll want this to effect POINTS
    }
}

Jewel::~Jewel() {}


void Boulder::doSomething()
{
    if (hitPts == 0)
        kill();
    
}

bool Boulder::canMove()
{
//    int count = 0;
//    Direction dir = getWorld()->getPlayer()->getDirection();
    vector<Actor*> ourStage = getWorld()->getStage();
    for (vector<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++) // find boulder
    {
        
        
        
    }
    return false;
}

Boulder::~Boulder() {}




