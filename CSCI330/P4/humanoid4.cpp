//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 4
//humanoid.cpp
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#include "humanoid4.h"

using namespace std;
using namespace GameSpace;

const int Humanoid::BASE_LEVEL = 1;
const int Humanoid::MIN_GP = 0;
const int Humanoid::MIN_XP = 0;
const int Humanoid::BASE_HP = 1;
const std::string Humanoid::DEFAULT_SKILLS[VocRules::VOC_MAX][SKILL_COUNT] = {/*NNE*/{"","",""},
                                                     	/*BBN*/{"CLIMB","LISTEN","SWIM"},
                                                     	/*CLR*/{"HEAL","USE MAGIC DEVICES",""},
                                                     	/*FTR*/{"INTIMIDATE","SWIM",""},
                                                     	/*ROG*/{"BLUFF","CLIMB","HIDE"},
                                                 		/*WIZ*/{"CONCENTRATION","HIDE",
                                                                "USE MAGIC DEVICES"}};


Humanoid::Humanoid()
{

}

Humanoid::Humanoid(string newName, VocRules::VocType newVoc, VocRules::VocType defVoc, const int abilAdj[]): CreatureClass(newName)
{
    SetVoc(newVoc,defVoc);
    SetStats(abilAdj);
    SetSkills();
}
       
Humanoid::Humanoid(const Humanoid & h): CreatureClass(h)
{
    CopyHumanoid(h);
}   

void Humanoid::CopyHumanoid(const Humanoid & h){
    voc = h.voc;
    WeaponClass * wpn = NULL;
    ArmorClass * amr = NULL;

    for(int i = 0; i < HSTAT_COUNT; i++){
        hStats[i] = h.hStats[i];
    }
    for(int j = 0; j < h.pack.size(); j++){
        wpn = dynamic_cast<WeaponClass*>(h.pack[j]);
        amr = dynamic_cast<ArmorClass*>(h.pack[j]);
        if(wpn){
            pack.push_back(new WeaponClass(wpn->Name()));
        }else if(amr){
            pack.push_back(new ArmorClass(amr->Name()));
        }
    }

    return;
}

Humanoid::~Humanoid(){
    while(not pack.empty()){
        if(pack[0]){
            delete pack[0];
        }
        pack.erase(pack.begin());
    }
}

void Humanoid::SetVoc(VocRules::VocType newVoc, VocRules::VocType defVoc)
{
    if(newVoc > VocRules::WIZ or newVoc < VocRules::NNE){
        throw INVALID_VOC;
    }else if(newVoc == VocRules::NNE){
        voc = defVoc;
    }else{
        voc = newVoc;
    }
    
    
    return;
}   

void Humanoid::SetStats(const int abilAdj[]){
    VocRules::VocRules * vPtr;
    vPtr = VocRules::GetVocRules();
    RollType r;
    int diceNum,
        rollHP,
        initStats[VocRules::VOC_MAX];
    for(int i = DEX; i <= WIS; i++){
            r = (RollType)i;
            initStats[i] = Dice::Roll(Name(),r,3,6) + abilAdj[i];
    }
    CreatureClass::SetStats(initStats);
    diceNum = vPtr->VocRules::HitDie(voc);
    rollHP = Dice::Roll(Name(),GameSpace::HP,1,diceNum) + AbilityMod(CON);
    if(rollHP < BASE_HP){
        rollHP = BASE_HP;
    }
    SetHP(rollHP);
    hStats[EXP] = MIN_XP;
    hStats[EGP] = Dice::Roll(Name(),GameSpace::GP,1,4);
    hStats[LEVEL] = BASE_LEVEL;
    vPtr->VocRules::DeleteVocRules();

    return;
}

void Humanoid::SetSkills(){
    string initSkills[SKILL_COUNT];

    for(int i = 0; i < SKILL_COUNT; i++){
        initSkills[i] = DEFAULT_SKILLS[voc][i];
    }
    CreatureClass::SetSkills(initSkills,SKILL_COUNT);

    return;
}    

void Humanoid::Write(ostream& out)const{
    vector<string> skillVec = Skills();
    vector<string> packVec = Pack();

    out << Voc_Str() << "#"
        << Name() << "#("
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
        << endl 
        << '\t' 
        << Level() << "#"
        << XP() << "#"
        << GP() << "#(";
    for(int j = 0; j < packVec.size(); j++){
        if(j != packVec.size() - 1){
            out << packVec[j] << ",";
        }else{
            out << packVec[j];
        }
    }
    out << ")#"
        << endl;
}

int Humanoid::Voc()const{
	return voc;
}

string Humanoid::Voc_Str()const{
    return VocRules::VocToStr(voc);
}

int Humanoid::Level()const{
    return (int)hStats[LEVEL];
}

long Humanoid::XP()const{
    return hStats[EXP];
}

long Humanoid::GP()const{
    return hStats[EGP];
}

std::vector<std::string> Humanoid::Pack()const{
    std::vector<string> rVec;

    for(int i = 0; i < pack.size(); i++){
        rVec.push_back(pack[i]->Name());
    }
    sort(rVec.begin(), rVec.end());

    return rVec;
}

std::vector<std::string> Humanoid::EquipInventory()const{
    std::vector<string> inventory;

    for(int i = 0; i < pack.size(); i++){
        inventory.push_back(pack[i]->Name());
    }

    if(HasWeapon()){
        inventory.push_back(Weapon());
    }
    if(HasArmor()){
        inventory.push_back(Armor());
    }

    return inventory;
}

long Humanoid::UpdateGP(int value){
    long result = hStats[EGP] + value;
    
    if(result >= MIN_GP){
        hStats[EGP] += value;
    }
    
    return hStats[EGP];
}

long Humanoid::UpdateXP(int value){
    VocRules::VocRules * vPtr;
    vPtr = VocRules::GetVocRules();
    int addedHP = 0;
    
    if(value >= MIN_XP){
        int diceNum = vPtr->VocRules::HitDie(voc);
        hStats[EXP] += value;
        while(hStats[EXP] >= VocRules::XPforPromotion(hStats[LEVEL]+1)
        and hStats[LEVEL] < VocRules::LEVEL_MAX){
            hStats[LEVEL]++;
            addedHP = Dice::Roll(Name(),GameSpace::HP,1,diceNum) + AbilityMod(CON);
            if(addedHP >= 1){
                UpdateHP(addedHP);
            }else{
                UpdateHP(1);
            }            
        }
    }
    vPtr->VocRules::DeleteVocRules();
    
    return hStats[EXP];
}

EquipClass::EquipClass * Humanoid::FindEquipment(EquipClass * equipment){
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


WeaponClass::WeaponClass * Humanoid::FindWeapon(WeaponClass * wpn){
    WeaponClass::WeaponClass * tmp = NULL;
    
    tmp = CreatureClass::FindWeapon(wpn);
    if(tmp and Active()){
        pack.push_back(tmp);
        tmp = NULL;
    }
    
    return tmp;
}


ArmorClass::ArmorClass * Humanoid::FindArmor(ArmorClass * amr){
    ArmorClass::ArmorClass * tmp = NULL;
    
    tmp = CreatureClass::FindArmor(amr);
    if(tmp and Active()){
        pack.push_back(tmp);
        tmp = NULL;
    }
    
    return tmp;
}


bool Humanoid::ChangeEquipment(string equipName){
    bool r = false;
    bool found = false;
    int pos;
    EquipClass * tmp = NULL;

    for(int i = 0; i < pack.size(); i++){
        if(Ucase(equipName) == pack[i]->Name()){
            found = true;
            pos = i;
        }
    }
    if(not found and (Ucase(equipName) == Weapon() or Ucase(equipName) == Armor())){
        r = true;
    }

    if(Active() and found){
        tmp = FindEquipment(pack[pos]);
        pack.erase(pack.begin() + pos);
        r = true;
    }

    return r;
}


EquipClass::EquipClass * Humanoid::BuyEquipment(EquipClass * equipment){
    EquipClass * tmp = NULL;
    int totalGp;

    if(equipment and GP() >= equipment->Cost() and Active()){
        totalGp = UpdateGP(-(equipment->Cost()));
        tmp = FindEquipment(equipment);
    }else{
        tmp = equipment;
    }

    return tmp;
}


EquipClass::EquipClass * Humanoid::SellEquipment(string equipment){
    bool foundInPack = false;
    int pos;
    int totalGp;
    EquipClass * tmp = NULL;

    if(Active()){
        for(int i = 0; i < pack.size(); i++){
            if(Ucase(equipment) == pack[i]->Name()){
                foundInPack = true;
                pos = i;
            }
        }
        if(foundInPack){
            totalGp = UpdateGP(pack[pos]->Cost());
            tmp = pack[pos];
            pack.erase(pack.begin() + pos);
        }else if(Weapon() == Ucase(equipment)){
            totalGp = UpdateGP(WeaponClass::LookUpCost(equipment));
            tmp = LoseWeapon();
        }else if(Armor() == Ucase(equipment)){
            totalGp = UpdateGP(ArmorClass::LookUpCost(equipment));
            tmp = LoseArmor();
        }
    }

    return tmp;
}


int Humanoid::AttackRoll()const{
    int rNum = 0;

    if(Active()){
        rNum = Dice::Roll(Name(),GameSpace::ATT,1,20) + AttackBonus();
    }

    return rNum;
}

int Humanoid::AttackBonus()const{
    int attBonus = 0;
    VocRules::VocRules * vPtr;
    vPtr = VocRules::GetVocRules();

    
    if(WeaponClass::IsRange(Weapon())){
        attBonus = vPtr->VocRules::BaseAttackBonus(voc,hStats[LEVEL]) + AbilityMod(DEX);
    }else{
        attBonus = vPtr->VocRules::BaseAttackBonus(voc,hStats[LEVEL]) + AbilityMod(STR);
    }
    
    vPtr->VocRules::DeleteVocRules();

    return attBonus;
}

int Humanoid::SavingThrow(SavingThrowType s)const{
    int bonus = 0;
    VocRules::VocRules * vPtr;
    vPtr = VocRules::GetVocRules();
    
    if(Active()){
        switch(s){
            case FORT:
                bonus = vPtr->VocRules::BaseSaveBonus(voc,hStats[LEVEL], FORT) + AbilityMod(CON);
                break;
            case REFLEX:
                bonus = vPtr->VocRules::BaseSaveBonus(voc,hStats[LEVEL], REFLEX) + AbilityMod(DEX);
                break;
            case WILL:
                bonus = vPtr->VocRules::BaseSaveBonus(voc,hStats[LEVEL], WILL) + AbilityMod(WIS);
                break;
            default:
                throw INVALID_SAVINGTHROW;
                break;
        }
    }
    vPtr->VocRules::DeleteVocRules();

    return (Dice::Roll(Name(),GameSpace::SVTH,1,20)) + bonus;
}

Humanoid & Humanoid::operator=(const Humanoid & h){
    if(this != &h){
        CreatureClass::operator=(h);
        CopyHumanoid(h);
    }

    return * this;
}
