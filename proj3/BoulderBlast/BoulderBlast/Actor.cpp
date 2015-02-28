#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>

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

bool Actor::canMove(Direction dir)
{
    return false;
}

// MOVE FUNCTIONS
// Only to be used if canMove
void Actor::moveUp()
{
    this->moveTo(this->getX(), this->getY()+1);
}

void Actor::moveDown()
{
    this->moveTo(this->getX(), this->getY()-1);
}

void Actor::moveLeft()
{
    this->moveTo(this->getX()-1, this->getY());
}

void Actor::moveRight()
{
    this->moveTo(this->getX()+1, this->getY());
}

bool Actor::hit()
{
    vector<Actor*> thisStage = getWorld()->getStage();
    for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
    {
        if ((*q)->who() == IID_BULLET)
        {
            if(this->getX() == (*q)->getX() && this->getY() == (*q)->getY())
                return true;
        }
    }
    return false;
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
        vector<Actor*> thisStage = getWorld()->getStage();
        for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
        {
            if (getWorld()->getKey(ch))
            {
                switch(ch)
                {
                    case KEY_PRESS_LEFT:
                        setDirection(left);
                        for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
                        {
                            if ((*q)->who() == IID_BOULDER && this->getX()-1 == (*q)->getX() &&
                                this->getY() == (*q)->getY())
                            {
                                if ((*q)->canMove(left) && this->canMove(left))
                                    (*q)->moveLeft();
                            }
                        }
                        if (canMove(left))
                        {
                            this->moveLeft();
                        }
                        
                        break;
                    case KEY_PRESS_RIGHT:
                        setDirection(right);
                        for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
                        {
                            if ((*q)->who() == IID_BOULDER && this->getX()+1 == (*q)->getX() &&
                                this->getY() == (*q)->getY())
                            {
                                if ((*q)->canMove(right) && this->canMove(right))
                                    (*q)->moveRight();
                            }
                        }
                        if (canMove(right))
                        {
                            this->moveRight();
                        }
                        break;
                    case KEY_PRESS_UP:
                        setDirection(up);
                        // THIS IS HOW WE MOVE BOULDERS
                        for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
                        {
                            if ((*q)->who() == IID_BOULDER && this->getX() == (*q)->getX() &&
                                this->getY() == (*q)->getY()-1)
                            {
                                if ((*q)->canMove(up) && this->canMove(up))
                                    (*q)->moveUp();
                            }
                        }
                        if (canMove(up))
                        {
                            this->moveUp();
                        }
                        break;
                    case KEY_PRESS_DOWN:
                        setDirection(down);
                        for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
                        {
                            if ((*q)->who() == IID_BOULDER && this->getX() == (*q)->getX() &&
                                this->getY() == (*q)->getY()+1)
                            {
                                if ((*q)->canMove(down) && this->canMove(down))
                                    (*q)->moveDown();
                            }
                        }
                        if (canMove(down))
                        {
                            this->moveDown();
                        }
                        
                        break;
                    case KEY_PRESS_ESCAPE:
//                        getWorld()->decLives();
                        getWorld()->diagnostics();
                        break;
                    case KEY_PRESS_SPACE:
                        // fire bullet if there is ammo!
                        break;
                }
            }
        }
    }
    else
    {
        return; // you're dead
    }
}


bool Player::canMove(Direction dir)
{
    int count =0;
    vector<Actor*> thisStage = getWorld()->getStage();
    int xCol = this->getX();
    int yRow = this->getY();
    for (vector<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++) // all actors loop
    {
        if (dir == up)
        {
            if (yRow + 1 >= VIEW_HEIGHT)
                count++;
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead())) &&
                (*q)->getY() == yRow+1 && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER  && !(*q)->amIDead() &&
                (*q)->getY() == yRow+1 && (*q)->getX() == xCol && !(*q)->canMove(up))
                count++;
        }
        if (dir == down)
        {
            if (yRow - 1 < 0)
                count++;
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead())) &&
                (*q)->getY() == yRow-1 && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER  && !(*q)->amIDead() &&
                (*q)->getY() == yRow-1 && (*q)->getX() == xCol && !(*q)->canMove(down))
                count++;
        }
        if (dir == left)
        {
            if (xCol - 1 < 0)
                count++;
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead())) &&
                (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_BOULDER  && !(*q)->amIDead() &&
                (*q)->getY() == yRow && (*q)->getX() == xCol-1 && !(*q)->canMove(left))
                count++;
        }
        if (dir == right)
        {
            if (xCol + 1 >= VIEW_WIDTH)
                count++;
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead())) &&
                (*q)->getY() == yRow && (*q)->getX() == xCol+1)
                count++;
            if ((*q)->who() == IID_BOULDER && !(*q)->amIDead() &&
                (*q)->getY() == yRow && (*q)->getX() == xCol+1 && !(*q)->canMove(right))
                count++;
        }
    }
    if (count != 0)
        return false;
    return true;
}


Player::~Player() {}


// SNARLBOT

void HorizontalSnarlbot::doSomething()
{
    if (amIDead() == true)
        return;
    if (m_tick != 0)
    {
        tickMachine();
        return;
    }
    if (m_tick == 0)
    {
        // try to shoot
        if (shouldShoot(getDirection()))
        {
            // FIRE BULLET!
            // GIVE BULLET TO STUDENT WORLD!
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        
        // try to move
        if (canMove(getDirection()))
        {
            if (getDirection() == left)
                moveLeft();
            if (getDirection() == right)
                moveRight();
        }
        
        if (hit())
        {
            if (m_health != 0)
            {
                m_health -= 2;
                getWorld()->playSound(SOUND_ROBOT_IMPACT);
            }
            if (amIDead())
            {
                kill();
                getWorld()->playSound(SOUND_ROBOT_DIE);
                getWorld()->increaseScore(100);
            }
            
        }
        
        
    }
    
    
}

bool HorizontalSnarlbot::canMove(Direction dir)
{
    int count = 0;
    int xCol = this->getX();
    int yRow = this->getY();
    vector<Actor*> ourStage = getWorld()->getStage();
    for (vector<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++) // find boulder
    {
        if (dir == left)
        {
            if (xCol - 1 < 0)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
        }
        if (dir == right)
        {
            if (xCol + 1 >= VIEW_WIDTH)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow && (*q)->getX() == xCol+1)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow && (*q)->getX() == xCol+1)
                count++;
        }
    }
    if (count != 0)
    {
        if (dir == left)
            setDirection(right);
        if (dir == right)
            setDirection(left);
        return false;
    }
    return true;
}

bool HorizontalSnarlbot::shouldShoot(Direction dir)
{
    if (getWorld()->getPlayer()->getY() == this->getY() && noObstacles(this->getX(), this->getY(), dir))
    {
        // SHOOT
        return true;
    }
    return false;
}

int HorizontalSnarlbot::tickGen()
{
    int levelNumber = 2;
    int ticks = (28 - levelNumber) / 4; // levelNumber is the current
    // level number (0, 1, 2, etc.)
    if (ticks < 3)
        ticks = 3; // no SnarlBot moves more frequently than this
    
    return ticks;
}
bool HorizontalSnarlbot::noObstacles(int xCols, int yRows, Direction dir)
{
    if (dir == right)
    {
        vector<Actor*> ourStage = getWorld()->getStage();
        for (vector<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
        {
            for (int i = xCols; i < VIEW_WIDTH; i++)
            {
                if (((*q)->who() == IID_WALL || (*q)->who() == IID_BOULDER) && this->getY() == (*q)->getY() && i == (*q)->getX())
                {
                    return false;
                }
            
            }
        }
    }
    if (dir == left)
    {
        vector<Actor*> ourStage = getWorld()->getStage();
        for (vector<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
        {
            for (int i = xCols; i >= 0; i--)
            {
                if (((*q)->who() == IID_WALL || (*q)->who() == IID_BOULDER) && this->getY() == (*q)->getY() && i == (*q)->getX())
                {
                    return false;
                }
                
            }
        }
    }
    return true;
}

void HorizontalSnarlbot::tickMachine()
{
    m_tick--; 
}

void Boulder::doSomething()
{
    if (hitPts == 0)
        kill();
}

bool Boulder::canMove(Direction dir)
{
    int count = 0;
    int xCol = this->getX();
    int yRow = this->getY();
    vector<Actor*> ourStage = getWorld()->getStage();
    for (vector<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++) // find boulder
    {
        if (dir == up)
        {
            if (yRow + 1 >= VIEW_HEIGHT)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow+1 && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow+1 && (*q)->getX() == xCol)
                count++;
        }
        if (dir == down)
        {
            if (yRow - 1 < 0)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow-1 && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow-1 && (*q)->getX() == xCol)
                count++;
        }
        if (dir == left)
        {
            if (xCol - 1 < 0)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
        }
        if (dir == right)
        {
            if (xCol + 1 >= VIEW_WIDTH)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow && (*q)->getX() == xCol+1)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow && (*q)->getX() == xCol+1)
                count++;
        }
    }
    if (count != 0)
        return false;
    return true;
}

Boulder::~Boulder() { }


void Bullet::doSomething()
{
    
}

Bullet::~Bullet() { }

void Hole::doSomething()
{
    vector<Actor*> ourStage = getWorld()->getStage();
    for (vector<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
    {
        if ((*q)->who() == IID_BOULDER && this->getX() == (*q)->getX() && this->getY() == (*q)->getY())
        {
            (*q)->kill();
            this->kill();
        }
    }
}

Hole::~Hole() { }

void Exit::doSomething()
{
    /* this bit works */
    int count = 0;
    vector<Actor*> ourStage = getWorld()->getStage();
    for (vector<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
    {
        if ((*q)->who() == IID_JEWEL)
            count++;
    }
    if (count == 0 && m_active == false)
    {
        getWorld()->playSound(SOUND_REVEAL_EXIT);
        setActive(); // this sets the active indicator to true, makes the exit visible;
        
    }
    /*                */
    
    if (m_active == true)
    {
        if (getWorld()->getPlayer()->getX() == this->getX() && getWorld()->getPlayer()->getY() == this->getY())
        {
            kill();
            getWorld()->endLevel();
        }
    }
}

Exit::~Exit() { }


void Goodie::doSomething()
{
    if (amIDead())
        return;
    if (this->getX() == getWorld()->getPlayer()->getX() && this->getY() == getWorld()->getPlayer()->getY())
    {
        this->givePoints();
        this->kill();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        this->goodieSpec();
    }
}

void Goodie::givePoints()
{
    getWorld()->increaseScore(this->getPoints());
}

void Jewel::goodieSpec()
{
    
}

void ExtraLifeGoodie::goodieSpec()
{
    getWorld()->incLives();
}

void RestoreHealthGoodie::goodieSpec()
{
    getWorld()->getPlayer()->setHealth(20);
}

void Ammo::goodieSpec()
{
    getWorld()->getPlayer()->addAmmo(20);
}