/*Kai Jungbluth*/
#ifndef CREATURE_DOT_H
#define CREATURE_DOT_H

#include <iostream>
#include <cstring>
#include "cc1.h"
#include "gamespace.h"
#include "voc.h"
#include "dice.h"

using namespace std;
using namespace GameSpace;

class CreatureClass{
    public:
        enum AbilityType{DEX,CON,INT,CHA,STR,WIS};
        //Data type representing abilities.
        enum RaceType{HUMAN,ELF,HALFELF,ORC,TROLL,OGRE};
        //Data type representing races.
        enum StatType{EHP=6,EXP,EGP,LEVEL,ROW,COL};
        //Data type representing non-ability stats.
        
        static const int ABILITY_COUNT = 6;
        //The number of abilities a creature has.
        static const int STAT_COUNT = 12;
        //The number of stats a creature has.
        static const int RACE_COUNT = 6;
        //The total number of races.
        static const int HUMAN_COUNT = 4;
        //The number of humanoid creatures.
        static const int MONSTER_COUNT = 2;
        //The number of monster creatures.
        
        CreatureClass();
        //Constructor used to create default creature.
        CreatureClass(std::string newName);
        //Constructor used when a string is provided.
        CreatureClass(std::string newName, RaceType newRace);
        //Constructor used when a string and RaceType are provided.
        CreatureClass(std::string newName, RaceType newRace, VocRules::VocType newVoc);
        //Constructor used when a string, RaceType, and VocType are provided.

        ~CreatureClass();
        //Destructor
        
        void Write(ostream& out)const;
        //Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.
        std::string Name()const;
        //Returns the name of the creature.
        //Pre: None.
        //Post: Returns the creature’s name as a string.
        int Row()const;
        //Returns the row that the creature is located on.
        //Pre: None.
        //Post: Returns the creature’s row as an integer.
        int Col()const;
        //Returns the column that the creature is located on.
        //Pre: None.
        //Post: Returns the creature’s col as an integer.
        int Race()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race as an integer.
        std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race as a string.
        int Voc()const;
        //Returns the vocation of the creature.
        //Pre: None.
        //Post: Returns the creature’s voc as an integer.
        std::string Voc_Str()const;
        //Returns the vocation of the creature.
        //Pre: None.
        //Post: Returns the creature’s voc as a string.
        int Level()const;
        //Returns the level of the creature.
        //Pre: None.
        //Post: Returns the creature’s level as an integer.
        int HP()const;
        //Returns the hitpoints of the creature.
        //Pre: None.
        //Post: Returns the creature’s HP as an integer.
        long XP()const;
        //Returns the experience of the creature.
        //Pre: None.
        //Post: Returns the creature’s XP as an integer.
        long GP()const;
        //Returns the gold points of the creature.
        //Pre: None.
        //Post: Returns the creature’s GP as an integer.
        int Ability(AbilityType ability)const;
        //Returns the creature’s specific ability value.
        //Pre: None.
        //Post: Returns the creature’s specific ability value as an integer.
        bool Humanoid()const;
        //Determines whether or not the creature is humanoid.
        //Pre: None.
        //Post: Returns true if the creature is humanoid, false otherwise.
        bool Monster()const;
        //Determines whether or not the creature is a monster.
        //Pre: None.
        //Post: Returns true if the creature is a monster, false otherwise.
        bool Dead()const;
        //Determines whether or not the creature is dead.
        //Pre: None.
        //Post: Returns true if the creature is dead, false otherwise.
        bool Dying()const;
        //Determines whether or not the creature is dying.
        //Pre: None.
        //Post: Returns true if the creature is dying, false otherwise.
        bool Disabled()const;
        //Determines whether or not the creature is disabled.
        //Pre: None.
        //Post: Returns true if the creature is disabled, false otherwise.
        int AbilityMod(AbilityType ability)const;
        //Determines the ability modifier based on the ability parameter.
        //Pre: ability must be a valid AbilityType.
        //Post: Returns the ability modifier as an integer.
        bool SetCell(int newRow, int newCol);
        //Updates the creature’s coordinates.
        //Pre: newRow and newCol must be greater than -1.
        //Post: Sets the creature’s row and column equal to the parameters and returns true if both are greater than or equal to -1.
        int UpdateHP(int modification);
        //Updates the hitpoints of the creature.
        //Pre: None.
        //Post: HP is modified and returned as an integer.
        long UpdateGP(int value);
        //Narrative: Updates the gold points of the creature.
        //Pre: value must not make the creature's GP negative.
        //Post: GP is modified and returned as an integer.
        long UpdateXP(int value);
        //Narrative: Updates the experience points of the creature.
        //Pre: value cannot be negative.
        //Post: XP is modified and returned as an integer.
        
        bool operator==(const CreatureClass & c)const;
        //Compares two creatures to see if they are equal.
        //Pre: None
        //Post: Returns true if the creatures are identical, false otherwise.
        bool operator!=(const CreatureClass & c)const;
        //Narrative: Compares two creatures to see if they are different.
        //Pre: None
        //Post: Returns true if the creatures are not identical, true otherwise.
        
    private:
        static const std::string DEFAULT_NAME;
        //Default name assigned if input is not valid.
        static const int DYING_HP;
        //The maximum HP at which the creature is dying.
        static const int DEAD_HP;
        //The maximum HP at which the creature is dead.
        static const int DISABLED_NUM;
        //The maximum ability value at which the creature is disabled.
        static const int BASE_HP;
        //The default value given to hitpoints.
        static const int BASE_LEVEL;
        //The default value given to level.
        static const int CON_DEAD;
        //The maximum CON at which the creature is dead.
        static const int MIN_ROW;
        //The minimum row at which the creature can reside.
        static const int MIN_COL;
        //The minimum column at which the creature can reside.
        static const int MIN_NAME;
        //The minimum size of the name.
        static const int MIN_GP;
        //The minimum amount of GP.
        static const int MIN_XP;
        //The minimum amount of XP.
        static const int STAT_DEFAULT;
        //The default stat value.
        static const int MONSTER_OFFSET;
        //The offset used in arrays for monster default abilities.
        static const RaceType DEFAULT_RACE;
        //Default race assigned if input is not valid.
        static const VocRules::VocType DEFAULT_VOC[RACE_COUNT];
        //Default vocation based on race.
        static const int ABILITY_ADJ[HUMAN_COUNT][ABILITY_COUNT];
        //Ability adjustments based on race and ability.
        static const int DEFAULT_ABILITY[MONSTER_COUNT][ABILITY_COUNT];
        //Default abilities for monsters.
        
        std::string name;
        //The creature's name.
        RaceType race;
        //The creature's race.
        VocRules::VocType voc;
        //The creature's vocation.
        long statScores[STAT_COUNT];
        //The creature's stat values.
        
        
        void SetName(std::string newName);
        //Helper function that sets the name of the creature.
        //Pre: None.
        //Post: Changes the name to match the parameter.
        void SetRace(RaceType newRace);
        //Helper function that sets the race of the creature.
        //Pre: None.
        //Post: Changes the race to match the parameter.
        void SetVoc(VocRules::VocType newVoc);
        //Helper function that sets the vocation of the creature.
        //Pre: None.
        //Post: Changes the voc to match the parameter.
        void SetStats();
        //Helper function that sets the stats of the creature.
        //Pre: None.
        //Post: Calculates the stat values.
};

std::ostream& operator<<(ostream& out, const CreatureClass & c);
//Outputs the contents of the creature.
//Pre: None.
//Post: A statement is outputted displaying the creatures characteristics.

#endif
