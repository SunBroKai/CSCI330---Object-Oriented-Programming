//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 3
//humanoidRaces.cpp
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#include "humanoidRaces3.h"

using namespace std;
using namespace GameSpace;

//************************************** Human **********************************
const VocRules::VocType Human::HUMAN_VOC = VocRules::FTR;
const int Human::HUMAN_ABILADJ[ABILITY_COUNT] = {0,0,0,0,0,0};
const std::string Human::RACE = "HUMAN";
const std::string Human::DEFAULT_EQUIP[VocRules::VOC_MAX][HUMAN_EQUIP] = 	{{"","",""}, //NNE
																			{"Studded leather","Dagger","Short bow"}, //BBN
																			{"Large wooden shield","Crossbow","Mace"}, //CLR
																			{"Large wooden shield","Sword",""}, //FTR
																			{"Leather jacket","Rapier","Short bow"}, //ROG
																			{"Club","Dagger","Light crossbow"}}; //WIZ

Human::Human()
{
	
}

Human::Human(string newName, VocRules::VocType newVoc): Humanoid(newName,newVoc,HUMAN_VOC,HUMAN_ABILADJ)
{

}

Human::Human(const Human & h): Humanoid(h)
{

}

void Human::Write(ostream& out)const
{
    out << Race_Str() << "#";
    Humanoid::Write(out);

    return;
}

std::vector<std::string> Human::EquipInitialList()const
{
	std::vector<string> initEquip;

	for(int i = 0; i < HUMAN_EQUIP; i++){
		if(DEFAULT_EQUIP[Voc()][i] != ""){
			initEquip.push_back(DEFAULT_EQUIP[Voc()][i]);
		}
	}

	return initEquip;
}

std::string Human::Race_Str()const
{
	return RACE;
}

//************************************** Elf ************************************
const VocRules::VocType Elf::ELF_VOC = VocRules::WIZ;
const int Elf::ELF_ABILADJ[ABILITY_COUNT] = {2,-2,0,0,0,0};
const std::string Elf::RACE = "ELF";
const std::string Elf::DEFAULT_EQUIP[VocRules::VOC_MAX][ELF_EQUIP] = 	{{"","",""}, //NNE
																		{"Studded leather","Dagger","Short bow"}, //BBN
																		{"Large wooden shield","Long sword","Short bow"}, //CLR
																		{"Small wooden shield","Sword",""}, //FTR
																		{"Leather jacket","Rapier","Short bow"}, //ROG
																		{"Short bow","Quarter staff",""}}; //WIZ

Elf::Elf()
{
	
}

Elf::Elf(string newName, VocRules::VocType newVoc): Humanoid(newName,newVoc,ELF_VOC,ELF_ABILADJ)
{

}

Elf::Elf(const Elf & e): Humanoid(e)
{

}

void Elf::Write(ostream& out)const
{
    out << Race_Str() << "#";
    Humanoid::Write(out);

    return;
}

std::vector<std::string> Elf::EquipInitialList()const
{
	std::vector<string> initEquip;

	for(int i = 0; i < ELF_EQUIP; i++){
		if(DEFAULT_EQUIP[Voc()][i] != ""){
			initEquip.push_back(DEFAULT_EQUIP[Voc()][i]);
		}
	}

	return initEquip;
}

std::string Elf::Race_Str()const
{
	return RACE;
}

//************************************ Halfelf **********************************
const VocRules::VocType HalfElf::HALFELF_VOC = VocRules::ROG;
const int HalfElf::HALFELF_ABILADJ[ABILITY_COUNT] = {0,0,0,0,0,0};
const std::string HalfElf::RACE = "HALFELF";
const std::string HalfElf::DEFAULT_EQUIP[VocRules::VOC_MAX][HALFELF_EQUIP] = 	{{"","",""}, //NNE
																				{"Studded leather","Dagger","Short bow"}, //BBN
																				{"Large wooden shield","Long sword",""}, //CLR
																				{"Small wooden shield","Sword",""}, //FTR
																				{"Leather jacket","Rapier","Short bow"}, //ROG
																				{"Club","Light crossbow",""}}; //WIZ

HalfElf::HalfElf()
{
	
}

HalfElf::HalfElf(string newName, VocRules::VocType newVoc): Humanoid(newName,newVoc,HALFELF_VOC,HALFELF_ABILADJ)
{

}

HalfElf::HalfElf(const HalfElf & h): Humanoid(h)
{

}

void HalfElf::Write(ostream& out)const
{
    out << Race_Str() << "#";
    Humanoid::Write(out);

    return;
}

std::vector<std::string> HalfElf::EquipInitialList()const
{
	std::vector<string> initEquip;

	for(int i = 0; i < HALFELF_EQUIP; i++){
		if(DEFAULT_EQUIP[Voc()][i] != ""){
			initEquip.push_back(DEFAULT_EQUIP[Voc()][i]);
		}
	}

	return initEquip;
}

std::string HalfElf::Race_Str()const
{
	return RACE;
}

//************************************** Orc ************************************
const VocRules::VocType Orc::ORC_VOC = VocRules::BBN;
const int Orc::ORC_ABILADJ[ABILITY_COUNT] = {0,0,-2,-2,2,-1};
const std::string Orc::RACE = "ORC";
const std::string Orc::DEFAULT_EQUIP[VocRules::VOC_MAX][ORC_EQUIP] = 	{{"","",""}, //NNE
																		{"Studded leather","Dagger","Great axe","Short bow"}, //BBN
																		{"Crossbow","Short spear","",""}, //CLR
																		{"Large wooden shield","Sword","",""}, //FTR
																		{"Leather","Rapier","Short bow",""}, //ROG
																		{"Club","Light crossbow","",""}}; //WIZ

Orc::Orc()
{
	
}

Orc::Orc(string newName, VocRules::VocType newVoc): Humanoid(newName,newVoc,ORC_VOC,ORC_ABILADJ)
{

}

Orc::Orc(const Orc & o): Humanoid(o)
{

}

void Orc::Write(ostream& out)const
{
	out << Race_Str() << "#";
    Humanoid::Write(out);

    return;
}

std::vector<std::string> Orc::EquipInitialList()const
{
	std::vector<string> initEquip;

	for(int i = 0; i < ORC_EQUIP; i++){
		if(DEFAULT_EQUIP[Voc()][i] != ""){
			initEquip.push_back(DEFAULT_EQUIP[Voc()][i]);
		}
	}

	return initEquip;
}

std::string Orc::Race_Str()const
{
	return RACE;
}
