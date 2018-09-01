#include "primitives.h"

Mvector3d::Mvector3d()
	: x(0)
	, y(0)
	, z(0)
{
}
Mvector3d::Mvector3d(double a, double b, double c)
	: x(a)
	, y(b)
	, z(c)
{
}

Mvector3d Mvector3d::operator + (Mvector3d a)
{
 return Mvector3d(x + a.x, y + a.y, z + a.z);
}

void Mvector3d::translate(Mvector3d a)
{
 x += a.x;
 y += a.y;
 z += a.z;
}

Mvector3d Mvector3d::operator - (Mvector3d a)
{
 return Mvector3d(x - a.x, y - a.y, z - a.z);
}

Mvector3d Mvector3d::operator * (float a)
{
 return Mvector3d(a * x, a * y, a * z);
}

double Mvector3d::operator % (Mvector3d a)
{
 return (x * a.x) + (y * a.y) + (z * a.z);
}

Mvector3d Mvector3d::operator / (Mvector3d a)
{
 return Mvector3d(x * a.x, y * a.y, z * a.z);
}

Mvector3d Mvector3d::operator * (Mvector3d a)
{
 return Mvector3d((y * a.z) - (z * a.y), (z * a.x) - (x * a.z), (x * a.y) - (y * a.z));
}

double Mvector3d::length()
{
 return sqrt(x*x + y*y + z*z);
}

Mvector3d Mvector3d::normalize()
{
 float L = length(); // wielkie L bo male wyglada jak 1
 if(L == 0) return Mvector3d(x, y, z);
 return Mvector3d(x/L, y/L, z/L);
}

Mvector3d Mvector3d::anty()
{
 return Mvector3d(-x, -y, -z);
}

double cosangle3d(Mvector3d a, Mvector3d b)
{
 if((a.length() != 0) && (b.length() != 0)) return (a % b) / (a.length() * b.length());
 else return 0;
}
