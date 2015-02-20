#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir)
{
}

int StudentWorld::init() // necessary
{
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
// this is basically the 'tick' method
{
		  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}



// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp




































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

