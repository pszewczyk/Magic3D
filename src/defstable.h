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
		std::map <std::string, std::string> Wartosci;
		std::map <std::string, CDefsTable*> Tabele;
        CDefsTable();
	public:
		CDefsTable(std::ifstream&);
		CDefsTable(std::string);
		~CDefsTable();

		bool loadData(std::ifstream&);
		int GetInt(const std::string, const int) const;
		float GetFloat(const std::string, const float) const;
		bool GetBool(const std::string, const bool = true) const;
		std::string GetString(const std::string, const std::string = "error") const;
		CDefsTable* GetTable(const std::string) const;
		std::vector <std::string> GetList(const std::string, char = ',') const;
		std::vector <int> GetIntList(const std::string, char = ',') const;
		std::vector <std::string> GetTabeleK() const;
		std::vector <CDefsTable*> GetTabele() const;
		std::vector <std::string> GetWartosci() const;
		std::vector <std::string> GetRealWartosci() const;
		std::map<std::string, int> GetIntMap(const std::string) const;
		
		std::string GetSource() const;
};

#endif
