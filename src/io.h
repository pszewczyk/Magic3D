// MRPG Input/Output Header & stringi
#ifndef IO_H
#define IO_H

#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <stack>
#include "config.h"

void Error(const std::string);
std::string Lowercase(const std::string a);
std::string Uppercase(const std::string a);
std::wstring StrToWstr(const std::string s);
int StrToInt(const std::string s);
std::string IntToStr(int);
std::string BreakLines(const std::string s, int a=30);
std::string RandomString(int a=4);

char getcz();

#endif
