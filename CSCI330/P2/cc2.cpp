//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 2
//cc2.cpp CreatureClass
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include "cc2.h"

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
const int CreatureClass::MAX_NAME = 10;
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
const std::string CreatureClass::DEFAULT_SKILLS[VocRules::VOC_MAX][DSKILL_COUNT] = {/*NNE*/{"","",""},
                                                                     /*BBN*/{"CLIMB","LISTEN","SWIM"},
                                                                     /*CLR*/{"HEAL","USE MAGIC DEVICES",""},
                                                                     /*FTR*/{"INTIMIDATE","SWIM",""},
                                                                     /*ROG*/{"BLUFF","CLIMB","HIDE"},
                                                                     /*WIZ*/{"CONCENTRATION","HIDE",
                                                                                "USE MAGIC DEVICES"}};
const std::string CreatureClass::MONSTER_SKILLS[MONSTER_COUNT][DSKILL_COUNT] ={
                                                                    /*TROLL*/{"LISTEN","SPOT",""},
                                                                    /*OGRE*/ {"INTIMIDATE","LISTEN","SPOT"} 
                                                                              };

CreatureClass::CreatureClass(){
    SetName(DEFAULT_NAME);
    race = DEFAULT_RACE;
    voc = DEFAULT_VOC[race];
    SetStats();
    SetEquip();
    SetSkills();
}

CreatureClass::CreatureClass(string newName, RaceType newRace, VocRules::VocType newVoc){
    SetName(newName);
    SetRace(newRace);
    SetVoc(newVoc);
    SetStats();
    SetEquip();
    SetSkills();
}

CreatureClass::CreatureClass(const CreatureClass & c){
    SetName(c.name);
    SetRace(c.race);
    SetVoc(c.voc);
    for(int i = 0; i < STAT_COUNT; i++){
        statScores[i] = c.statScores[i];
    }
    if(c.weapon != NULL){
        weapon = new WeaponClass(c.weapon->Name());
    }else{
        weapon = NULL;
    }
    if(c.armor != NULL){
        armor = new ArmorClass(c.armor->Name());
    }else{
        armor = NULL;
    }   
    for(int j = 0; j < c.skills.size(); j++){
        skills.push_back(c.skills[j]);
    }
}

CreatureClass::~CreatureClass(){
    if(name != NULL){
        delete[] name;
        name = NULL;
    }
    if(weapon != NULL){
        delete weapon;
        weapon = NULL;
    }
    if(armor != NULL){
        delete armor;
        armor = NULL;
    }
    
    return;
}

void CreatureClass::SetName(string newName){
    string tmpName = TrimStr(newName);
    if(tmpName.size() <= MIN_NAME){
        name = new char[DEFAULT_NAME.size() + 1];
        strcpy(name, DEFAULT_NAME.c_str());
    }else if(tmpName.size() >= MAX_NAME){
        tmpName.resize(MAX_NAME);
        name = new char[tmpName.size() + 1];
        strcpy(name, tmpName.c_str());
    }else{
        name = new char[tmpName.size() + 1];
        strcpy(name, tmpName.c_str());
    }
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

void CreatureClass::SetEquip(){
    weapon = NULL;
    armor = NULL;

    return;
}

void CreatureClass::SetSkills(){
    int skillNum = 0;
    bool valid = true;
    if(Humanoid()){
        switch(voc){
            case VocRules::NNE:
                break;
            case VocRules::BBN:
                skillNum = 3;
                valid = true;
                break;
            case VocRules::CLR:
                skillNum = 2;
                valid = true;
                break;
            case VocRules::FTR:
                skillNum = 2;
                valid = true;
                break;
            case VocRules::ROG:
                skillNum = 3;
                valid = true;
                break;
            case VocRules::WIZ:
                skillNum = 3;
                valid = true;
                break;
            default:
                break;
        }
        if(valid){
            for(int i = 0; i < skillNum; i++){
                skills.push_back(DEFAULT_SKILLS[voc][i]);
            }
        }
    }else if(Monster()){
        int offset = (int)race - MONSTER_OFFSET;
        switch(race){
            case TROLL:
            valid = true;
            skillNum = 2;
                break;
            case OGRE:
            valid = true;
            skillNum = 3;
                break;
            default:
                break;
        }
        if(valid){
            for(int i = 0; i < skillNum; i++){
                skills.push_back(MONSTER_SKILLS[offset][i]);
            }
        }
    }
    
    return;
}

std::vector<std::string> CreatureClass::ReadFile(string fileName){
    ifstream inFile;
    string inStr;
    vector<string> inVec;
    inFile.open(fileName.c_str());
    while(not inFile.eof()){
        getline(inFile,inStr,'#');
        inVec.push_back(Ucase(inStr));
        inFile.ignore(1000, '\n');
    }
    inFile.close();

    return inVec;
}

std::vector<CreatureClass::AbilityType> CreatureClass::ReadAbil(string fileName){
    ifstream inFile;
    string inStr;
    
    vector<AbilityType> inVec;
    inFile.open(fileName.c_str());
    while(not inFile.eof()){
        inFile.ignore(1000, '#');
        getline(inFile,inStr,'\n');
        inVec.push_back(StrToAbil(Ucase(inStr)));
    }
    inFile.close();
    
    return inVec;
}

CreatureClass::AbilityType CreatureClass::StrToAbil(string abilityStr){
    CreatureClass::AbilityType rAbil = CreatureClass::DEX;
    if(abilityStr == "DEX"){
        rAbil = CreatureClass::DEX;
    }else if(abilityStr == "CON"){
        rAbil = CreatureClass::CON;
    }else if(abilityStr == "INT"){
        rAbil = CreatureClass::INT;
    }else if(abilityStr == "CHA"){
        rAbil = CreatureClass::CHA;
    }else if(abilityStr == "STR"){
        rAbil = CreatureClass::STR;
    }else if(abilityStr == "WIS"){
        rAbil = CreatureClass::WIS;
    }
    
    return rAbil;
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
    if(armor != NULL){
        out << armor->Name();
    }
    out << "#";
    if(weapon != NULL){
        out << weapon->Name();
    }
    out << "#(";
    for(int i = 0; i < skills.size(); i++){
        if(i != skills.size() - 1){
            out << skills[i] << ",";
        }else{
            out << skills[i];
        }
    }
    out << ")#";

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
    return race;
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
    return voc;
}

string CreatureClass::Voc_Str()const{
    return VocRules::VocToStr(voc);
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

std::vector<int> CreatureClass::Abilities(){
    std::vector<int> rVec;

    for(int i = DEX; i <= WIS; i++){
        rVec.push_back((int)statScores[i]);
    }

    return rVec;
}

bool CreatureClass::Humanoid()const{
    return (race == HUMAN or race == ELF or race == HALFELF or race == ORC);
}

bool CreatureClass::Monster()const{
    return (race == TROLL or race == OGRE);
}

bool CreatureClass::Dead()const{
    return (statScores[EHP] <= DEAD_HP or  statScores[CON] <= CON_DEAD);
}

bool CreatureClass::Dying()const{
    return (statScores[EHP] < DYING_HP and statScores[EHP] > DEAD_HP);
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

string CreatureClass::Weapon(){
    string rStr;
    if(weapon != NULL){
        rStr = weapon->Name();
    }

    return rStr;
}

string CreatureClass::Armor(){
    string rStr;
    if(armor != NULL){
        rStr = armor->Name();
    }

    return rStr;
}

int CreatureClass::SkillCheck(string skill){
    std::vector<string> strVec = ReadFile("skills.in");
    std::vector<AbilityType> abilVec = ReadAbil("skills.in");
    bool found = false;
    int rNum = 0;

    for(int i = 0; i < skills.size(); i++){
        if(Ucase(skill) == skills[i]){
            found = true;
        }
    }
    if(found == true and (not Dead())){
        for(int j = 0; j < strVec.size();j++){
            if(Ucase(skill) == strVec[j]){
                rNum = Dice::Roll(name,GameSpace::SKCK,1,20) + AbilityMod(abilVec[j]);
            }
        }
    }

    return rNum;
}

std::vector<string> CreatureClass::Skills(){
    return skills;
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

bool CreatureClass::HasWeapon(){
    return (weapon != NULL);
}

bool CreatureClass::HasArmor(){
    return (armor != NULL);
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

WeaponClass::WeaponClass * CreatureClass::FindWeapon(WeaponClass::WeaponClass * wpn){
    WeaponClass::WeaponClass * tmp = NULL;
    
    if(wpn != NULL){
        if((not Dying()) and (not Dead()) and (not Disabled())){
            tmp = weapon;
            weapon = wpn;
        }else{
            tmp = wpn;
        }
    }
    
    return tmp;
}

WeaponClass::WeaponClass * CreatureClass::LoseWeapon(){
    WeaponClass::WeaponClass * tmp = NULL;
    if(weapon != NULL){
        tmp = weapon;
        weapon = NULL;
    }

    return tmp;
}

ArmorClass::ArmorClass * CreatureClass::FindArmor(ArmorClass::ArmorClass * amr){
    ArmorClass::ArmorClass * tmp = NULL;
    if(amr != NULL){
        if((not Dying()) and (not Dead()) and (not Disabled())){
            tmp = armor;
            armor = amr;
        }else{
            tmp = amr;
        }
    }

    return tmp;
}

ArmorClass::ArmorClass * CreatureClass::LoseArmor(){
    ArmorClass::ArmorClass * tmp = NULL;
    if(armor != NULL){
        tmp = armor;
        armor = NULL;
    }

    return tmp;
}

bool CreatureClass::AddSkill(string skill){
    std::vector<string> inVec;
    bool found = false,
         valid = false,
         r = false;

    inVec = ReadFile("skills.in");
    for(int i = 0; i < inVec.size(); i++){
        if(Ucase(skill) == inVec[i]){
            valid = true;
            for (int j = 0; j < skills.size(); j++){
                if(inVec[i] == skills[j]){
                    found = true;
                    r = true;
                }
            }
        }
    }
    if((valid) and (not found) and (not Dying()) and (not Dead()) and (not Disabled())){
        skills.push_back(Ucase(skill));
        r = true;
    }

    return r;
}

void CreatureClass::Amnesia(){
    skills.clear();

    return;
}

bool CreatureClass::operator==(const CreatureClass & c)const{
    return (Ucase(name) == Ucase(c.name));
}


bool CreatureClass::operator!=(const CreatureClass & c)const{
    return (Ucase(name) != Ucase(c.name));
}

bool CreatureClass::operator<(const CreatureClass & c)const{
    return (not GameSpace::Cmp(c.name, name));
}

bool CreatureClass::operator<=(const CreatureClass & c)const{
    return (GameSpace::Cmp(name, c.name));
}

bool CreatureClass::operator>(const CreatureClass & c)const{
    return (not GameSpace::Cmp(name, c.name));
}

bool CreatureClass::operator>=(const CreatureClass & c)const{
    return (GameSpace::Cmp(c.name, name));
}

CreatureClass & CreatureClass::operator=(const CreatureClass & c){
    if(this != &c){
        delete[] name;
        if(c.name != NULL){
            SetName(c.name);
        }else{
            name = NULL;
        }
        race = c.race;
        voc = c.voc;
        for(int i = 0; i < STAT_COUNT; i++){
            statScores[i] = c.statScores[i];
        }
        delete weapon;
        if(c.weapon != NULL){
            weapon = new WeaponClass(c.weapon->Name());
        }else{
            weapon = NULL;
        }
        delete armor;
        if(c.armor != NULL){
            armor = new ArmorClass(c.armor->Name());
        }else{
            armor = NULL;
        }
        skills.clear();
        for(int j = 0; j < c.skills.size(); j++){
            skills.push_back(c.skills[j]);
        }
    }
    return * this;
}

ostream& operator<<(ostream& out, const CreatureClass & c){
    c.Write(out);
      
    return out;
}
