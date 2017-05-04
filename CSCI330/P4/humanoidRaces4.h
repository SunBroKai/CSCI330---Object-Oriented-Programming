//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//humanoidRaces.h
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.
#ifndef HUMANOIDRACES_DOT_H
#define HUMANOIDRACES_DOT_H

#include "humanoid4.h"

using namespace std;
using namespace GameSpace;

//************************************** Human **********************************
class Human: public Humanoid{
	public:
		Human(string newName, VocRules::VocType newVoc = HUMAN_VOC);
		//Parameterized constructor.

        Human(const Human & h);
        //Copy constructor.
        
        virtual Human * Clone()const;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.

        virtual void Write(ostream& out)const;
        //Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.

        virtual std::vector<std::string> EquipInitialList()const;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

		std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

	private:
		static const VocRules::VocType HUMAN_VOC;
        //Default vocation for humans.
        static const int HUMAN_ABILADJ[ABILITY_COUNT];
        //Ability adjustments based ability for humans.
        static const std::string RACE;
        //Creature's race.
        static const int HUMAN_EQUIP = 3;
        //Number of default equipment.
        static const std::string DEFAULT_EQUIP[VocRules::VOC_MAX][HUMAN_EQUIP];
        //Creature's initial equipment.

        Human();
        //Default constructor.
};

//************************************** Elf ************************************
class Elf: public Humanoid{
	public:
        Elf(string newName, VocRules::VocType newVoc = ELF_VOC);
		//Parameterized constructor.

        Elf(const Elf & e);
        //Copy constructor.
        
        virtual Elf * Clone()const;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.

        virtual void Write(ostream& out)const;
        //Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.

        virtual std::vector<std::string> EquipInitialList()const;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

		std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

	private:
		static const VocRules::VocType ELF_VOC;
        //Default vocation for elves.
        static const int ELF_ABILADJ[ABILITY_COUNT];
        //Ability adjustments based ability for elves.
        static const std::string RACE;
        //Creature's race.
        static const int ELF_EQUIP = 3;
        //Number of default equipment.
        static const std::string DEFAULT_EQUIP[VocRules::VOC_MAX][ELF_EQUIP];
        //Creature's initial equipment.

        Elf();
        //Default constructor.
};

//********************************** HalfElf ************************************
class HalfElf: public Humanoid{
	public:
		HalfElf(string newName, VocRules::VocType newVoc = HALFELF_VOC);
		//Parameterized constructor.

        HalfElf(const HalfElf & h);
        //Copy constructor.
        
        virtual HalfElf * Clone()const;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.

        virtual void Write(ostream& out)const;
        //Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.

        virtual std::vector<std::string> EquipInitialList()const;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

		std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

	private:
		static const VocRules::VocType HALFELF_VOC;
        //Default vocation for halfelves.
        static const int HALFELF_ABILADJ[ABILITY_COUNT];
        //Ability adjustments based ability for halfelves.
        static const std::string RACE;
        //Creature's race.
        static const int HALFELF_EQUIP = 3;
        //Number of default equipment.
        static const std::string DEFAULT_EQUIP[VocRules::VOC_MAX][HALFELF_EQUIP];
        //Creature's initial equipment.

        HalfElf();
        //Default constructor.
};

//********************************** Orc ****************************************
class Orc: public Humanoid{
	public:
		Orc(string newName, VocRules::VocType newVoc = ORC_VOC);
		//Parameterized constructor.

        Orc(const Orc & o);
        //Copy constructor.
        
        virtual Orc * Clone()const;
        //Creates a clone of the creature.
        //Pre: None
        //Post: Returns pointer to clone creature.

        virtual void Write(ostream& out)const;
        //Helper function that outputs the creature's properties.
        //Pre: None.
        //Post: Prints the creature's properties.

        virtual std::vector<std::string> EquipInitialList()const;
        //Returns the initial list of equipment.
        //Pre: none.
        //Post: Initial list of equipment is returned by name.

		std::string Race_Str()const;
        //Returns the race of the creature.
        //Pre: None.
        //Post: Returns the creature’s race.

	private:
		static const VocRules::VocType ORC_VOC;
        //Default vocation for orcs.
        static const int ORC_ABILADJ[ABILITY_COUNT];
        //Ability adjustments based ability for orcs.
        static const std::string RACE;
        //Creature's race.
        static const int ORC_EQUIP = 4;
        //Number of default equipment.
        static const std::string DEFAULT_EQUIP[VocRules::VOC_MAX][ORC_EQUIP];
        //Creature's initial equipment.

        Orc();
        //Default constructor.
};

#endif
