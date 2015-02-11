//
//  main.cpp
//  homework3
//
//  Created by Grace Phillips on 2/6/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include <iostream>
#include <string>
#include "character.cpp"

class Character;
void strike(const Character* cp);

using namespace std;



int main()
{
    Character* characters[4];
    characters[0] = new Dwarf("Gimlet");
    // Elves have a name and initial number of arrows in their quiver
    characters[1] = new Elf("Legolam", 10);
    characters[2] = new Boggie("Frito");
    characters[3] = new Boggie("Spam");

    
    cout << "The characters strike!" << endl;
    for (int k = 0; k < 4; k++)
        strike(characters[k]);
    
    // Clean up the characters before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete characters[k];
}