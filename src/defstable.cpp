// MRPG Defs Table CPP

#include <fstream>
#include <map>

#include "defstable.h"
#include "io.h"
#include "strings.h"

CDefsTable* EmptyDef;

CDefsTable::CDefsTable()
	: Wartosci()
	, Tabele()
{
}

CDefsTable::CDefsTable(ifstream &b) 
	: Wartosci()
	, Tabele()
{
	loadData(b);
}

CDefsTable::CDefsTable(string filename) 
	: Wartosci()
	, Tabele()
{
	ifstream b;
	b.open(filename.c_str(),ifstream::in);
	if(!b) {
        printf("file %s could not be opened\n", filename.c_str());
    }
	loadData(b);
	b.close();
}

bool CDefsTable::loadData(ifstream &b)
{
	if(!b)
	{
		Error("CDefsTable: Zamkniety ifstream");
		return false;
	}
	string k, v = "", t = "";
	unsigned int d, e = 0;
	bool u = 1;
	char mander[1337];
	while(u)
	{
		if(b.eof()) return true;
		b >> t;
		while(!t.empty())
		{
			if(t.size() > 1)
			{
				if((t[0] == '/') && (t[1] == '/'))
				{
					b.getline(mander, 1337);
					t = "";
				}
			}
			if(!e && !t.empty() && (t[0] == '}'))
			{
				return true;
			}
			d = t.size();
			if(!d) continue;
			if(e < 2)
			{
				if(e && (t[0] == '='))
				{
					t = t.substr(1, d-1);
					d = t.size();
					e = 2;
				}
				else
				{
					if(e && (t[0] != '='))
					{
						Error("DefsTable: syf: " + k);
					}
					for(unsigned int i = 0; i < d; ++i)
					{
						if(t[i] == '=')
						{
							k = t;
							k.resize(i);
							t = t.substr(i+1, d-i-1);
							d = t.size();
							e = 2;
							break;
						}
					}
				}
				if(e != 2)
				{
					k = t;
					t = "";
					d = 0;
					e = 1;
				}
			}
			if(t.size() > 1)
			{
				if((t[0] == '/') && (t[1] == '/'))
				{
					b.getline(mander, 1337);
					t = "";
				}
			}
			if((e == 2) && !t.empty())
			{
				if(t[0] == '{')
				{
					k = Lowercase(k);
					if(Tabele.find(k) != Tabele.end())
					{
						Error("DefsTable: tabela " + k + " juz jest");
						delete Tabele[k];
					}
					Tabele[k] = new CDefsTable(b);
					t = "";
					v = "";
					e = 0;
				}
				else
				{
					for(unsigned int i = 0; i < d; ++i)
					{
						if(t[i] == ';')
						{
							d = v.size();
							v += t;
							v.resize(i + d);
							k = Lowercase(k);
							Wartosci[k] = v;
							v = "";
							t = t.substr(i+1, d-i+1);
							e = 0;
							break;
						}
					}
					if(e)
					{
						v += t + ' ';
						t = "";
					}
				}
			}
		}
	}
	return true;
}

CDefsTable::~CDefsTable()
{
	for(map <string, CDefsTable*>::iterator i = Tabele.begin(); i != Tabele.end(); ++i)
	{
		delete i->second;
	}
}

int CDefsTable::GetInt(string a, const int b) const
{
	a = Lowercase(a);
	if(Wartosci.find(a) == Wartosci.end()) return b;
	string c = Wartosci.find(a)->second;
	return StrToInt(c);
}

float CDefsTable::GetFloat(string a, const float b) const
{
	a = Lowercase(a);
	if(Wartosci.find(a) == Wartosci.end()) return b;
	string c = Wartosci.find(a)->second;
	unsigned int d = c.size();
	unsigned int i = 0;
	bool minus = 0;
	bool kropka_jest = 0;
	unsigned int kropka = 0;
	int e = 0;
	if(c[0] == '-')
	{
		minus = 1;
		++i;
	}
	else if(c[0] == '+')
	{
		++i;
	}
	for(; i < d; ++i)
	{
		if(c[i] == 32)
		{
			continue;
		}
		if((c[i] > 47) && (c[i] < 58))
		{
			e = 10*e + c[i] - 48;
			if(kropka_jest) ++kropka;
		}
		else if((c[i] == '.') || (c[i] == ','))
		{
			if(kropka_jest) return b;
			kropka_jest = 1;
		}
		else return b;
	}
	d = 1;
	for(i = 0; i < kropka; ++i)
	{
		d *= 10;
	}
	float f = float(e)/d;
	return (minus ? (-f) : f);
}

string CDefsTable::GetString(string a, const string b) const
{
	a = Lowercase(a);
	if(Wartosci.find(a) == Wartosci.end()) return b;
	else return Wartosci.find(a)->second;
}

bool CDefsTable::GetBool(string a, bool b) const
{
    a = Lowercase(a);
    if(Wartosci.find(a) == Wartosci.end()) return b;
	else return Wartosci.find(a)->second=="true";
}

vector<string> CDefsTable::GetList(string a, char inter) const{
    vector<string> result;
    string all;
    all = GetString(a);
    string buffer = "";
    for(int i=0; i<all.size(); i++) {
        if(all[i]==inter) {
            result.push_back(buffer);
            buffer = "";
            continue;
        }
        buffer += all[i];
    }
    result.push_back(buffer);
    return result;
}

vector<int> CDefsTable::GetIntList(string a, char inter) const{
    vector<string> exploded = GetList(a, inter);
    vector<int> result;
    for(int i=0; i<exploded.size(); i++) {
        result.push_back(StrToInt(exploded[i]));
    }
    return result;
}

CDefsTable* CDefsTable::GetTable(string a) const
{
	a = Lowercase(a);
	if(Tabele.find(a) == Tabele.end()) return EmptyDef;
	else return Tabele.find(a)->second;
}

vector <string> CDefsTable::GetWartosci() const
{
	vector <string> a;
	for(map <string, string>::const_iterator i = Wartosci.begin(); i != Wartosci.end(); ++i)
	{
		a.push_back(i->first);
	}
	return a;
}

vector <string> CDefsTable::GetRealWartosci() const
{
	vector <string> a;
	for(map <string, string>::const_iterator i = Wartosci.begin(); i != Wartosci.end(); ++i)
	{
		a.push_back(i->second);
	}
	return a;
}

vector <string> CDefsTable::GetTabeleK() const
{
	vector <string> a;
	for(map <string, CDefsTable*>::const_iterator i = Tabele.begin(); i != Tabele.end(); ++i)
	{
		a.push_back(i->first);
	}
	return a;
}

vector <CDefsTable*> CDefsTable::GetTabele() const
{
	vector <CDefsTable*> a;
	for(map <string, CDefsTable*>::const_iterator i = Tabele.begin(); i != Tabele.end(); ++i)
	{
		a.push_back(i->second);
	}
	return a;
}

map<string, int> CDefsTable::GetIntMap(string a) const
{
    map<string, int> result;
    CDefsTable* def = GetTable(a);
    vector<string> v = def->GetWartosci();
    printf("bla\n");
    for(int i=0; i<v.size(); i++) {
        result[v[i]] = def->GetInt(v[i], 0);
    }
    return result;
}


string CDefsTable::GetSource() const {
    string result;
    //for(map <string, CDefsTable*>::const_iterator i = Tabele.begin(); i != Tabele.end(); ++i)
    //for(map <string, CDefsTable*>::const_iterator i = Tabele.begin(); i != Tabele.end(); ++i) 
    return result;
}
