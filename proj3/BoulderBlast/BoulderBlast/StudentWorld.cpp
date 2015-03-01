#include "StudentWorld.h"
#include "Level.h"
#include <string>
#include <list>
#include <iomanip>
#include <sstream>
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




GameWorld* createStudentWorld(string assetDir)
{

    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir), assDir(assetDir), m_endLevel(false), levBonus(1000)
{
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::init()
{
    levelLoader();
    resetBonus();
    m_endLevel = false;
    // getContentsOf(col, row); 

    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() // this is basically the 'tick' method
{
    Level lev(assetDirectory());
    //    Level::LoadResult result = lev.loadLevel(curL);
    int levell = getLevel();
    ostringstream strstrm;
    strstrm.fill('0');
    strstrm << "level" ;
    strstrm << setw(2) << levell;
    strstrm << ".dat";
    string stir = strstrm.str();
    Level::LoadResult res = lev.loadLevel(stir);
    if (res == Level::load_fail_file_not_found)
        return GWSTATUS_PLAYER_WON; // you're out of levels!
    
    // update game status
    // ask everyone to do something
    // remove dead actors
    
    //update display text
    updateDisplayText();
    
    // give each character the chance to do something
   ;
    for (list<Actor*>::iterator q = m_stage.begin(); true; q++) // all actors loop
    {
       if (q!= m_stage.end())
       {
        if (!(*q)->amIDead()) // it's a pointer to a pointer to an actor
        {
            (*q)->doSomething();
            
            if (m_player->amIDead())
                return GWSTATUS_PLAYER_DIED;
            // if completed level
                // increase score
                // return GWSTATUS_FINISHED_LEVEL
        }
       }
       else {
           break;
       }
        
    } // end all actors loop
    
    // remove dead game objects
    removeDeadGameObjects();
    
    if (m_endLevel == true)
        return GWSTATUS_FINISHED_LEVEL;
    
    // reduce level bonus by one
    decLevBonus();
    

    
    if (m_player->amIDead())
        return GWSTATUS_PLAYER_DIED;

    if (m_endLevel == true)
    {
        increaseScore(2000);
        increaseScore(levBonus); // bonus
        return GWSTATUS_FINISHED_LEVEL;
    }
    // if completed level
    // increase score
    // return GWSTATUS_FINISHED_LEVEL
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
//    int count = 0;
//    for (list<Actor*>::iterator q = m_stage.begin(); q != m_stage.end(); q++)
//    {
//        count++;
//    }
//    for (int i = 0; i < count; i++)
//    {
//        Actor* temp = m_stage.back();
//        m_stage.pop_back();
//        delete temp;
//    }
    list<Actor*>::iterator q;
    q = m_stage.begin();
    
    while(q != m_stage.end())
    {
        delete (*q);
        q = m_stage.erase(q);
    }
    
}

void StudentWorld::updateDisplayText() {
    
    int score = getScore();
    int level = getLevel();
    unsigned int bonus = getLevBonus();
    int livesLeft = getLives();
    int hp = m_player->getHealth();
    setprecision(0);
    string perfString = "Score: " + to_string(score) + " Level: " + to_string(level) + " Lives: " + to_string(livesLeft) + " Health: " + to_string((hp/20.0)*100) + "% Ammo: " + to_string(m_player->getAmmo()) + " Bonus: " + to_string(bonus);
    setGameStatText(perfString);
    
}

int StudentWorld::levelLoader()
{
    // LOAD UP YER LEVEL
    Level lev(assetDirectory());
//    Level::LoadResult result = lev.loadLevel(curL);
    int levell = getLevel();
    ostringstream strstrm;
    strstrm.fill('0');
    strstrm << "level" ;
    strstrm << setw(2) << levell;
    strstrm << ".dat";
    string stir = strstrm.str();
    Level::LoadResult res = lev.loadLevel(stir);
    
    
    if (res == Level::load_fail_file_not_found ||
        res == Level::load_fail_bad_format)
        cerr << "Bad levels" << endl; // something bad happened!
    
    
    // FILL UP YER list OF ACTORS
    for (int c = 0; c < VIEW_WIDTH; c++) // col loop
    {
        for (int r = 0; r < VIEW_HEIGHT; r++) // row loop
        {
            Level::MazeEntry atHand = lev.getContentsOf(c, r);
            if (atHand != Level::empty)
            {
                if (atHand == Level::player) {
                    Actor* bigshot = new Player(c, r, this);
                    m_stage.push_back(bigshot);
                    m_player = bigshot;
                }
                // wall
                if (atHand == Level::wall)
                    m_stage.push_back(new Wall(c, r, this));
                // jewel
                if (atHand == Level::jewel)
                    m_stage.push_back(new Jewel(c, r, this));
                // boulder
                if (atHand == Level::boulder)
                    m_stage.push_back(new Boulder(c, r, this));
                // hole
                if (atHand == Level::hole)
                    m_stage.push_back(new Hole(c, r, this));
                // exit
                if (atHand == Level::exit)
                    m_stage.push_back(new Exit(c, r, this));
                // extra life
                if (atHand == Level::extra_life)
                    m_stage.push_back(new ExtraLifeGoodie(c, r, this));
                // retore health
                if (atHand == Level::restore_health)
                    m_stage.push_back(new RestoreHealthGoodie(c, r, this));
                // ammo
                if (atHand == Level::ammo)
                    m_stage.push_back(new Ammo(c, r, this));
                
                
                // HORIZ SNARLBOT
                if (atHand == Level::horiz_snarlbot)
                    m_stage.push_back(new HorizontalSnarlbot(c, r, this));
                // VERT SNARLBOT
                if (atHand == Level::vert_snarlbot)
                    m_stage.push_back(new VerticalSnarlbot(c, r, this));
                
                if (atHand == Level::angry_kleptobot_factory)
                    m_stage.push_back(new KleptobotFactory(c, r, this, true));
                if (atHand == Level::kleptobot_factory)
                    m_stage.push_back(new KleptobotFactory(c, r, this, false));
                
                
                
            } // end not empty
        } // end row loop
    } // end col loop
    
    return 0;
}

void StudentWorld::removeDeadGameObjects()
{
    for (list<Actor*>::iterator q = m_stage.begin(); q != m_stage.end(); q++)
    {
        if ((*q)->amIDead() == true)
        {
            delete (*q);
            m_stage.erase(q);
        }
    }
//    list<Actor*>::iterator q;
//    q = m_stage.begin();
//    
//    while(q != m_stage.end())
//    {
//        if ((*q)->amIDead() == true)
//        {
//            delete (*q);
//            q = m_stage.erase(q);
//        }
//    }
}

void StudentWorld::endLevel()
{
    m_endLevel = true;
}

void StudentWorld::diagnostics()
{
    cout << "Player score: " << getScore() << endl;
    cout << "Player lives: " << getLives() << endl;
    cout << "Player health: " << getPlayer()->getHealth() << endl;
    cout << "Player ammo: " << getPlayer()->getAmmo() << endl;
    cout << "---------" << endl;
}

void StudentWorld::addActor(Actor* act)
{
    m_stage.push_back(act);
}



////////////////////////////////
//         THE ARSENAL        //
////////////////////////////////

//unsigned int getLevel() const;
//unsigned int getLives() const;
//void decLives();
//void incLives();
//unsigned int getScore() const;
//void increaseScore(unsigned int howMuch);
//void setGameStatText(string text);
//bool getKey(int& value);
//void playSound(int soundID);



