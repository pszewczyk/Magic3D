// MRPG Defs Table Header
#ifndef DEFSTABLE_H
#define DEFSTABLE_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "config.h"

//using std::string;
//using std::ifstream;
//using std::vector;
//using std::map;

class CDefsTable
{
	private:
		map <string, string> Wartosci;
		map <string, CDefsTable*> Tabele;
        CDefsTable();
	public:
		CDefsTable(ifstream&);
		CDefsTable(string);
		~CDefsTable();

		bool loadData(ifstream&);
		int GetInt(const string, const int) const;
		float GetFloat(const string, const float) const;
		bool GetBool(const string, const bool = true) const;
		string GetString(const string, const string = "error") const;
		CDefsTable* GetTable(const string) const;
		vector <string> GetList(const string, char = ',') const;
		vector <int> GetIntList(const string, char = ',') const;
		vector <string> GetTabeleK() const;
		vector <CDefsTable*> GetTabele() const;
		vector <string> GetWartosci() const;
		vector <string> GetRealWartosci() const;
		map<string, int> GetIntMap(const string) const;
		
		string GetSource() const;
};

#endif
