/*
primitives.h - proste klasy, np wektory
*/

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <math.h>
#include "config.h"

class Mvector3d
{
public:
       //wspó³rzêdne
       double x;
       double y;
       double z;
       //konstruktory
       Mvector3d();
       Mvector3d(double, double, double);
       //operacje arytmetyczne:
       virtual void translate(Mvector3d); //translacja
       Mvector3d operator + (Mvector3d); //suma
       Mvector3d operator - (Mvector3d); //ró¿nica
       Mvector3d operator * (Mvector3d); //iloczyn wektorowy
       Mvector3d operator * (float);       //mno¿enie przez skalar
       double operator % (Mvector3d);       //iloczyn skalarny
       Mvector3d operator / (Mvector3d);       //iloczyn skalarny
       //inne funkcje
       double length();                       //d³ugoœæ wektora
       Mvector3d normalize();              //zwraca wektor znormalizowany (d³ugoœæ 1, kierunek i zwrot ten sam)
       Mvector3d anty();
};

double cosangle3d(Mvector3d a, Mvector3d b);

#endif
