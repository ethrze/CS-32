#include "Actor.h"
#include "StudentWorld.h"
#include <list>
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
    list<Actor*> thisStage = getWorld()->getStage();
    for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
    {
        if ((*q)->who() == IID_BULLET && (*q)->amIDead() == false)
        {
            if(this->getX() == (*q)->getX() && this->getY() == (*q)->getY())
            {
                (*q)->kill();
                return true;
            }
        }
    }
    return false;
}

////////////////
//    WALL    //
////////////////

void Wall::doSomething()
{
    // mostly we do nothing. 'cause we're a wall. 
    if (hit())
    {
        list<Actor*> thisStage = getWorld()->getStage();
        for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
        {
            if ((*q)->who() == IID_BULLET && getX() == (*q)->getX() && getY() == (*q)->getY())
                (*q)->kill();
        }
    }
}

Wall::~Wall() {}


////////////////
//   PLAYER   //
////////////////
void Player::doSomething()
{
    if (amIDead() != true)
    {
        int ch;
        list<Actor*> thisStage = getWorld()->getStage();
        for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
        {
            if (getWorld()->getKey(ch))
            {
                switch(ch)
                {
                    case KEY_PRESS_LEFT:
                        setDirection(left);
                        for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
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
                        for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
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
                        for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
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
                        for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++)
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
                        if (getWorld()->getLives() != 0)
                            getWorld()->decLives();
                        if (getWorld()->getLives() == 0)
                            kill();
//                        getWorld()->diagnostics();
                        break;
                    case KEY_PRESS_SPACE:
                        // fire bullet if there is ammo!
                        if (m_ammo != 0)
                        {
                            decAmmo();
                            if (GraphObject::getDirection() == left)
                                if (getX() - 1 >= 0)
                                    getWorld()->addActor(new Bullet(getX()-1, getY(), getWorld(), left));
                            if (GraphObject::getDirection() == right)
                                if (getX() + 1 < VIEW_WIDTH)
                                    getWorld()->addActor(new Bullet(getX()+1, getY(), getWorld(), right));
                            if (GraphObject::getDirection() == down)
                                if (getY() - 1 >= 0)
                                    getWorld()->addActor(new Bullet(getX(), getY()-1, getWorld(), down));
                            if (GraphObject::getDirection() == up)
                                if (getY() + 1 < VIEW_HEIGHT)
                                    getWorld()->addActor(new Bullet(getX(), getY()+1, getWorld(), up));
                            getWorld()->playSound(SOUND_PLAYER_FIRE);
                        }
                        break;
                        
                }
            }
        }
        if (hit())
        {
            decHealth(2);
            getWorld()->playSound(SOUND_PLAYER_IMPACT);
        }
        if (getHealth() == 0)
        {
            kill();
            getWorld()->playSound(SOUND_PLAYER_DIE);
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
    list<Actor*> thisStage = getWorld()->getStage();
    int xCol = this->getX();
    int yRow = this->getY();
    for (list<Actor*>::iterator q = thisStage.begin(); q != thisStage.end(); q++) // all actors loop
    {
        if (dir == up)
        {
            if (yRow + 1 >= VIEW_HEIGHT)
                count++;
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead()) || ((*q)->who() == IID_SNARLBOT)) &&
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
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead()) || ((*q)->who() == IID_SNARLBOT)) &&
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
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead()) || ((*q)->who() == IID_SNARLBOT)) &&
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
            if (((*q)->who() == IID_WALL || ((*q)->who() == IID_HOLE && !(*q)->amIDead()) || ((*q)->who() == IID_SNARLBOT)) &&
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
int Robot::tickGen() // omnidir
{
    int levelNumber = 2;
    int ticks = (28 - levelNumber) / 4; // levelNumber is the current
    // level number (0, 1, 2, etc.)
    if (ticks < 3)
        ticks = 3; // no SnarlBot moves more frequently than this
    
    return ticks;
}

bool Robot::canMove(Direction dir)
{
    
    int count = 0;
    int xCol = this->getX();
    int yRow = this->getY();
    list<Actor*> ourStage = getWorld()->getStage();
    for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++) // find boulder
    {
        if (dir == left)
        {
            if (xCol - 1 < 0)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_HOLE && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
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
            if ((*q)->who() == IID_HOLE && (*q)->getY() == yRow && (*q)->getX() == xCol+1)
                count++;
        }
        if (dir == up)
        {
            if (yRow + 1 >= VIEW_HEIGHT)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY()+1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY()+1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_HOLE && (*q)->getY()+1 == yRow && (*q)->getX() == xCol)
                count++;
        }
        if (dir == down)
        {
            if (yRow - 1 < 0)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY()-1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY()-1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_HOLE && (*q)->getY()-1 == yRow && (*q)->getX() == xCol)
                count++;
        }
    }
    if (count != 0)
    {
        return false;
    }
    return true;
    
    
}



////////////////
//  HSNARLBOT //
////////////////
void HorizontalSnarlbot::doSomething() // omnidir
{
    if (amIDead() == true)
        return;
    if (m_tick != tickGen())
    {
        m_tick++;
        return;
    }
    if (m_tick == tickGen())
    {
        // try to shoot
        if (shouldShoot(getDirection()))
        {
            // FIRE BULLET!
            // GIVE BULLET TO STUDENT WORLD!
            if (getDirection() == left)
            {
                Actor* bull = new Bullet(getX()-1, getY(), getWorld(), left);
                getWorld()->addActor(bull);
            }
            if (getDirection() == right)
            {
                Actor* bull = new Bullet(getX()+1, getY(), getWorld(), right);
                getWorld()->addActor(bull);
            }
            if (getDirection() == down)
            {
                Actor* bull = new Bullet(getX(), getY()-1, getWorld(), down);
                getWorld()->addActor(bull);
            }
            if (getDirection() == up)
            {
                Actor* bull = new Bullet(getX(), getY()+1, getWorld(), up);
                getWorld()->addActor(bull);
            }
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        
        // try to move
        else if (canMove(getDirection()))
        {
            if (getDirection() == left)
                moveLeft();
            if (getDirection() == right)
                moveRight();
            if (getDirection() == down)
                moveDown();
            if (getDirection() == up)
                moveUp();
        }
        
        if (hit())
        {
            if (m_health != 0)
            {
                m_health -= 2;
                getWorld()->playSound(SOUND_ROBOT_IMPACT);
            }
            if (m_health == 0)
            {
                kill();
                getWorld()->playSound(SOUND_ROBOT_DIE);
                getWorld()->increaseScore(100);
            }
        }
        m_tick = 1;
    }
}

bool HorizontalSnarlbot::canMove(Direction dir) // omnidir
{
    int count = 0;
    int xCol = this->getX();
    int yRow = this->getY();
    list<Actor*> ourStage = getWorld()->getStage();
    for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++) // find boulder
    {
        if (dir == left)
        {
            if (xCol - 1 < 0)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_HOLE && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
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
            if ((*q)->who() == IID_HOLE && (*q)->getY() == yRow && (*q)->getX() == xCol+1)
                count++;
        }
        if (dir == up)
        {
            if (yRow + 1 >= VIEW_HEIGHT)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY()+1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY()+1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_HOLE && (*q)->getY()+1 == yRow && (*q)->getX() == xCol)
                count++;
        }
        if (dir == down)
        {
            if (yRow - 1 < 0)
                count++;
            if ((*q)->who() == IID_WALL && (*q)->getY()-1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY()-1 == yRow && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_HOLE && (*q)->getY()-1 == yRow && (*q)->getX() == xCol)
                count++;
        }
    }
    if (count != 0)
    {
        if (dir == left)
            setDirection(right);
        if (dir == right)
            setDirection(left);
        if (dir == up)
            setDirection(down);
        if (dir == down)
            setDirection(up);
        return false;
    }
    return true;
}

int HorizontalSnarlbot::tickGen()
{
    return Robot::tickGen();
}

bool HorizontalSnarlbot::shouldShoot(Direction dir) // omnidir
{
    if (dir == left)
    {
        if (getWorld()->getPlayer()->getY() == this->getY() && getWorld()->getPlayer()->getX() < this-> getX() && noObstacles(this->getX(), getWorld()->getPlayer()->getX(), dir))
        {
            // SHOOT
            return true;
        }
        return false;
    }
    if (dir == right)
    {
        if (getWorld()->getPlayer()->getY() == this->getY() && getWorld()->getPlayer()->getX() > this-> getX() && noObstacles(this->getX(), getWorld()->getPlayer()->getX(), dir))
        {
            // SHOOT
            return true;
        }
        return false;
    }
    if (dir == down)
    {
        if (getWorld()->getPlayer()->getX() == this->getX() && getWorld()->getPlayer()->getY() < this-> getY() && noObstacles(this->getY(), getWorld()->getPlayer()->getY(), dir))
        {
            // SHOOT
            return true;
        }
        return false;
    }
    if (dir == up)
    {
        if (getWorld()->getPlayer()->getX() == this->getX() && getWorld()->getPlayer()->getY() > this-> getY() && noObstacles(this->getY(), getWorld()->getPlayer()->getY(), dir))
        {
            // SHOOT
            return true;
        }
        return false;
    }
    return false; // shouldn't make it here
}

bool HorizontalSnarlbot::noObstacles(int xCols, int pxCols, Direction dir) // omnidir
{
    if (dir == right)
    {
        list<Actor*> ourStage = getWorld()->getStage();
        for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
        {
            for (int i = xCols; i < pxCols; i++)
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
        list<Actor*> ourStage = getWorld()->getStage();
        for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
        {
            for (int i = xCols; i >= pxCols; i--)
            {
                if (((*q)->who() == IID_WALL || (*q)->who() == IID_BOULDER) && this->getY() == (*q)->getY() && i == (*q)->getX())
                {
                    return false;
                }
                
            }
        }
    }
    if (dir == up)
    {
        list<Actor*> ourStage = getWorld()->getStage();
        for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
        {
            for (int i = xCols; i < pxCols; i++)
            {
                if (((*q)->who() == IID_WALL || (*q)->who() == IID_BOULDER) && this->getX() == (*q)->getX() && i == (*q)->getY())
                {
                    return false;
                }
                
            }
        }
    }
    if (dir == down)
    {
        list<Actor*> ourStage = getWorld()->getStage();
        for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
        {
            for (int i = xCols; i >= pxCols; i--)
            {
                if (((*q)->who() == IID_WALL || (*q)->who() == IID_BOULDER) && this->getX() == (*q)->getX() && i == (*q)->getY())
                {
                    return false;
                }
                
            }
        }
    }
    return true;
}

////////////////
//  VSNARLBOT //
////////////////

// INHERITANCE TOO GOOD BRUH


////////////////
//  KLEPTOBOT //
////////////////

void Kleptobot::doSomething()
{
    if (amIDead() == true)
        return;
    if (m_tick != tickGen())
    {
        m_tick++;
        return;
    }
    if (m_tick == tickGen())
    {
        
        list<Actor*> ourStage = getWorld()->getStage();
        for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
        {
            if ( ((*q)->who() == IID_EXTRA_LIFE || (*q)->who() == IID_RESTORE_HEALTH || (*q)->who() == IID_AMMO) &&
                (*q)->getX() == this->getX() && (*q)->getY() == this->getY() && hasGoodie == false)
            {
                if ( 1 == rand() % 10)
                {
                    stolenGoodie = (*q)->who();
                    hasGoodie = true;
                    (*q)->kill();
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    return;
                }
            }
        }
        
        // try to move
        if (moves != dBT && canMove(getDirection()))
        {
            if (getDirection() == left)
                moveLeft();
            if (getDirection() == right)
                moveRight();
            if (getDirection() == down)
                moveDown();
            if (getDirection() == up)
                moveUp();
            moves++;
        }
        
        if (!canMove(getDirection()) || moves == dBT)
        {
            // pick random new dBT
            dBT = dbtGen();
            moves = 0;
            // pick random new direction
            getRandDir();
            
            if (!canMove(m_dir))
                getRandDir();
            
            if (!canMove(left) && !canMove(right) && !canMove(up) && !canMove(down))
            {
                m_dir = right;
                return;
            }
            
        }
        
        if (hit())
        {
            if (m_health != 0)
            {
                m_health -= 2;
                getWorld()->playSound(SOUND_ROBOT_IMPACT);
            }
            if (m_health == 0)
            {
                kill();
                
                if (stolenGoodie == IID_AMMO)
                {
                    Actor* ammo = new Ammo(getX(), getY(), getWorld());
                    getWorld()->getStage().push_back(ammo);
                }
                if (stolenGoodie == IID_EXTRA_LIFE)
                {
                    Actor* extra = new ExtraLifeGoodie(getX(), getY(), getWorld());
                    getWorld()->getStage().push_back(extra);
                }
                if (stolenGoodie == IID_RESTORE_HEALTH)
                {
                    Actor* restore = new RestoreHealthGoodie(getX(), getY(), getWorld());
                    getWorld()->getStage().push_back(restore);
                }
                
                getWorld()->playSound(SOUND_ROBOT_DIE);
                getWorld()->increaseScore(10);
            }
        }
        m_tick = 1;
    }
}



/////////////////
// ANGRYKLEPTO //
/////////////////



////////////////
//   BOULDER  //
////////////////
void Boulder::doSomething()
{
    if (hit())
    {
        hitPts -= 2;
        
    }
    if (hitPts == 0)
        kill();
}

bool Boulder::canMove(Direction dir)
{
    int count = 0;
    int xCol = this->getX();
    int yRow = this->getY();
    list<Actor*> ourStage = getWorld()->getStage();
    for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++) // find boulder
    {
        if (dir == up)
        {
            if (yRow + 1 >= VIEW_HEIGHT)
                count++;
            if (((*q)->who() == IID_WALL || (*q)->who() == IID_SNARLBOT || (*q)->who() == IID_KLEPTOBOT ||
                 (*q)->who() == IID_ANGRY_KLEPTOBOT) && (*q)->getY() == yRow+1 && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow+1 && (*q)->getX() == xCol)
                count++;
        }
        if (dir == down)
        {
            if (yRow - 1 < 0)
                count++;
            if (((*q)->who() == IID_WALL || (*q)->who() == IID_SNARLBOT || (*q)->who() == IID_KLEPTOBOT ||
                 (*q)->who() == IID_ANGRY_KLEPTOBOT) && (*q)->getY() == yRow-1 && (*q)->getX() == xCol)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow-1 && (*q)->getX() == xCol)
                count++;
        }
        if (dir == left)
        {
            if (xCol - 1 < 0)
                count++;
            if (((*q)->who() == IID_WALL || (*q)->who() == IID_SNARLBOT || (*q)->who() == IID_KLEPTOBOT ||
                 (*q)->who() == IID_ANGRY_KLEPTOBOT) && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
            if ((*q)->who() == IID_BOULDER && (*q)->getY() == yRow && (*q)->getX() == xCol-1)
                count++;
        }
        if (dir == right)
        {
            if (xCol + 1 >= VIEW_WIDTH)
                count++;
            if (((*q)->who() == IID_WALL || (*q)->who() == IID_SNARLBOT || (*q)->who() == IID_KLEPTOBOT ||
                 (*q)->who() == IID_ANGRY_KLEPTOBOT) && (*q)->getY() == yRow && (*q)->getX() == xCol+1)
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

////////////////
//   BULLET   //
////////////////
void Bullet::doSomething()
{
    if (m_dir == left)
        Actor::moveLeft();
    if (m_dir == right)
        Actor::moveRight();
    if (m_dir == up)
        Actor::moveUp();
    if (m_dir == down)
        Actor::moveDown();
}

Bullet::~Bullet() { }

////////////////
//    HOLE    //
////////////////

void Hole::doSomething()
{
    list<Actor*> ourStage = getWorld()->getStage();
    for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
    {
        if ((*q)->who() == IID_BOULDER && this->getX() == (*q)->getX() && this->getY() == (*q)->getY())
        {
            (*q)->kill();
            this->kill();
        }
    }
}

Hole::~Hole() { }


////////////////
//    EXIT    //
////////////////
void Exit::doSomething()
{
    /* this bit works */
    int count = 0;
    list<Actor*> ourStage = getWorld()->getStage();
    for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
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
            getWorld()->playSound(SOUND_FINISHED_LEVEL);
            getWorld()->endLevel();
        }
    }
}

Exit::~Exit() { }

////////////////
//   GOODIE   //
////////////////
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

////////////////
//    JEWEL   //
////////////////
void Jewel::goodieSpec()
{
    
}

////////////////
//   X LIFE   //
////////////////
void ExtraLifeGoodie::goodieSpec()
{
    getWorld()->incLives();
}

////////////////
//  HEALTH G  //
////////////////
void RestoreHealthGoodie::goodieSpec()
{
    getWorld()->getPlayer()->setHealth(20);
}

////////////////
//    AMMO    //
////////////////
void Ammo::goodieSpec()
{
    getWorld()->getPlayer()->addAmmo(20);
}

////////////////
//ROBOT FACTORY/
////////////////
void KleptobotFactory::doSomething()
{
    int count = 0;
    int lowColBound = getX() - 3;
    int highColBound = getX() + 3;
    int lowRowBound = getY() - 3;
    int highRowBound = getY() + 3;
    if (getY() - 3 < 0)
        lowRowBound = 0;
    if (getY() + 3 >= VIEW_HEIGHT)
        highRowBound = VIEW_HEIGHT-1;
    if (getX() - 3 < 0)
        lowColBound = 0;
    if (getX() + 3 >= VIEW_WIDTH)
        highColBound = VIEW_WIDTH-1;
    
    
    bool flag = false;
    for (int r = lowRowBound; r <= highRowBound; r++)
    {
        for (int c = lowColBound; c <= highColBound; c++)
        {
            list<Actor*> ourStage = getWorld()->getStage();
            for (list<Actor*>::iterator q = ourStage.begin(); q != ourStage.end(); q++)
            {
                if((*q)->getX() == c && (*q)->getX() == r)
                    count++;
                else if((*q)->getX() == getX() && (*q)->getY() == getY())
                    flag = true;
                else
                    flag = false;
            }
            
        }
    }
    if (count < 3 && flag != true)
    {
        if ( 3 == rand() % 50) // that 1 in 50 chance
        {
            // honey, we're having a kleptobot!
            getWorld()->playSound(SOUND_ROBOT_BORN);
            if (angry == true)
            {
                Actor* baby = new AngryKleptobot(getX(), getY(), getWorld());
                getWorld()->addActor(baby);
            } else {
                Actor* baby = new Kleptobot(getX(), getY(), getWorld());
                getWorld()->addActor(baby);
            }
        } // end probability if
    } // end sensical if
    
}






