//Kai Jungbluth
//CSCI330-002
//Fall 2016
//Program 5
//db5.h CreatureDB
//Helped By: Zachary Gransbury, Chris Persinger, Troy Beauchat.
//Helped: Zachary Gransbury, Chris Persinger, Troy Beauchat.

#ifndef DB5_DOT_H
#define DB5_DOT_H

#include <utility>
#include "handle4.h"


using namespace std;
using namespace GameSpace;

class CreatureDB
{
	public:
		enum ExceptionType{BELOW_VALID_INDEX, ABOVE_VALID_INDEX};
		//Excetions thrown if index is bad.

        static CreatureDB * db_instance;
        //Instance pointer
        
		static CreatureDB * GetDB();
		//Returns the database.
		//Pre: None.
		//Post: Returns the instance of CreatureDB.

		static void DeleteDB();
		//Deletes instance of the database.
		//Pre: None.
		//Post: The instance of the database is deleted.

		bool LoadDB(istream& inFile);
		//Loads data into database.
		//Pre: None.
		//Post: Returns true if at least one creature is loaded.
		
		bool DumpDB(ostream& out);
		//Dumps database into output stream.
		//Pre: None.
		//Post: Returns true if at least one creature is dumped to the file.

		bool Add(const Creature& creature);
		//Adds creature to database.
		//Pre: None.
		//Post:  Returns true if creature is added, false otherwise.

		bool Remove(const string& creatureName);
		//Removes creature from the database.
		//Pre: None.
		//Post: Returns true if creature is found and deleted, false otherwise.

		bool Retrieve(const string& creatureName, Creature& creature) const;
		//Retreives creature from database.
		//Pre: None.
		//Post: Returns true if retrieved, false otherwise.

		void MakeEmpty();
		//Removes all creatures from the database.
		//Pre: None.
		//Post: All creatures are removed from the database.

		bool IsEmpty() const;
		//Checks if the database is empty.
		//Pre: None.
		//Post: Returns true if database is empty, false otherwise.

		int HumanoidCount() const;
		//Returns the number of humanoids in the database.
		//Pre: None.
		//Post: The number of humanoids is returned.
		

		int MonsterCount() const;
		//Returns the number of monsters in the database.
		//Pre: None.
		//Post: The number of monsters is returned.

		int EquipCount() const;
		//Narrative: Returns the number of equipment held by creatures in the database.
		//Pre-condition: None.
		//Post-condition: The number of equipment is returned.

		std::vector<string> SortByName() const;
		//Returns alphabetically sorted vector of creature names.
		//Pre: None.
		//Post: Returns vector of creatures sorted by name.

		std::vector<string> SortByXP() const;
		//Returns vector of creature names sorted by XP.
		//Pre: None.
		//Post: Returns vector of creatures sorted by XP.

		std::vector<string> SortByHP() const;
		//Returns vector of creature names sorted by HP.
		//Pre: None.
		//Post: Returns vector of creatures sorted by HP.

		const pair<const string, Creature>& operator[](int index);
		//Narrative: Overloads subscript operator.
		//Pre-condition: None.
		//Post-condition: Retrieves map entry by sequential location.

		//pair<string, Creature> & operator[](int i);
		//Don't implement
        
        void WriteAll(ostream& out) const;
        //Calls write function of every creature in database
        //Pre: None.
		//Post: Prints all creatures.
        
	private:
		std::map<const string, Creature> creatureMap;
		//Creature map.

		map<const string, Creature>::const_iterator cit;
		//constant iterator.
        
        CreatureDB();
        //Default constructor.
        
        Creature MakeHumanoid(char race, char voc, string name, int hp, int xp);
        //Helper function that creates a humanoid.
        //Pre: None.
        //Post: New humanoid is returned.
        
        Creature MakeMonster(char race, string name, int hp);
        //Helper function that creates a monster.
        //Pre: None.
        //Post: New monster is returned.
        
        void InitEquipCreature(Creature & c);
        //Equipts creature with initial equipment.
        //Pre: None.
        //Post: Creature is equipped with initial equipment.
};

ostream& operator<<(ostream& out,const CreatureDB* db);
//Outputs the contents of the database.
//Pre: None.
//Post: A statement is outputted displaying the creatures characteristics in the database.

bool CompareValue(pair<string, int> p_a, pair<string, int> p_b);
//Helper function used in sorting.
//Pre: None.
//Post: Compares the value of two pairs.

vector<string> SortVector(vector<pair<string, int> > v);
//Helper function that sorts a vector of pairs by value.
//Pre: None.
//Post: Returns a sorted vector.

char RaceToChar(int race);
//Helper function that returns race as a char.
//Pre: None.
//Post: Char corresponding to entered race is returned.

char VocToChar(int voc);
//Helper function that returns voc as a char.
//Pre: None.
//Post: Char corresponding to entered voc is returned.

Creature::RaceType CharToRace(char c);
//Helper function that converts a char to a racetype.
//Pre: None.
//Post: Returns corresponding racetype.

VocRules::VocType CharToVoc(char c);
//Helper function that converts a char to a voctype.
//Pre: None.
//Post: Returns corresponding voctype.

#endif
