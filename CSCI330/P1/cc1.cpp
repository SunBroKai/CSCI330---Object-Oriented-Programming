/*Kai Jungbluth - CSCI330*/
#include <iostream>
#include <cstring>
#include <cmath>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "cc1.h"

using namespace std;
using namespace GameSpace;

const std::string CreatureClass::DEFAULT_NAME = "DEFAULT";
const int CreatureClass::DYING_HP = 0;
const int CreatureClass::DEAD_HP = -10;
const int CreatureClass::DISABLED_NUM = 0;
const int CreatureClass::BASE_HP = 1;
const int CreatureClass::BASE_LEVEL = 1;
const int CreatureClass::CON_DEAD = 0;
const int CreatureClass::MIN_ROW = -1;
const int CreatureClass::MIN_COL = -1;
const int CreatureClass::MIN_NAME = 1;
const int CreatureClass::MIN_GP = 0;
const int CreatureClass::MIN_XP = 0;
const int CreatureClass::STAT_DEFAULT = 0;
const int CreatureClass::MONSTER_OFFSET = 4;
const CreatureClass::RaceType CreatureClass::DEFAULT_RACE = HUMAN;
const VocRules::VocType CreatureClass::DEFAULT_VOC[RACE_COUNT] =            
    {VocRules::FTR,VocRules::WIZ,VocRules::ROG,VocRules::BBN,VocRules::NNE,VocRules::NNE};
const int CreatureClass::ABILITY_ADJ[HUMAN_COUNT][ABILITY_COUNT] = {/*HUMAN*/{0,0,0,0,0,0},
                                                                    /*ELF*/{2,-2,0,0,0,0}, 
                                                                    /*HALFELF*/{0,0,0,0,0,0}, 
                                                                    /*ORC*/{0,0,-2,-2,2,-1} };
const int CreatureClass::DEFAULT_ABILITY[MONSTER_COUNT][ABILITY_COUNT] = {/*TROLL*/{14,23,6,6,23,9}, 
                                                                          /*OGRE*/{8,15,6,7,21,10} };

CreatureClass::CreatureClass(){
    SetName(DEFAULT_NAME);
    race = DEFAULT_RACE;
    voc = DEFAULT_VOC[race];
    SetStats();
    
    return;
}

CreatureClass::CreatureClass(string newName){
    SetName(newName);
    race = DEFAULT_RACE;
    voc = DEFAULT_VOC[race];
    SetStats();
    
    return;
}

CreatureClass::CreatureClass(string newName, RaceType newRace){
    SetName(newName);
    SetRace(newRace);
    voc = DEFAULT_VOC[race];
    SetStats();
    
    return;
}

CreatureClass::CreatureClass(string newName, RaceType newRace, VocRules::VocType newVoc){
    SetName(newName);
    SetRace(newRace);
    SetVoc(newVoc);
    SetStats();
    
    return;
}

CreatureClass::~CreatureClass(){
    /*if(name != NULL){
        delete[] name;
    }*/
    return;
}

void CreatureClass::SetName(string newName){
    if(newName.length() <= MIN_NAME){
            name = DEFAULT_NAME;
    }else{
            name = TrimStr(newName);
    }
    /*if(name == NULL){
        if(newName.length() >= 1){
            int i = newName.length() + 1;
            name = new char[i];
            strcpy(name, newName.c_str());
            name[i-1] = '\0';
        }else{
            int x = DEFAULT_NAME.length() + 1;
            name = new char[x];
            strcpy(name, DEFAULT_NAME.c_str());
            name[x-1] = '\0';
        }
    }*/
    return;
}

void CreatureClass::SetRace(RaceType newRace){
    if(newRace > OGRE or newRace < HUMAN){
        race = DEFAULT_RACE;
    }else{
        race = newRace;
    }
    return;
}

void CreatureClass::SetVoc(VocRules::VocType newVoc){
    if(Monster()){   
        voc = VocRules::NNE;
    }else if(newVoc > VocRules::WIZ or newVoc < VocRules::NNE or (Humanoid() and newVoc == VocRules::NNE)){
        voc = DEFAULT_VOC[race];
    }else{
        voc = newVoc;
    }
    
    return;
}

void CreatureClass::SetStats(){
    int i,
        offset = (int)race - MONSTER_OFFSET;
    string sname = name;
    RollType r;
    VocRules::VocRules * vPtr;
    vPtr = VocRules::GetVocRules();
    int diceNum,
		rollHP;
		
    if(Monster()){
        for(i = DEX; i <= WIS; i++){
            statScores[i] = DEFAULT_ABILITY[offset][i];
        }
        switch(race){
            case TROLL:
                statScores[EHP] = Dice::Roll(name,GameSpace::HP,6,8) + 36;
                break;
            case OGRE:
                statScores[EHP] = Dice::Roll(name,GameSpace::HP,4,8) + 8;
                break;
            default:
                break;
        }
        for(i = EXP; i <= LEVEL; i++){
            statScores[i] = STAT_DEFAULT;
        }
    }else if(Humanoid()){
        for(i = DEX; i <= WIS; i++){
            r = (RollType)i;
            statScores[i] = Dice::Roll(name,r,3,6) + ABILITY_ADJ[race][i];
        }
        diceNum = vPtr->VocRules::HitDie(voc);
        rollHP = Dice::Roll(name,GameSpace::HP,1,diceNum) + AbilityMod(CON);
        if(rollHP >= BASE_HP){
			statScores[EHP] = rollHP;
		}else{
			statScores[EHP] = BASE_HP;
		}
        statScores[EXP] = STAT_DEFAULT;
        statScores[EGP] = Dice::Roll(name,GameSpace::GP,1,4);
        statScores[LEVEL] = BASE_LEVEL;
    }
    statScores[ROW] = MIN_ROW;
    statScores[COL] = MIN_COL;
    vPtr->VocRules::DeleteVocRules();
    
    return;
}

void CreatureClass::Write(ostream& out)const{
    out << Race_Str() << "#"
        << Voc_Str() << "#"
        << Name() << "#("
        << Row() << ","
        << Col() << ")#"
        << HP() << "#"
        << Level() << "#"
        << XP() << "#"
        << GP() << "#"
        << Ability(CreatureClass::DEX) << "#"
        << Ability(CreatureClass::CON) << "#"
        << Ability(CreatureClass::INT) << "#"
        << Ability(CreatureClass::CHA) << "#"
        << Ability(CreatureClass::STR) << "#"
        << Ability(CreatureClass::WIS) << "#";
        
    return;
}

string CreatureClass::Name()const{
    string s = name;
    
    return s;
}

int CreatureClass::Row()const{
    return (int)statScores[ROW];
}

int CreatureClass::Col()const{
    
    return (int)statScores[COL];
}

int CreatureClass::Race()const{
    int i = (int)race;
    
    return i;
}

string CreatureClass::Race_Str()const{
    string s;
    
    switch(race){
        case HUMAN:
            s = "HUMAN";
            break;
        case ELF:
            s = "ELF";
            break;
        case HALFELF:
            s = "HALFELF";
            break;
        case ORC:
            s = "ORC";
            break;
        case TROLL:
            s = "TROLL";
            break;
        case OGRE:
            s = "OGRE";
            break;
        default:
            s = "";
            break;
    }
    return s;
}

int CreatureClass::Voc()const{
    int i = (int)voc;
    
    return i;
}

string CreatureClass::Voc_Str()const{
    string s = VocRules::VocToStr(voc);
    
    return s;
}

int CreatureClass::Level()const{
    return (int)statScores[LEVEL];
}

int CreatureClass::HP()const{
    return (int)statScores[EHP];
}

long CreatureClass::XP()const{
    return statScores[EXP];
}

long CreatureClass::GP()const{
    return statScores[EGP];
}

int CreatureClass::Ability(AbilityType ability)const{
    int i;
    
    if(ability > WIS or ability < DEX){
        i = STAT_DEFAULT;
    }else{
        i = (int)statScores[ability];
    }
    
    return i;
}

bool CreatureClass::Humanoid()const{
    bool r = false;
   
    if(race == HUMAN or race == ELF or race == HALFELF or race == ORC){
        r = true;
    }
   
    return r;
}

bool CreatureClass::Monster()const{
    bool r = false;
   
    if(race == TROLL or race == OGRE){
        r = true;
    }
   
    return r;
}

bool CreatureClass::Dead()const{
    bool r = false;
    
    if(statScores[EHP] <= DEAD_HP or  statScores[CON] <= CON_DEAD){
        r = true;
    }
    
    return r;
}

bool CreatureClass::Dying()const{
    bool r = false;
    
    if(statScores[EHP] < DYING_HP and statScores[EHP] > DEAD_HP){
        r = true;
    }
    
    return r;
}

bool CreatureClass::Disabled()const{
    bool r = false;
    int i;
    
    for(i = 0;i <= WIS;i++){
        if(statScores[i] <= 0){
            r = true;
        }
    }
    if(statScores[EHP] <= DYING_HP){
        r = true;
    }
    return r;
}

int CreatureClass::AbilityMod(AbilityType ability)const{
    int abilMod;
    
    abilMod = floor(((int)statScores[ability]/2) - 5);
    
    return abilMod;
}

bool CreatureClass::SetCell(int newRow, int newCol){
    bool r = false,
         testRow = true,
         testCol = true;
    
    if((newRow < MIN_ROW) or (newRow == MIN_ROW and newCol != MIN_COL)){
        testRow = false;
    }
    if((newCol < MIN_COL) or (newCol == MIN_COL and newRow != MIN_ROW)){
        testCol = false;
    }
    if(testRow == true and testCol == true){
        statScores[ROW] = newRow;
        statScores[COL] = newCol;
        r = true;
    }
    return r;
}

int CreatureClass::UpdateHP(int modification){
    statScores[EHP] += modification;
    
    return (int)statScores[EHP];
}

long CreatureClass::UpdateGP(int value){
    long result = statScores[EGP] + value;
    
    if(Humanoid() and result >= MIN_GP){
        statScores[EGP] += value;
    }
    
    return statScores[EGP];
}

long CreatureClass::UpdateXP(int value){
    VocRules::VocRules * vPtr;
    vPtr = VocRules::GetVocRules();
    int addedHP = 0;
    string sname = name;
    
    if(Humanoid() and value >= MIN_XP){
        int diceNum = vPtr->VocRules::HitDie(voc);
        statScores[EXP] += value;
        while(statScores[EXP] >= VocRules::XPforPromotion(statScores[LEVEL]+1)
        and statScores[LEVEL] < VocRules::LEVEL_MAX){
            statScores[LEVEL]++;
            addedHP = Dice::Roll(name,GameSpace::HP,1,diceNum) + AbilityMod(CON);
            if(addedHP >= 1){
                UpdateHP(addedHP);
            }else{
                UpdateHP(1);
            }            
        }
    }
    vPtr->VocRules::DeleteVocRules();
    
    return statScores[EXP];
}

bool CreatureClass::operator==(const CreatureClass & c)const{
    bool r = false;
    
    if(Ucase(name) == Ucase(c.name)){
        r = true;
    }
    
    return r;
}


bool CreatureClass::operator!=(const CreatureClass & c)const{
    bool r = false;
    
    if(Ucase(name) != Ucase(c.name)){
        r = true;
    }
    
    return r;
}

ostream& operator<<(ostream& out, const CreatureClass & c){
    c.Write(out);
      
    return out;
}