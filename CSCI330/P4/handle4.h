//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//handle.h Creature
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#ifndef HANDLE_DOT_H
#define HANDLE_DOT_H

#include "p4.h"

using namespace std;
using namespace GameSpace;

class Creature{
    public:
        enum RaceType{HUMAN,ELF,HALFELF,ORC,TROLL,OGRE};
        //Datatype that represents race.
        
        Creature(string name, RaceType race = HUMAN, VocRules::VocType voc = VocRules::NNE);
        //Parameterized constructor.
        
        Creature(const Creature & c);
        //Copy constructor.
        
        Creature(CreatureClass * ptr);
        //Parameterized constructor.
        
        ~Creature();
        //Destructor.
        
        string Race_Str() const;
        //Returns the creatures race.
        //Pre: None.
        //Post: The creatures race string is returned.
        
        int Race() const;
        //Returns the creatures race.
        //Pre: None
        //Post: Returns the integer corresponding to the race.
        
        bool IsHumanoid() const;
        //Determines if the creature is humanoid.
        //Pre: None.
        //Post: Returns true if creature is humanoid.
        
        bool IsMonster() const;
        //Determines if the creature is a monster.
        //Pre: None.
        //Post: Returns true if creature is a monster.
        
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

        int HP()const;
        //Returns the hitpoints of the creature.
        //Pre: None.
        //Post: Returns the creature’s HP.

        int Ability(CreatureClass::AbilityType ability)const;
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

        int AbilityMod(CreatureClass::AbilityType ability)const;
        //Determines the ability modifier based on the ability parameter.
        //Pre: ability must be a valid AbilityType.
        //Post: Returns the ability modifier.

        std::string Weapon()const;
        //Returns the weapon of the creature.
        //Pre: None.
        //Post: Returns the creature’s weapon.

        std::string Armor()const;
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

        std::vector<std::string> EquipInitialList();
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

        EquipClass::EquipClass * FindEquipment(EquipClass * equipment);
        //Equipts the creature with the equipment passed in.
        //Pre: None.
        //Post: weapon or armor is replaced with equipment passed in and returns old equipment.

        EquipClass::EquipClass * LoseEquipment();
        //Equipment is lost.
        //Pre: None.
        //Post: Returns weapon if weapon is present, armor if weapon is not present, NULL if neither is present.

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

        int AttackRoll()const;
        //Returns attack roll if creature is active.
        //Pre: None.
        //Post: Returns attack role if creature is active, otherwise 0.

        int SavingThrow(SavingThrowType s)const;
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

        long XP()const;
        //Returns the experience of the creature.
        //Pre: None.
        //Post: Returns the creature’s XP.

        long GP()const;
        //Returns the gold points of the creature.
        //Pre: None.
        //Post: Returns the creature’s GP.

        std::vector<std::string> Pack()const;
        //Returns the creature's pack.
        //Pre: None.
        //Post: The contents of the pack is returned.

        std::vector<std::string> EquipInventory()const;
        //Returns the creature's equipment.
        //Pre: None.
        //Post: Returns the creature's pack, weapon, and armor.

        long UpdateGP(int value);
        //Updates the gold points of the creature.
        //Pre: value must not make the creature's GP negative.
        //Post: GP is modified and returned.

        long UpdateXP(int value);
        //Updates the experience points of the creature.
        //Pre: value cannot be negative.
        //Post: XP is modified and returned.

        bool ChangeEquipment(string equipName);
        //Changes equipment worn/carried with equipment in pack if present.
        //Pre: None.
        //Post: equipment being worn is replaced and put into the pack.

        EquipClass::EquipClass * BuyEquipment(EquipClass * equipment);
        //Buys the equipment passed in if the creature has enough gp.
        //Pre: None.
        //Post: equipment is equipped and the equipment replaced is put into the pack.

        EquipClass::EquipClass * SellEquipment(string equip);
        //Sells the equipment passed in if present.
        //Pre: None.
        //Post: equipment is sold and the cost is added to gp.

        Creature & operator=(const Creature & c);
        //Overloaded assignment operator.

        bool operator==(const Creature & c)const;
        //Compares two creatures to see if they are equal.
        //Pre: None
        //Post: Returns true if the creatures are identical, false otherwise.

        bool operator!=(const Creature & c)const;
        //Compares two creatures to see if they are different.
        //Pre: None
        //Post: Returns true if the creatures are not identical, true otherwise.

        bool operator<(const Creature & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is less than parameter value, otherwise false.

        bool operator<=(const Creature & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is less or equal to parameter value, otherwise false.

        bool operator>(const Creature & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is greater than parameter value, otherwise false.

        bool operator>=(const Creature & c)const;
        //Compares creatures by non-case sensitive names.
        //Pre: None
        //Post: Returns true if name value is greater or equal to parameter value, otherwise false.

    private:
        static const int RACE_COUNT = 6;
        //Number of races.
        static const string RACE_STR[RACE_COUNT];
        //Race strings.

        CreatureClass * creature;
        //Instance of a  creature.

        Creature();
        //Default constructor
        
        void CopyIntoMe(const Creature & c);
        //Copies other creature into this.
        //Pre: None.
        //Post: this matches other creature.
};

std::ostream& operator<<(ostream& out, const Creature & c);
//Outputs the contents of the creature.
//Pre: None.
//Post: A statement is outputted displaying the creatures characteristics.


#endif
