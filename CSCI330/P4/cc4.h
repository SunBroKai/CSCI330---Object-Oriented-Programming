//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//cc4.h CreatureClass
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#ifndef CREATURE_DOT_H
#define CREATURE_DOT_H

#include <iostream>
#include <cstring>
#include <vector>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "equip.h"
#include "wpn.h"
#include "armor.h"

using namespace std;
using namespace GameSpace;

class CreatureClass{
    public:
        enum AbilityType{DEX,CON,INT,CHA,STR,WIS};
        //Data type representing abilities.
        
        static const int ABILITY_COUNT = 6;
        //The number of abilities a creature has.
        static const int STAT_COUNT = 9;
        //The number of stats a creature has.

        virtual ~CreatureClass();
        //Destructor
        
        virtual CreatureClass * Clone()const = 0;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.
        
        virtual void Write(ostream& out)const;
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

        int HP()const;
        //Returns the hitpoints of the creature.
        //Pre: None.
        //Post: Returns the creature’s HP.

        int Ability(AbilityType ability)const;
        //Returns the creature’s specific ability value.
        //Pre: None.
        //Post: Returns the creature’s specific ability value.

        std::vector<int> Abilities();
        //Returns the abilities of the creature.
        //Pre: None.
        //Post: Returns the creature’s abilities.

        bool Active()const;
        //Determines whether creature is active.
        //Pre: None.
        //Post: Returns true if creature is not dead, dying, or diabled, false otherwise.

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

        std:: string Weapon()const;
        //Returns the weapon of the creature.
        //Pre: None.
        //Post: Returns the creature’s weapon.

        std:: string Armor()const;
        //Returns the armor of the creature.
        //Pre: None.
        //Post: Returns the creature’s armor.

        int SkillCheck(std::string skill);
        //Returns the skill check.
        //Pre: Creature must be alive.
        //Post: Returns the creature’s skill check if skill is present, otherwise returns 0.

        bool HasWeapon()const;
        //Determines whether or not the creature has a weapon.
        //Pre: None.
        //Post: Returns true if the creature has a weapon, false otherwise.

        bool HasArmor()const;
        //Determines whether or not the creature has armor.
        //Pre: None.
        //Post: Returns true if the creature has armor, false otherwise.

        std::vector<std::string> Skills()const;
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

        virtual std::vector<std::string> EquipInitialList()const = 0;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

        virtual EquipClass::EquipClass * FindEquipment(EquipClass * equipment);
        //Equipts the creature with the equipment passed in.
        //Pre: None.
        //Post: weapon or armor is replaced with equipment passed in and returns old equipment.

        EquipClass::EquipClass * LoseEquipment();
        //Equipment is lost.
        //Pre: None.
        //Post: Returns weapon if weapon is present, armor if weapon is not present, NULL if neither is present.

        virtual WeaponClass::WeaponClass * FindWeapon(WeaponClass * wpn);
        //Changes the creature's weapon and returns the replaced weapon.
        //Pre: Creature’s weapon must not be NULL.
        //Post: Changes creature’s weapon to match parameter and returns replaced weapon.

        WeaponClass::WeaponClass * LoseWeapon();
        //Equipped weapon is lost.
        //Pre: Creature’s weapon must not be NULL.
        //Post: Returns lost weapon, returns NULL if none was lost.

        virtual ArmorClass::ArmorClass * FindArmor(ArmorClass * amr);
        //Changes the creature's armor and returns the replaced armor.
        //Pre: Creature’s armor must not be NULL.
        //Post: Changes creature’s armor to match parameter and returns replaced armor.

        ArmorClass::ArmorClass * LoseArmor();
        //Equipped armor is lost.
        //Pre: Creature’s armor must not be NULL.
        //Post: Returns lost armor, returns NULL if none was lost.

        bool AddSkill(string skill);
        //Adds skill to creature’s list of skills.
        //Pre: Creature must be alive.
        //Post: Skill is added to skill list if not present and returns true, otherwise returns false.

        void Amnesia();
        //Empties all skills from creature’s skill list.
        //Pre: None
        //Post: All skills are removed from creature’s skill list.

        int InitiativeCheck()const;
        //Returns initiative ckeck if creature is active.
        //Pre: None.
        //Post: Returns initiative ckeck if creature is active, otherwise 0.

        virtual int AttackRoll()const = 0;
        //Returns attack roll if creature is active.
        //Pre: None.
        //Post: Returns attack role if creature is active, otherwise 0.

        virtual int SavingThrow(SavingThrowType s)const = 0;
        //Returns saving throw if creature is active.
        //Pre: None.
        //Post: Returns saving throw if creature is active, otherwise 0.

        int Defense()const;
        //Returns defense roll if creature is active.
        //Pre: None.
        //Post: Returns defense roll if creature is active, otherwise 0.

        int Damage()const;
        //Returns damage roll if creature is active.
        //Pre: None.
        //Post: Returns damage roll if creature is active, otherwise 0.

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

    private:
        enum StatType{EHP=6,ROW,COL};
        //Data type representing non-ability stats.

        struct SkillRec{
            string skill;
            AbilityType abil;
        };

        static std::vector<SkillRec> SkillsTable;
        //Table of skills.
        static const std::string DEFAULT_NAME;
        //Default name assigned if input is not valid.
        static const int DYING_HP;
        //The maximum HP at which the creature is dying.
        static const int DEAD_HP;
        //The maximum HP at which the creature is dead.
        static const int DISABLED_NUM;
        //The maximum ability value at which the creature is disabled.
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

        char * name;
        //The creature's name.
        long statScores[STAT_COUNT];
        //The creature's stat values.
        WeaponClass * weapon;
        //The creature's weapon.
        ArmorClass * armor;
        //The creature's armor.
        std::vector<std::string> skills;
        //The creature's skills. 

        static void LoadSkillTable();
        //Loads the table of skills.
        //Pre: None.
        //Post: SkillsTable is loaded from skills.in.
        
        void SetEquip();
        //Helper function that sets the equipment of the creature.
        //Pre: None.
        //Post: Changes the creatures equipment to the default.
        
    protected:
        CreatureClass();
        //Constructor used to create default creature.

        CreatureClass(std::string newName);
        //Constructor used when a string, RaceType, and VocType are provided.

        CreatureClass(const CreatureClass & c);
        //Copy constructor.

        void SetName(std::string newName);
        //Helper function that sets the name of the creature.
        //Pre: None.
        //Post: Changes the name to match the parameter.

        void SetStats(int abil[]);
        //Sets the abilities, row, and column.
        //Pre: None.
        //Post: Abilities, row, and column are initialized.

        void SetHP(int hpNum);
        //Sets the initial hitpoints of the creature.
        //Pre: None.
        //Post: Hitpoints are initialized.

        void SetSkills(const std::string newSkills[], int size);
        //Sets the initial skills for the creature.
        //Pre: None.
        //Post: Initial skills are added to the creature.

        CreatureClass & operator=(const CreatureClass & c);
        //Overloaded assignment operator.
};

std::ostream& operator<<(ostream& out, const CreatureClass & c);
//Outputs the contents of the creature.
//Pre: None.
//Post: A statement is outputted displaying the creatures characteristics.

#endif
