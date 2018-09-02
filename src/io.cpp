// MRPG Input/Output CPP

#include "io.h"
#include <fstream>

//#include <windows.h>
//#include <conio.h>

using namespace std;

void Error(const std::string message)
{
	printf("ERROR: %s!\n", message.c_str());
}

std::string Lowercase(const std::string a)
{
	std::string b = a;
	for(unsigned int i=0; i<b.size(); ++i)
	{
		if((b[i] > 64) && (b[i] < 92)) b[i] += 32;
	}
	return b;
}

std::string Uppercase(const std::string a)
{
	std::string b = a;
	for(unsigned int i=0; i<b.size(); ++i)
	{
		if((b[i] > 96) && (b[i] < 124)) b[i] -= 32;
	}
	return b;
}

std::wstring StrToWstr(const std::string s)
{
    std::wstring tmp;
    for( unsigned i = 0; i < s.length(); i++ )
    {
        if( s[ i ] == '¹' ) tmp += 0x0105;
        else if( s[ i ] == 'æ' ) tmp += 0x0107;
        else if( s[ i ] == 'ê' ) tmp += 0x0119;
        else if( s[ i ] == '³' ) tmp += 0x0142;
        else if( s[ i ] == 'ñ' ) tmp += 0x0144;
        else if( s[ i ] == 'ó' ) tmp += 0x00F3;
        else if( s[ i ] == 'œ' ) tmp += 0x015B;
        else if( s[ i ] == 'Ÿ' ) tmp += 0x017A;
        else if( s[ i ] == '¿' ) tmp += 0x017C;
        else if( s[ i ] == '¥' ) tmp += 0x0104;
        else if( s[ i ] == 'Æ' ) tmp += 0x0106;
        else if( s[ i ] == 'Ê' ) tmp += 0x0118;
        else if( s[ i ] == '£' ) tmp += 0x0141;
        else if( s[ i ] == 'Ñ' ) tmp += 0x0143;
        else if( s[ i ] == 'Ó' ) tmp += 0x00D3;
        else if( s[ i ] == 'Œ' ) tmp += 0x015A;
        else if( s[ i ] == '' ) tmp += 0x0179;
        else if( s[ i ] == '¯' ) tmp += 0x017B;
        else tmp += s[ i ];
        
    }
    return tmp;
}

int StrToInt(const std::string c)
{
    unsigned int d = c.size();
	unsigned int i = 0;
	bool minus = 0;
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
		if(c[i] == 32) continue;
		if((c[i] < 48) || (c[i] > 57)) continue;  //trudno, bedziemy pomijaæ syf
		else e = 10*e + c[i] - 48;
	}
	return (minus ? (-e) : e);
}

std::string IntToStr(int n) {
    std::string tmp, ret;
     if(n < 0) {
          ret = "-";
          n = -n;
     }
     do {
          tmp += n % 10 + 48;
          n -= n % 10;
     }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
          ret += tmp[i];
     return ret;
}

std::string BreakLines(const std::string s, int a) {
    int c=0;
    std::string result;
    for(int i=0; i<s.size(); i++) {
        c++;
        result+=s[i];
        if(c>=a) {
            result+="\n";
            c = 0;
        }
    }
    return result;
}


std::string RandomString(int a) {
    std::string result(a,'#');
    for(int i=0; i<a; i++) {
        result[i] = rand()%('Z'-'A')+'A';
    }
    return result;
}
