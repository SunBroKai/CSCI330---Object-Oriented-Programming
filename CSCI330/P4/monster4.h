//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//monster.h
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.
#ifndef MONSTER_DOT_H
#define MONSTER_DOT_H

#include "cc4.h"

using namespace std;
using namespace GameSpace;

//************************************** Monster **********************************
class Monster: public CreatureClass{
	public:
        virtual Monster * Clone()const = 0;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.
        
        virtual std::vector<std::string> EquipInitialList()const = 0;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

        virtual EquipClass::EquipClass * FindEquipment(EquipClass * equipment);
        //Equipts the creature with the equipment passed in.
        //Pre: None.
        //Post: weapon or armor is replaced with equipment passed in and returns old equipment.

	virtual void Write(ostream& out)const;
	//Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.
        
	private:
        int AttackBonus(const int baseAtt[])const;
        //Calculates the creatures attack bonus.
        //Pre: None.
        //Post: attack bonus is returned.

	protected:
        Monster();
        //Default constructor.

        Monster(string newName);
        //Parameterized constructor.

        Monster(const Monster & m);
        //Copy constructor.

        void SetStats(const int defAbil[], int hpNum);
        //Sets the abilities, row, and column.
        //Pre: None.
        //Post: Abilities, row, and column are initialized.

		int AttackRoll(const int baseAtt[])const;
        //Returns attack roll if creature is active.
        //Pre: None.
        //Post: Returns attack role if creature is active, otherwise 0.

        int SavingThrow(SavingThrowType s, const int savingThrows[])const;
        //Returns saving throw if creature is active.
        //Pre: None.
        //Post: Returns saving throw if creature is active, otherwise 0.
};

//*************************************** Troll ***********************************
class Troll: public Monster{
	public:
		Troll(string newName);
		//Parameterized constructor.

		Troll(const Troll & t);
		//Copy constructor.
        
        virtual Troll * Clone()const;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.

		std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

        virtual std::vector<std::string> EquipInitialList()const;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

        virtual int AttackRoll()const;
        //Returns attack roll if creature is active.
        //Pre: None.
        //Post: Returns attack role if creature is active, otherwise 0.

        virtual int SavingThrow(SavingThrowType s)const;
        //Returns saving throw if creature is active.
        //Pre: None.
        //Post: Returns saving throw if creature is active, otherwise 0.

        virtual void Write(ostream& out)const;
		//Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.
	private:
		static const int TROLL_SKILLS = 2;
		//The number of default skills.
		static const int TROLL_ABILITY[ABILITY_COUNT];
        //Default abilities for trolls.
		static const std::string DEFAULT_SKILLS[TROLL_SKILLS];
        //Default skills for each vocation.
        static const std::string RACE;
        //The creature's race.
        static const int BASE_ATT[2];
        //The creature's base attack bonus.
        static const int SAVING_THROW[3];
        //The creature's saving throws.
        static const std::string INIT_EQUIP[2];
        //The creature's initial equipment.

        Troll();
		//Default constructor.
};

//*************************************** Ogre ************************************
class Ogre: public Monster{
	public:
		Ogre(string newName);
		//Parameterized constructor.

		Ogre(const Ogre & o);
		//Copy constructor.
        
        virtual Ogre * Clone()const;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.

		std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

        virtual std::vector<std::string> EquipInitialList()const;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

        virtual int AttackRoll()const;
        //Returns attack roll if creature is active.
        //Pre: None.
        //Post: Returns attack role if creature is active, otherwise 0.

        virtual int SavingThrow(SavingThrowType s)const;
        //Returns saving throw if creature is active.
        //Pre: None.
        //Post: Returns saving throw if creature is active, otherwise 0.

        virtual void Write(ostream& out)const;
		//Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.

	private:
		static const int OGRE_SKILLS = 3;
		//The number of default skill.
		static const int OGRE_ABILITY[ABILITY_COUNT];
                //Default abilities for ogre.
		static const std::string DEFAULT_SKILLS[OGRE_SKILLS];
        //Default skills for each vocation.
        static const std::string RACE;
        //The creature's race.
        static const int BASE_ATT[2];
        //The creature's base attack bonus.
        static const int SAVING_THROW[3];
        //The creature's saving throws.
        static const std::string INIT_EQUIP[2];
        //The creature's initial equipment.

        Ogre();
		//Default contructor.
};

#endif
