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
//







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
                    if (canMove(this->getX()-1, this->getY()))
                    {
                        this->moveTo(this->getX()-1, this->getY());
                    }
                    setDirection(left);
                    break;
                case KEY_PRESS_RIGHT:
                    if (canMove(this->getX()+1, this->getY()))
                    {
                        this->moveTo(this->getX()+1, this->getY());
                    }
                    setDirection(right);
                    break;
                case KEY_PRESS_UP:
                    if (canMove(this->getX(), this->getY()+1))
                    {
                        this->moveTo(this->getX(), this->getY()+1);
                    }
                    setDirection(up);
                    break;
                case KEY_PRESS_DOWN:
                    if (canMove(this->getX(), this->getY()-1))
                    {
                        this->moveTo(this->getX(), this->getY()-1);
                    }
                    setDirection(down);
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















