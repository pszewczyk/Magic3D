// MRPG Input/Output Header & stringi
#ifndef IO_H
#define IO_H

#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <stack>
#include "config.h"

void Error(const string);
string Lowercase(const string a);
string Uppercase(const string a);
wstring StrToWstr(const string s);
int StrToInt(const string s);
string IntToStr(int);
string BreakLines(const string s, int a=30);
string RandomString(int a=4);

char getcz();

#endif
