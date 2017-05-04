//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//cc4.cpp CreatureClass
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#include "cc4.h"

using namespace std;
using namespace GameSpace;

const std::string CreatureClass::DEFAULT_NAME = "DEFAULT";
const int CreatureClass::DYING_HP = 0;
const int CreatureClass::DEAD_HP = -10;
const int CreatureClass::DISABLED_NUM = 0;
const int CreatureClass::CON_DEAD = 0;
const int CreatureClass::MIN_ROW = -1;
const int CreatureClass::MIN_COL = -1;
const int CreatureClass::MIN_NAME = 1;
const int CreatureClass::MAX_NAME = 10;
std::vector<CreatureClass::SkillRec> CreatureClass::SkillsTable;

CreatureClass::CreatureClass(){

}

CreatureClass::CreatureClass(string newName){
    SetName(newName);
    SetEquip();
    LoadSkillTable();
}

CreatureClass::CreatureClass(const CreatureClass & c){
    SetName(c.name);
    for(int i = 0; i < STAT_COUNT; i++){
        statScores[i] = c.statScores[i];
    }
    if(c.weapon != NULL){
        weapon = new WeaponClass(c.weapon->EquipClass::Name());
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
    LoadSkillTable();
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
        throw INVALID_NAME;
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

void CreatureClass::SetStats(int abil[]){
    for(int i = DEX; i <= WIS; i++){
        statScores[i] = abil[i];
    }
    statScores[ROW] = MIN_ROW;
    statScores[COL] = MIN_COL;

    return;
}

void CreatureClass::SetHP(int hpNum){
    statScores[EHP] = hpNum;

    return;
}

void CreatureClass::SetSkills(const std::string newSkills[], int size){
    for(int i = 0; i < size; i++){
        if(newSkills[i] != ""){
            skills.push_back(newSkills[i]);
        }
    }

    return;
}

void CreatureClass::LoadSkillTable(){
    ifstream inFile;
    SkillRec skill;
    string inStr;

    inFile.open("skills.in");
    while(not inFile.eof()){
        getline(inFile,inStr,'#');
        if(inFile){
            skill.skill = Ucase(inStr);
            getline(inFile,inStr,'\n');
            if(inStr == "DEX"){
                skill.abil = CreatureClass::DEX;
            }else if(inStr == "CON"){
                skill.abil = CreatureClass::CON;
            }else if(inStr == "INT"){
                skill.abil = CreatureClass::INT;
            }else if(inStr == "CHA"){
                skill.abil = CreatureClass::CHA;
            }else if(inStr == "STR"){
                skill.abil = CreatureClass::STR;
            }else if(inStr == "WIS"){
                skill.abil = CreatureClass::WIS;
            }
            SkillsTable.push_back(skill);
            //cout << skill.skill << endl;
            //cout << skill.abil << endl;
        }
    }
    inFile.close();

    return;
}

void CreatureClass::SetEquip(){
    weapon = NULL;
    armor = NULL;

    return;
}

void CreatureClass::Write(ostream& out)const{
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
    for(int i = 0; i < skills.size(); i++){
        if(i != skills.size() - 1){
            out << skills[i] << ",";
        }else{
            out << skills[i];
        }
    }
    out << ")#";
    if(armor != NULL){
        out << armor->Name();
    }
    out << "#";
    if(weapon != NULL){
        out << weapon->Name();
    }

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

int CreatureClass::HP()const{
    return (int)statScores[EHP];
}

int CreatureClass::Ability(AbilityType ability)const{
    int i;
    
    if(ability > WIS or ability < DEX){
        throw INVALID_ABILITY;
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

bool CreatureClass::Active()const{
    return (not(Dead() or Dying() or Disabled()));
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
    
    if(ability < DEX or ability > WIS){
        throw INVALID_ABILITY;
    }else{
        abilMod = floor(((int)statScores[ability]/2) - 5);
    }
    
    return abilMod;
}

string CreatureClass::Weapon()const{
    string rStr;
    if(weapon != NULL){
        rStr = weapon->EquipClass::Name();
    }

    return rStr;
}

string CreatureClass::Armor()const{
    string rStr;
    if(armor != NULL){
        rStr = armor->Name();
    }

    return rStr;
}

int CreatureClass::SkillCheck(string skill){
    bool    found = false,
            calculated = false;
    int rNum = 0;

    for(int i = 0; i < skills.size(); i++){
        if(Ucase(skill) == skills[i]){
            found = true;
        }
    }
    if(found == true and (not Dead())){
        for(int j = 0; j < SkillsTable.size(); j++){
            if(Ucase(skill) == SkillsTable[j].skill and calculated == false){
                rNum = Dice::Roll(name,GameSpace::SKCK,1,20) + AbilityMod(SkillsTable[j].abil);
                calculated = true;
            }
        }
    }

    return rNum;
}

std::vector<string> CreatureClass::Skills()const{
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

bool CreatureClass::HasWeapon()const{
    return (weapon != NULL);
}

bool CreatureClass::HasArmor()const{
    return (armor != NULL);
}

int CreatureClass::UpdateHP(int modification){
    statScores[EHP] += modification;
    
    return (int)statScores[EHP];
}

EquipClass::EquipClass * CreatureClass::FindEquipment(EquipClass * equipment){
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

EquipClass::EquipClass * CreatureClass::LoseEquipment(){
    EquipClass::EquipClass * tmp = NULL;

    if(HasWeapon()){
        tmp = weapon;
        weapon = NULL;
    }else if(HasArmor()){
        tmp = armor;
        armor = NULL;
    }

    return tmp;
}

WeaponClass::WeaponClass * CreatureClass::FindWeapon(WeaponClass::WeaponClass * wpn){
    WeaponClass::WeaponClass * tmp = NULL;
    
    if(wpn != NULL){
        if(Active()){
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
    if(HasWeapon()){
        tmp = weapon;
        weapon = NULL;
    }

    return tmp;
}

ArmorClass::ArmorClass * CreatureClass::FindArmor(ArmorClass::ArmorClass * amr){
    ArmorClass::ArmorClass * tmp = NULL;
    if(amr != NULL){
        if(Active()){
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
    if(HasArmor()){
        tmp = armor;
        armor = NULL;
    }

    return tmp;
}

bool CreatureClass::AddSkill(string skill){
    bool found = false,
         valid = false,
         r = false;

    for(int i = 0; i < SkillsTable.size(); i++){
        if(Ucase(skill) == SkillsTable[i].skill){
            valid = true;
            for (int j = 0; j < skills.size(); j++){
                if(SkillsTable[i].skill == skills[j]){
                    found = true;
                    r = true;
                }
            }
        }
    }
    if((valid) and (not found) and Active()){
        skills.push_back(Ucase(skill));
        r = true;
    }

    return r;
}

void CreatureClass::Amnesia(){
    skills.clear();

    return;
}

int CreatureClass::InitiativeCheck()const{
    int rNum = 0;

    if(Active()){
        rNum = Dice::Roll(name,GameSpace::INIT,1,20) + AbilityMod(DEX);
    }

    return rNum;
}

int CreatureClass::Defense()const{
    int defNum = 0;

    if(Active() and HasArmor()){
        defNum = 10 + AbilityMod(DEX) + armor->Bonus();
    }else if(Active()){
        defNum = 10 + AbilityMod(DEX);
    }

    return defNum;
}

int CreatureClass::Damage()const{
    int damage = 0;

    if(Active() and HasWeapon()){
        if(WeaponClass::IsMelee(Weapon())){
            damage = weapon->Damage(name) + AbilityMod(STR);
        }else{
            damage = weapon->Damage(name);
        }
    }else if(Active() and not HasWeapon()){
        damage = AbilityMod(STR);
    }
    if(damage < 0){
        damage = 0;
    }

    return damage;
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
        for(int i = 0; i < STAT_COUNT; i++){
            statScores[i] = c.statScores[i];
        }
        delete weapon;
        if(c.weapon != NULL){
            weapon = new WeaponClass(c.weapon->EquipClass::Name());
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
