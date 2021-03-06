#include "StudentWorld.h"
#include "Level.h"
#include <string>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir), assDir(assetDir)
{
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::init()
{
    levelLoader();
    // getContentsOf(col, row); 

    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() // this is basically the 'tick' method
{
    // update game status
    // ask everyone to do something
    // remove dead actors
    
    for (vector<Actor*>::iterator q = m_stage.begin(); q != m_stage.end(); q++) // all actors loop
    {
        if (!(*q)->amIDead()) // it's a pointer to a pointer to an actor
        {
            (*q)->doSomething();
            
            if (m_player->amIDead())
                return GWSTATUS_PLAYER_DIED;
            
        }
    
    } // end all actors loop
    
    if (m_player->amIDead())
        return GWSTATUS_PLAYER_DIED;
    
//    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    
}

void updateDisplayText() {
    
    
    //setGameStatText(perfString);
    
}

int StudentWorld::levelLoader()
{
    // LOAD UP YER LEVEL
    std::string curL;
    curL = "level03.dat";
    
    Level lev(assDir);
    Level::LoadResult result = lev.loadLevel(curL);
    
    if (result == Level::load_fail_file_not_found ||
        result == Level::load_fail_bad_format)
        return -1; // something bad happened!
    
    
    // FILL UP YER VECTOR OF ACTORS
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
                if (atHand == Level::wall)
                    m_stage.push_back(new Wall(c, r, this));
                
            } // end not empty
        } // end row loop
    } // end col loop
    
    return 0;
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



















////////////////////////////////
//          LALALAND          //
////////////////////////////////



//int StudentWorld::move() {

//    // Update the Game Status Line
//    updateDisplayText(); // update the score/lives/level text at screen top


//    // The term "actors" refers to all robots, the Player, Goodies, // Boulders, Jewels, Holes, Bullets, the Exit, etc.
//    // Give each actor a chance to do something
//    for each of the actors in the game world {
//        if (actor[i] is still active/alive) {
//            // ask each actor to do something (e.g. move)
//            16
//            actor[i]->doSomething();
//            if (thePlayerDiedDuringThisTick()) return GWSTATUS_PLAYER_DIED;
//            if (thePlayerCompletedTheCurrentLevel()) {
//                increaseScoreAppropriately(); return GWSTATUS_FINISHED_LEVEL;
//            } }
//    }
//    removeDeadGameObjects(); // delete dead game objects
//    // Reduce the current bonus for the Level by one
//    reduceLevelBonusByOne();
//    // If the player has collected all of the Jewels on the level, then we
//    // must expose the Exit so the player can advance to the next level
//    if (thePlayerHasCollectedAllOfTheJewelsOnTheLevel()) exposeTheExitInTheMaze(); // make the exit Active
//    // return the proper result
//    if (thePlayerDiedDuringThisTick()) return GWSTATUS_PLAYER_DIED;
//    if (thePlayerCompletedTheCurrentLevel()) {
//        // Remove newly-dead actors after each tick
//        increaseScoreAppropriately(); return GWSTATUS_FINISHED_LEVEL;
//    }
//    // continue playing the current level return GWSTATUS_CONTINUE_GAME;
//}





