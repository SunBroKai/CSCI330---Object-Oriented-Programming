//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//monster.cpp
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#include "monster4.h"

using namespace std;
using namespace GameSpace;

//************************************** Monster **********************************

Monster::Monster(){

}

Monster::Monster(string newName): CreatureClass(newName)
{

}

Monster::Monster(const Monster & m): CreatureClass(m)
{

}

void Monster::SetStats(const int defAbil[], int hpNum)
{
    int abil[ABILITY_COUNT];

    for(int i = 0; i < ABILITY_COUNT; i++){
        abil[i] = defAbil[i];
    }
    CreatureClass::SetStats(abil);
    SetHP(hpNum);

    return;
}

EquipClass::EquipClass * Monster::FindEquipment(EquipClass * equipment)
{
    EquipClass * rEquip = NULL;
    WeaponClass * tmpWpn = NULL;
    ArmorClass * tmpAmr = NULL;

    tmpWpn = dynamic_cast <WeaponClass*>(equipment);
    tmpAmr = dynamic_cast <ArmorClass*>(equipment);

    if(tmpWpn){
        rEquip = FindWeapon(tmpWpn);
    }else if(tmpAmr){
        rEquip = FindArmor(tmpAmr);
    }else{
        rEquip = equipment;
    }

    return rEquip;
}


int Monster::AttackRoll(const int baseAtt[])const
{
    int rNum = 0;

    if(Active()){
        rNum = Dice::Roll(Name(),GameSpace::ATT,1,20) + AttackBonus(baseAtt);
    }

    return rNum;
}

int Monster::AttackBonus(const int baseAtt[])const
{
    int attRoll = 0;

    
    if(WeaponClass::IsRange(Weapon())){
        attRoll = baseAtt[1] + AbilityMod(DEX);
    }else if(WeaponClass::IsMelee(Weapon())){
        attRoll = baseAtt[0] + AbilityMod(STR);
    }else{
        attRoll = AbilityMod(STR);
    }
    

    return attRoll;
}

int Monster::SavingThrow(SavingThrowType s, const int savingThrows[])const
{
    int bonus = 0;

    if(Active()){
        switch(s){
            case FORT:
                bonus = savingThrows[s - 1] + AbilityMod(CON);
                break;
            case REFLEX:
                bonus = savingThrows[s - 1] + AbilityMod(DEX);
                break;
            case WILL:
                bonus = savingThrows[s - 1] + AbilityMod(WIS);
                break;
            default:
                throw INVALID_SAVINGTHROW;
                break;
        }
    }

    return Dice::Roll(Name(),GameSpace::SVTH,1,20) + bonus;
}


void Monster::Write(ostream& out)const
{
    vector<string> skillVec = Skills();

    out << Name() << "#("
        << Row() << ","
        << Col() << ")#"
        << HP() << "#["
        << Ability(CreatureClass::DEX) << "#"
        << Ability(CreatureClass::CON) << "#"
        << Ability(CreatureClass::INT) << "#"
        << Ability(CreatureClass::CHA) << "#"
        << Ability(CreatureClass::STR) << "#"
        << Ability(CreatureClass::WIS) << "]#(";
    for(int i = 0; i < skillVec.size(); i++){
        if(i != skillVec.size() - 1){
            out << skillVec[i] << ",";
        }else{
            out << skillVec[i];
        }
    }
    out << ")#"
        << Armor() << "#"
        << Weapon() << "#"
        << endl;

    return;
}

//*************************************** Troll ***********************************

const int Troll::TROLL_ABILITY[ABILITY_COUNT] = {14,23,6,6,23,9};
const std::string Troll::DEFAULT_SKILLS[TROLL_SKILLS] = {"LISTEN","SPOT"};
const std::string Troll::RACE = "TROLL";
const int Troll::BASE_ATT[2] = {9,1};
const int Troll::SAVING_THROW[3] = {11,4,3};
const std::string Troll::INIT_EQUIP[2] = {"Thick skin","Club"};

Troll::Troll()
{

}

Troll::Troll(string newName): Monster(newName)
{  
    Monster::SetStats(TROLL_ABILITY,Dice::Roll(Name(),GameSpace::HP,6,8) + 36);
    SetSkills(DEFAULT_SKILLS, TROLL_SKILLS);
}

Troll::Troll(const Troll & t): Monster(t)
{

}

Troll * Troll::Clone()const
{
    return new Troll(*this);
}

std::string Troll::Race_Str()const
{
	return RACE;
}

std::vector<std::string> Troll::EquipInitialList()const
{
    std::vector<string> initEquip;

    initEquip.push_back(INIT_EQUIP[0]);
    initEquip.push_back(INIT_EQUIP[1]);

    return initEquip;
}

int Troll::AttackRoll()const
{
    return Monster::AttackRoll(BASE_ATT);
}

int Troll::SavingThrow(SavingThrowType s)const
{
    return Monster::SavingThrow(s,SAVING_THROW);
}

void Troll::Write(ostream& out)const
{
    out << Race_Str() << "#";
    Monster::Write(out);

    return;
}

//*************************************** Ogre ************************************

const int Ogre::OGRE_ABILITY[ABILITY_COUNT] = {8,15,6,7,21,10};
const std::string Ogre::DEFAULT_SKILLS[OGRE_SKILLS] = {"INTIMIDATE","LISTEN","SPOT"};
const std::string Ogre::RACE = "OGRE";
const int Ogre::BASE_ATT[2] = {8,1};
const int Ogre::SAVING_THROW[3] = {6,0,1};
const std::string Ogre::INIT_EQUIP[2] = {"Spiked bands","Spear"};

Ogre::Ogre()
{
    
}

Ogre::Ogre(string newName): Monster(newName)
{
    Monster::SetStats(OGRE_ABILITY, Dice::Roll(Name(),GameSpace::HP,4,8) + 8);
    SetSkills(DEFAULT_SKILLS, OGRE_SKILLS);
}

Ogre::Ogre(const Ogre & o): Monster(o)
{

}

Ogre * Ogre::Clone()const
{
    return new Ogre(*this);
}

std::string Ogre::Race_Str()const
{
	return RACE;
}

std::vector<std::string> Ogre::EquipInitialList()const
{
    std::vector<string> initEquip;

    initEquip.push_back(INIT_EQUIP[0]);
    initEquip.push_back(INIT_EQUIP[1]);

    return initEquip;
}


int Ogre::AttackRoll()const
{
    return Monster::AttackRoll(BASE_ATT);
}

int Ogre::SavingThrow(SavingThrowType s)const
{
    return Monster::SavingThrow(s,SAVING_THROW);
}

void Ogre::Write(ostream& out)const
{
    out << Race_Str() << "#";
    Monster::Write(out);

    return;
}
