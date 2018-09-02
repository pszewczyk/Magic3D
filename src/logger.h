#ifndef MLOGGER_H
#define MLOGGER_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include "config.h"

class MLogger{
private:
    std::ofstream aut;
public:
    MLogger(std::string filename);
    ~MLogger();
    void Error(std::string text);
    void Print(std::string text);
};

#endif
