//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//humanoid.h
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.
#ifndef HUMANOID_DOT_H
#define HUMANOID_DOT_H

#include "cc4.h"

using namespace std;
using namespace GameSpace;

class Humanoid: public CreatureClass{
	public:      
	        virtual ~Humanoid();
            //Destructor
    
            virtual Humanoid * Clone()const = 0;
            //Creates a clone of the creature.
            //Pre: None
            //Post: Returns pointer to clone creature.
            
            virtual void Write(ostream& out)const;
            //Helper function that outputs the creature's properties.
            //Pre: None.
            //Post: Prints the creature's properties.

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

            virtual std::vector<std::string> EquipInitialList()const = 0;
            //Returns the initial list of equipment.
            //Pre: none.
            //Post: Initial list of equipment is returned by name.

            virtual EquipClass::EquipClass * FindEquipment(EquipClass * equipment);
            //Equipts the creature with the equipment passed in.
            //Pre: None.
            //Post: weapon or armor is replaced with equipment passed in and puts old equipment into the pack.

            virtual WeaponClass::WeaponClass * FindWeapon(WeaponClass * wpn);
            //Changes the creature's weapon and returns the replaced weapon.
            //Pre: Creature’s weapon must not be NULL.
            //Post: Changes creature’s weapon to match parameter and returns replaced weapon.

            virtual ArmorClass::ArmorClass * FindArmor(ArmorClass * amr);
            //Changes the creature's armor and returns the replaced armor.
            //Pre: Creature’s armor must not be NULL.
            //Post: Changes creature’s armor to match parameter and returns replaced armor.

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

            virtual int AttackRoll()const;
            //Returns attack roll if creature is active.
            //Pre: None.
            //Post: Returns attack role if creature is active, otherwise 0.

            virtual int SavingThrow(SavingThrowType s)const;
            //Returns saving throw if creature is active.
            //Pre: None.
            //Post: Returns saving throw if creature is active, otherwise 0.

            Humanoid& operator=(const Humanoid & h);
            //Overloaded assignment operator.
                
	private:
            enum HstatType{EXP,EGP,LEVEL};
            //Data type that represents the humanoid stats.

        	static const int BASE_LEVEL;
            //The default value given to level.
            static const int MIN_GP;
            //The minimum amount of GP.
            static const int MIN_XP;
            //The minimum amount of XP.
            static const int BASE_HP;
            //The base amount of hitpoints.
            static const int SKILL_COUNT = 3;
        	//The number of default skill.
            static const int HSTAT_COUNT = 3;
            //The number of humanoid stats.
        	static const std::string DEFAULT_SKILLS[VocRules::VOC_MAX][SKILL_COUNT];
            //Default skills.

        	VocRules::VocType voc;
            //The creature's vocation.
            long hStats[HSTAT_COUNT];
            //The creature's humanoid stats.
            std::vector<EquipClass*> pack;
            //The creature's inventory.

            void SetVoc(VocRules::VocType newVoc, VocRules::VocType defVoc);
            //Helper function that sets the vocation of the creature.
            //Pre: None.
            //Post: Changes the voc to match the parameter.

            void SetStats(const int abilAdj[]);
            //Sets the abilities, row, and column.
            //Pre: None.
            //Post: Abilities, row, and column are initialized.

            void SetSkills();
            //Sets the initial skills for the creature.
            //Pre: None.
            //Post: Initial skills are added to the creature.

            int AttackBonus()const;
            //Calculates the creatures attack bonus.
            //Pre: None.
            //Post: attack bonus is returned.

        protected:
            Humanoid();
            //Default constructor.

            Humanoid(string newName, VocRules::VocType newVoc, VocRules::VocType defVoc, const int abilAdj[]);
            //Parameterized constructor.

            Humanoid(const Humanoid & h);
            //Copy constructor.

            void CopyHumanoid(const Humanoid & h);
            //Helper function for copy constructor.
            //Pre: None.
            //Post: Copies humanoid traits to other creature.
};

#endif
