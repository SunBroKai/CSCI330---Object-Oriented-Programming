//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//handle.cpp Creature
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat. 
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#include "handle4.h"

using namespace std;
using namespace GameSpace;

const string Creature::RACE_STR[RACE_COUNT] = {"HUMAN","ELF","HALFELF","ORC","TROLL","OGRE"};

Creature::Creature(): creature(NULL)
{
    
}

Creature::Creature(string name, RaceType race, VocRules::VocType voc): creature(NULL)
{
    switch(race){
        case ELF:
            creature = new Elf(name, voc);
            break;
        case HALFELF:
            creature = new HalfElf(name, voc);
            break;
        case ORC:
            creature = new Orc(name, voc);
            break;
        case TROLL:
            creature = new Troll(name);
            break;
        case OGRE:
            creature = new Ogre(name);
            break;
        case HUMAN:
        default:
            creature = new Human(name, voc);
    }
}

Creature::Creature(const Creature & c): creature(NULL)
{
    CopyIntoMe(c);
}

Creature::Creature(CreatureClass * ptr): creature(NULL)
{
    if(ptr){
        creature = ptr->Clone();
    }
}

Creature::~Creature()
{
    if(creature){
        delete creature;
        creature = NULL;
    }
}

void Creature::CopyIntoMe(const Creature & c)
{
    delete creature;
    creature = NULL;
    if (c.creature)
    {
        creature = c.creature->Clone();
    }
    
    return;
}

string Creature::Race_Str() const
{
    Human * tmpHuman = dynamic_cast<Human*>(creature);
    Elf * tmpElf = dynamic_cast<Elf*>(creature);
    HalfElf * tmpHalfElf = dynamic_cast<HalfElf*>(creature);
    Orc * tmpOrc = dynamic_cast<Orc*>(creature);
    Troll * tmpTroll = dynamic_cast<Troll*>(creature);
    Ogre * tmpOgre = dynamic_cast<Ogre*>(creature);
    
    if(tmpHuman){
        return tmpHuman->Race_Str();
    }else if(tmpElf){
        return tmpElf->Race_Str();
    }else if(tmpHalfElf){
        return tmpHalfElf->Race_Str();
    }else if(tmpOrc){
        return tmpOrc->Race_Str();
    }else if(tmpTroll){
        return tmpTroll->Race_Str();
    }else if(tmpOgre){
        return tmpOgre->Race_Str();
    }
    
    return "";
}

int Creature::Race() const
{
    int race = 0;
    
    if(creature){
        for(int i = 0; i < RACE_COUNT; i++){
            if(Ucase(Race_Str()) == Ucase(RACE_STR[i])){
                race = i;
            }
        }
    }
    
    return race;
}

bool Creature::IsHumanoid() const
{
    bool humanoid = false;
    Humanoid * tmpHum = dynamic_cast<Humanoid*>(creature);
    
    if(tmpHum){
        humanoid = true;
    }
    
    return humanoid;
}

bool Creature::IsMonster() const
{
    bool monster = false;
    Monster * tmpMon = dynamic_cast<Monster*>(creature);
    
    if(tmpMon){
        monster = true;
    }
    
    return monster;
}

void Creature::Write(ostream& out) const
{
    if(creature){
        creature->Write(out);
    }
    
    return;
}

std::string Creature::Name() const
{
    if(creature){
        return creature->Name();
    }
    
    return "";
}

int Creature::Row()const
{
    if(creature){
        return creature->Row();
    }
    
    return 0;
}

int Creature::Col()const
{
    if(creature){
        return creature->Col();
    }
    
    return 0;
}

int Creature::HP()const
{
    if(creature){
        return creature->HP();
    }
    
    return 0;
}

int Creature::Ability(CreatureClass::AbilityType ability)const
{
    if(creature){
        return creature->Ability(ability);
    }
    
    return 0;
}

std::vector<int> Creature::Abilities()
{
    if(creature){
        return creature->Abilities();
    }
    
    return vector<int>();
}

bool Creature::Active()const
{
    if(creature){
        return creature->Active();
    }
    
    return false;
}

bool Creature::Dead()const
{
    if(creature){
        return creature->Dead();
    }
    
    return false;
}

bool Creature::Dying()const
{
    if(creature){
        return creature->Dying();
    }
    
    return false;
}

bool Creature::Disabled()const
{
    if(creature){
        return creature->Disabled();
    }
    
    return false;
}

int Creature::AbilityMod(CreatureClass::AbilityType ability)const
{
    if(creature){
        return creature->AbilityMod(ability);
    }
    
    return 0;
}

std::string Creature::Weapon()const
{
    if(creature){
        return creature->Weapon();
    }
    
    return "";
}

std::string Creature::Armor()const
{
    if(creature){
        return creature->Armor();
    }
    
    return "";
}

int Creature::SkillCheck(std::string skill)
{
    if(creature){
        return creature->SkillCheck(skill);
    }
    
    return 0;
}

bool Creature::HasWeapon()const
{
    if(creature){
        return creature->HasWeapon();
    }
    
    return false;
}

bool Creature::HasArmor()const
{
    if(creature){
        return creature->HasArmor();
    }
    
    return false;
}

std::vector<std::string> Creature::Skills()const
{
    if(creature){
        return creature->Skills();
    }
    
    return vector<string>();
}

bool Creature::SetCell(int newRow, int newCol)
{
    if(creature){
        return creature->SetCell(newRow, newCol);
    }
    
    return false;
}

int Creature::UpdateHP(int modification)
{
    if(creature){
        return creature->UpdateHP(modification);
    }
    
    return 0;
}

std::vector<std::string> Creature::EquipInitialList()
{
    if(creature){
        return creature->EquipInitialList();
    }
    
    return vector<string>();
}

EquipClass::EquipClass * Creature::FindEquipment(EquipClass * equipment)
{
    if(creature){
        return creature->FindEquipment(equipment);
    }
    
    return NULL;
}

EquipClass::EquipClass * Creature::LoseEquipment()
{
    if(creature){
        return creature->LoseEquipment();
    }
    
    return NULL;
}

WeaponClass::WeaponClass * Creature::FindWeapon(WeaponClass * wpn)
{
    if(creature){
        return creature->FindWeapon(wpn);
    }
    
    return NULL;
}

WeaponClass::WeaponClass * Creature::LoseWeapon()
{
    if(creature){
        return creature->LoseWeapon();
    }
    
    return NULL;
}

ArmorClass::ArmorClass * Creature::FindArmor(ArmorClass * amr)
{
    if(creature){
        return creature->FindArmor(amr);
    }
    
    return NULL;
}

ArmorClass::ArmorClass * Creature::LoseArmor()
{
    if(creature){
        return creature->LoseArmor();
    }
    
    return NULL;
}

bool Creature::AddSkill(string skill)
{
    if(creature){
        return creature->AddSkill(skill);
    }
    
    return false;
}

void Creature::Amnesia()
{
    if(creature){
        creature->Amnesia();
    }
    
    return;
}

int Creature::InitiativeCheck()const
{
    if(creature){
        return creature->InitiativeCheck();
    }
    
    return 0;
}

int Creature::AttackRoll()const
{
    if(creature){
        return creature->AttackRoll();
    }
    
    return 0;
}

int Creature::SavingThrow(SavingThrowType s)const
{
    if(creature){
        return creature->SavingThrow(s);
    }
    
    return 0;
}

int Creature::Defense()const
{
    if(creature){
        return creature->Defense();
    }
    
    return 0;
}

int Creature::Damage()const
{
    if(creature){
        return creature->Damage();
    }
    
    return 0;
}

int Creature::Voc()const
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->Voc();
    }
    
    return VocRules::NNE;
}

std::string Creature::Voc_Str()const
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->Voc_Str();
    }
    
    return "";
}

int Creature::Level()const
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->Level();
    }
    
    return 0;
}

long Creature::XP()const
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->XP();
    }
    
    return 0;
}

long Creature::GP()const
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->GP();
    }
    
    return 0;
}

std::vector<std::string> Creature::Pack()const
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->Pack();
    }
    
    return vector<string>();
}

std::vector<std::string> Creature::EquipInventory()const
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->EquipInventory();
    }
    
    return vector<string>();
}

long Creature::UpdateGP(int value)
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->UpdateGP(value);
    }
    
    return 0;
}

long Creature::UpdateXP(int value)
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->UpdateXP(value);
    }
    
    return 0;
}

bool Creature::ChangeEquipment(string equipName)
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->ChangeEquipment(equipName);
    }
    
    return false;
}

EquipClass::EquipClass * Creature::BuyEquipment(EquipClass * equipment)
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->BuyEquipment(equipment);
    }
    
    return NULL;
}

EquipClass::EquipClass * Creature::SellEquipment(string equip)
{
    Humanoid * tmp = dynamic_cast<Humanoid*>(creature);
    
    if(tmp){
        return tmp->SellEquipment(equip);
    }
    
    return NULL;
}

Creature & Creature::operator=(const Creature & c)
{
    if(this != &c){
        CopyIntoMe(c);
    }
    return * this;
}

bool Creature::operator==(const Creature & c)const
{
    if(creature and *creature == *c.creature){
        return true;
    }
    
    return false;
}

bool Creature::operator!=(const Creature & c)const
{
    if(creature and *creature != *c.creature){
        return true;
    }
    
    return false;
}

bool Creature::operator<(const Creature & c)const
{
    if(creature and *creature < *c.creature){
        return true;
    }
    
    return false;
}

bool Creature::operator<=(const Creature & c)const
{
    if(creature and *creature <= *c.creature){
        return true;
    }
    
    return false;
}

bool Creature::operator>(const Creature & c)const
{
    if(creature and *creature > *c.creature){
        return true;
    }
    
    return false;
}

bool Creature::operator>=(const Creature & c)const
{
    if(creature and *creature >= *c.creature){
        return true;
    }
    
    return false;
}

std::ostream& operator<<(ostream& out, const Creature & c)
{
    c.Write(out);
    
    return out;
}







