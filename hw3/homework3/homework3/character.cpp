//
//  character.cpp
//  homework3
//

//minor change


//#include <iostream>
//#include <string>
//
//
//using namespace std;

// Your declarations and implementations would go here

//////////////////////
///  DECLARATIONS  ///
//////////////////////
class Character {
public:
    virtual ~Character() {} //wut
    virtual string name() const;
    virtual void printWeapon() const = 0;
    virtual string attackAction() const;
    Character(string name);
private:
    string m_name;
protected:
    
};


class Dwarf : public Character {
public:
    ~Dwarf() { cout << "Destroying " << this->name() << " the dwarf" << endl; }
    Dwarf(string name);
    virtual void printWeapon() const;
private:
    string m_name;
};


class Elf : public Character {
public:
    ~Elf() { cout << "Destroying " << this->name() << " the elf" << endl;}
    Elf(string name, int nArrows);
    virtual void printWeapon() const;
private:
    int m_nArrows;
};

class Boggie : public Character {
public:
    ~Boggie() { cout << "Destroying " << this->name() << " the boggie" << endl;}
    Boggie(string name);
    virtual void printWeapon() const;
    virtual string attackAction() const;
private:
    string m_name;
};

void strike(const Character* cp);


/////////////////////
// IMPLEMENTATION  //
/////////////////////

string rush = "rushes toward the enemy";
string cower = "whimpers";

// CHARACTER
Character::Character(string name)
{
    m_name = name;
}

string Character::name() const
{
    return m_name;
}
string Character::attackAction() const
{
      return rush;
}


// DWARF
Dwarf::Dwarf(string name)
: Character(name)
{
}
void Dwarf::printWeapon() const
{
    cout << "an axe";
}

// ELF
Elf::Elf(string name, int nArrows)
: Character(name), m_nArrows(nArrows)
{
}
void Elf::printWeapon() const
{
    cout << "a bow and quiver of " << m_nArrows << " arrows";
}


// BOGGIE
Boggie::Boggie(string name)
: Character(name)
{
}
void Boggie::printWeapon() const
{
    cout << "a short sword";
}
string Boggie::attackAction() const
{
    return cower;
}


////// Include nothing past this point ---------------------------------------------------------------------
//void strike(const Character* cp)
//{
//    cout << cp->name() << ", wielding ";
//    cp->printWeapon();
//    cout << ", ";
//    std::cout << cp->attackAction();
//    cout << "." << endl;
//}



//The characters strike!
//Gimlet, wielding an axe, rushes toward the enemy.
//Legolam, wielding a bow and quiver of 10 arrows, rushes toward the enemy.
//Frito, wielding a short sword, whimpers.
//Spam, wielding a short sword, whimpers.
//Cleaning up
//Destroying Gimlet the dwarf
//Destroying Legolam the elf
//Destroying Frito the boggie
//Destroying Spam the boggie