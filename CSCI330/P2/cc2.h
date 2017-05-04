//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 2
//cc2.cpp CreatureClass
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#ifndef CREATURE_DOT_H
#define CREATURE_DOT_H

#include <iostream>
#include <cstring>
#include <vector>
#include "cc2.h"
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "wpn2.h"
#include "armor2.h"

using namespace std;
using namespace GameSpace;

class CreatureClass{
    public:
        enum AbilityType{DEX,CON,INT,CHA,STR,WIS};
        //Data type representing abilities.
        enum RaceType{HUMAN,ELF,HALFELF,ORC,TROLL,OGRE};
        //Data type representing races.
        
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
        static const int DSKILL_COUNT = 3;
        //The number of default skills.
        
        CreatureClass(std::string newName = DEFAULT_NAME, RaceType newRace = DEFAULT_RACE, VocRules::VocType newVoc = VocRules::NNE);
        //Constructor used when a string, RaceType, and VocType are provided.

        CreatureClass(const CreatureClass & c);
        //Copy constructor.

        ~CreatureClass();
        //Destructor
        
        void Write(ostream& out)const;
        //Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.

        std::string Name()const;
        //Returns the name of the creature.
        //Pre: None.
        //Post: Returns the creature’s name.

        int Row()const;
        //Returns the row that the creature is located on.
        //Pre: None.
        //Post: Returns the creature’s row.

        int Col()const;
        //Returns the column that the creature is located on.
        //Pre: None.
        //Post: Returns the creature’s col.

        int Race()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

        std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

        int Voc()const;
        //Returns the vocation of the creature.
        //Pre: None.
        //Post: Returns the creature’s voc.

        std::string Voc_Str()const;
        //Returns the vocation of the creature.
        //Pre: None.
        //Post: Returns the creature’s voc.

        int Level()const;
        //Returns the level of the creature.
        //Pre: None.
        //Post: Returns the creature’s level.

        int HP()const;
        //Returns the hitpoints of the creature.
        //Pre: None.
        //Post: Returns the creature’s HP.

        long XP()const;
        //Returns the experience of the creature.
        //Pre: None.
        //Post: Returns the creature’s XP.

        long GP()const;
        //Returns the gold points of the creature.
        //Pre: None.
        //Post: Returns the creature’s GP.

        int Ability(AbilityType ability)const;
        //Returns the creature’s specific ability value.
        //Pre: None.
        //Post: Returns the creature’s specific ability value.

        std::vector<int> Abilities();
        //Returns the abilities of the creature.
        //Pre: None.
        //Post: Returns the creature’s abilities.

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
        //Post: Returns the ability modifier.

        std:: string Weapon();
        //Returns the weapon of the creature.
        //Pre: None.
        //Post: Returns the creature’s weapon.

        std:: string Armor();
        //Returns the armor of the creature.
        //Pre: None.
        //Post: Returns the creature’s armor.

        int SkillCheck(std::string skill);
        //Returns the skill check.
        //Pre: Creature must be alive.
        //Post: Returns the creature’s skill check if skill is present, otherwise returns 0.

        bool HasWeapon();
        //Determines whether or not the creature has a weapon.
        //Pre: None.
        //Post: Returns true if the creature has a weapon, false otherwise.

        bool HasArmor();
        //Determines whether or not the creature has armor.
        //Pre: None.
        //Post: Returns true if the creature has armor, false otherwise.

        std::vector<std::string> Skills();
        //Returns the skills of the creature.
        //Pre: None.
        //Post: Returns the creature’s skills.

        bool SetCell(int newRow, int newCol);
        //Updates the creature’s coordinates.
        //Pre: newRow and newCol must be greater than -1.
        //Post: Sets the creature’s row and column equal to the parameters and returns true if both are greater than or equal to -1.

        int UpdateHP(int modification);
        //Updates the hitpoints of the creature.
        //Pre: None.
        //Post: HP is modified and returned.

        long UpdateGP(int value);
        //Updates the gold points of the creature.
        //Pre: value must not make the creature's GP negative.
        //Post: GP is modified and returned.

        long UpdateXP(int value);
        //Updates the experience points of the creature.
        //Pre: value cannot be negative.
        //Post: XP is modified and returned.

        WeaponClass::WeaponClass * FindWeapon(WeaponClass * wpn);
        //Changes the creature's weapon and returns the replaced weapon.
        //Pre: Creature’s weapon must not be NULL.
        //Post: Changes creature’s weapon to match parameter and returns replaced weapon.

        WeaponClass::WeaponClass * LoseWeapon();
        //Equipped weapon is lost.
        //Pre: Creature’s weapon must not be NULL.
        //Post: Returns lost weapon, returns NULL if none was lost.

        ArmorClass::ArmorClass * FindArmor(ArmorClass * amr);
        //Changes the creature's armor and returns the replaced armor.
        //Pre: Creature’s armor must not be NULL.
        //Post: Changes creature’s armor to match parameter and returns replaced armor.

        ArmorClass::ArmorClass * LoseArmor();
        //Equipped armor is lost.
        //Pre: Creature’s armor must not be NULL.
        //Post: Returns lost armor, returns NULL if none was lost.

        bool AddSkill(string skill);
        //
        //
        //

        void Amnesia();
        //Empties all skills from creature’s skill list.
        //Pre: None
        //Post: All skills are removed from creature’s skill list.

        bool operator==(const CreatureClass & c)const;
        //Compares two creatures to see if they are equal.
        //Pre: None
        //Post: Returns true if the creatures are identical, false otherwise.

        bool operator!=(const CreatureClass & c)const;
        //Compares two creatures to see if they are different.
        //Pre: None
        //Post: Returns true if the creatures are not identical, true otherwise.

        bool operator<(const CreatureClass & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is less than parameter value, otherwise false.

        bool operator<=(const CreatureClass & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is less or equal to parameter value, otherwise false.

        bool operator>(const CreatureClass & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is greater than parameter value, otherwise false.

        bool operator>=(const CreatureClass & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is greater or equal to parameter value, otherwise false.

        CreatureClass & operator=(const CreatureClass & c);
        //Overloaded assignment operator.

    private:
        enum StatType{EHP=6,EXP,EGP,LEVEL,ROW,COL};
        //Data type representing non-ability stats.

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
        static const int MAX_NAME;
        //The maximum size of the name.
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
        static const std::string DEFAULT_SKILLS[VocRules::VOC_MAX][DSKILL_COUNT];
        //Default skills for each vocation.
        static const std::string MONSTER_SKILLS[MONSTER_COUNT][DSKILL_COUNT];

        char * name;
        //The creature's name.
        RaceType race;
        //The creature's race.
        VocRules::VocType voc;
        //The creature's vocation.
        long statScores[STAT_COUNT];
        //The creature's stat values.
        WeaponClass * weapon;
        //The creature's weapon.
        ArmorClass * armor;
        //The creature's armor.
        std::vector<std::string> skills;
        //The creature's skills.       
        
        
        CreatureClass();
        //Constructor used to create default creature.

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

        void SetEquip();
        //Helper function that sets the equipment of the creature.
        //Pre: None.
        //Post: Changes the creatures equipment to the default.

        void SetSkills();
        //Helper function that sets the skills of the creature.
        //Pre: None.
        //Post: Changes the skills to the default.

        std::vector<std::string> ReadFile(std::string fileName);
        //Creates a vector of strings from the ifstream.
        //Pre: None
        //Post: Returns a vector of strings from the ifstream.

        std::vector<AbilityType> ReadAbil(std::string fileName);
        //Creates a vector of AbilityTypes from the ifstream.
        //Pre: None
        //Post: Returns a vector of AbilityTypes from the ifstream.

        AbilityType StrToAbil(std::string abilityStr);
        //Turns a string into an AbilityType.
        //Pre: None.
        //Post: Returns the string as the corresponding AbilityType.
};

std::ostream& operator<<(ostream& out, const CreatureClass & c);
//Outputs the contents of the creature.
//Pre: None.
//Post: A statement is outputted displaying the creatures characteristics.

#endif
