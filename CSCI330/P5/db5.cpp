//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 5
//db5.h CreatureDB
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#include "db5.h"

using namespace std;
using namespace GameSpace;

CreatureDB::CreatureDB * CreatureDB::db_instance = NULL;

CreatureDB::CreatureDB()
{
    
}

CreatureDB::CreatureDB * CreatureDB::GetDB()
{
    if(not db_instance){
        db_instance = new CreatureDB;
    }
    return db_instance;
}

void CreatureDB::DeleteDB()
{
    if(db_instance){
        delete db_instance;
        db_instance = NULL;
    }
    
    return;
}

bool CreatureDB::LoadDB(istream& inFile)
{
    char type;
    char voc;
    char trash;
    string name;
    int hp;
    int xp;
    bool r = false;

    inFile.get(type);
    while(not inFile.eof()){
        if(inFile){
            inFile >> trash;
            if(type == 'H' or type == 'E' or type == 'F' or type == 'O'){
                inFile.get(voc);
                inFile >> trash;
            }
            getline(inFile,name,'#');
            inFile >> hp;
            inFile >> trash;
            if(type == 'H' or type == 'E' or type == 'F' or type == 'O'){
                inFile >> xp;
                Add(MakeHumanoid(type,voc,name,hp,xp));
            }else{
                Add(MakeMonster(type,name,hp));
            }
            inFile.ignore(256,'\n');
            r = true;
        }
        inFile.get(type);
    }

    return r;
}

bool CreatureDB::DumpDB(ostream& out)
{
    bool r = false;
    
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        r = true;
        out << RaceToChar(it->second.Race()) << '#';
        if(it->second.IsHumanoid()){
            out << VocToChar(it->second.Voc()) << '#';
        }
        out << it->second.Name() << '#' << it->second.HP() << '#';
        if(it->second.IsHumanoid()){
            out << it->second.XP() << '#';
        }
        out << endl;
    }
    
    return r;
}

bool CreatureDB::Add(const Creature& creature)
{
	bool r = false;
	int initSize = creatureMap.size();
	creatureMap.insert(pair<const string,Creature>(creature.Name(),creature));
	if(creatureMap.size() > initSize){
		r = true;
	}

	return r;
}

bool CreatureDB::Remove(const string& creatureName)
{
    bool r = false;
    
    if(creatureMap.count(creatureName) > 0){
        creatureMap.erase(creatureName);
        r = true;
    }
    
    return r;
}

bool CreatureDB::Retrieve(const string& creatureName, Creature& creature) const
{
    bool r = false;
    if(creatureMap.count(creatureName) > 0){
        creature = creatureMap.at(creatureName);
        r = true;
    }
    
    return r;
}

void CreatureDB::MakeEmpty()
{
    creatureMap.clear();
    
    return;
}

bool CreatureDB::IsEmpty() const
{
    return (creatureMap.size() == 0);
}

int CreatureDB::HumanoidCount() const
{
    int humanoids = 0;
    
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        if(it->second.IsHumanoid()){
            humanoids++;
        }
    }
    
    return humanoids;
}

int CreatureDB::MonsterCount() const
{
    int monsters = 0;
    
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        if(it->second.IsMonster()){
            monsters++;
        }
    }
    
    return monsters;
}

int CreatureDB::EquipCount() const
{
    int equipNum = 0;
    vector<string> packVec;
    
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        if(it->second.HasWeapon()){
            equipNum++;
        }
        if(it->second.HasArmor()){
            equipNum++;
        }
        packVec = it->second.Pack();
        equipNum += packVec.size();
        packVec.clear();
    }
    
    return equipNum;
}

std::vector<string> CreatureDB::SortByName() const
{
    vector<string> creatureVec;
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        creatureVec.push_back(it->first);
    }
    sort(creatureVec.begin(), creatureVec.end());
    
    return creatureVec;
}

std::vector<string> CreatureDB::SortByXP() const
{
    vector<pair<string, int> > sortVec;
    vector<string> creatureVec;
    
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        sortVec.push_back(pair<string, int>(it->second.Name(), it->second.XP()));
    }
    
    return SortVector(sortVec);
}

std::vector<string> CreatureDB::SortByHP() const
{
    vector<pair<string, int> > sortVec;
    
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        sortVec.push_back(pair<string, int>(it->second.Name(), it->second.HP()));
    }
    
    return SortVector(sortVec);
}

const pair<const string, Creature>& CreatureDB::operator[](int index)
{
    cit = creatureMap.begin();

    if(index < 0){
    	throw BELOW_VALID_INDEX;
    }else if(index >= creatureMap.size()){
    	throw ABOVE_VALID_INDEX;
    }else{
    	for(int i = 0; i < index; i++){
        	cit++;
    	}
	}
    
    return *cit;
}

void CreatureDB::WriteAll(ostream& out) const
{
    for(map<const string, Creature>::const_iterator it = creatureMap.begin(); it != creatureMap.end(); it++){
        it->second.Write(out);
    }
    
    return;
}

Creature CreatureDB::MakeHumanoid(char race, char voc, string name, int hp, int xp)
{
    Creature c(name, CharToRace(race), CharToVoc(voc)); 
    
    InitEquipCreature(c);
    c.UpdateXP(xp - c.XP());
    c.UpdateHP(hp - c.HP());
    
    return c;
}

Creature CreatureDB::MakeMonster(char race, string name, int hp)
{
    Creature c(name, CharToRace(race));
    
    InitEquipCreature(c);
    c.UpdateHP(hp - c.HP());
    
    return c;
}

void CreatureDB::InitEquipCreature(Creature & c)
{
    vector<string> equipVec;
    
    equipVec = c.EquipInitialList();
    sort(equipVec.begin(), equipVec.end());
    for(int i = 0; i < equipVec.size(); i++){
        if(WeaponClass::IsEquipment(equipVec[i])){
            c.FindEquipment(new WeaponClass(equipVec[i]));
        }else if(ArmorClass::IsEquipment(equipVec[i])){
            c.FindEquipment(new ArmorClass(equipVec[i]));
        }
    }
    
    return;
}

ostream& operator<<(ostream& out,const CreatureDB* db)
{
    db->WriteAll(out);
    
    return out;
}

vector<string> SortVector(vector<pair<string, int> > v)
{
    vector<string> creatureVec;
    
    sort(v.begin(), v.end(), CompareValue);
    for(int i = v.size() - 1; i >= 0; i--){
        creatureVec.push_back(v[i].first);
    }
    reverse(creatureVec.begin(),creatureVec.end());
    
    return creatureVec;
}

bool CompareValue(pair<string, int> p_a, pair<string, int> p_b)
{
    return (p_a.second < p_b.second);
}

char RaceToChar(int race)
{
    char r;
    
    switch(race){
        case 0:
            r = 'H';
            break;
        case 1:
            r = 'E';
            break;
        case 2:
            r = 'F';
            break;
        case 3:
            r = 'O';
            break;
        case 4:
            r = 'T';
            break;
        case 5:
            r = 'G';
            break;
        default:
            r = '0';
    }
    
    return r;
}

char VocToChar(int voc)
{
    char r;
    
    switch(voc){
        case 1:
            r = 'B';
            break;
        case 2:
            r = 'C';
            break;
        case 3:
            r = 'F';
            break;
        case 4:
            r = 'R';
            break;
        case 5:
            r = 'W';
            break;
        default:
            r = '0';
    }
    
    return r;
}

Creature::RaceType CharToRace(char c)
{
    Creature::RaceType r;
    
    switch(c){
        case 'H':
            r = Creature::HUMAN;
            break;
        case 'E':
            r = Creature::ELF;
            break;
        case 'F':
            r = Creature::HALFELF;
            break;
        case 'O':
            r = Creature::ORC;
            break;
        case 'T':
            r = Creature::TROLL;
            break;
        case 'G':
            r = Creature::OGRE;
            break;
        default:
            r = Creature::HUMAN;
    }
    
    return r;
}

VocRules::VocType CharToVoc(char c)
{
    VocRules::VocType v;
    switch(c){
        case 'B':
            v = VocRules::BBN;
            break;
        case 'C':
            v = VocRules::CLR;
            break;
        case 'F':
            v = VocRules::FTR;
            break;
        case 'R':
            v = VocRules::ROG;
            break;
        case 'W':
            v = VocRules::WIZ;
            break;
        default:
            v = VocRules::FTR;
    }
    
    return v;
}


