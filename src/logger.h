#ifndef MLOGGER_H
#define MLOGGER_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include "config.h"

class MLogger{
private:
    ofstream aut;
public:
    MLogger(string filename);
    ~MLogger();
    void Error(string text);
    void Print(string text);
};

#endif
