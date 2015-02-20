#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

	virtual int init() // necessary
	{
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
    // this is basically the 'tick' method
	{
		  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times 
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp() // necessary
	{
	}

private:
};


//unsigned int getLevel() const;
//unsigned int getLives() const;
//void decLives();
//void incLives();
//unsigned int getScore() const;
//void increaseScore(unsigned int howMuch);
//void setGameStatText(string text);
//bool getKey(int& value);
//void playSound(int soundID);



#endif // STUDENTWORLD_H_
