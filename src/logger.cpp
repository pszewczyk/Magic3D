#include "logger.h"

MLogger::MLogger(string filename) {
    aut.open(filename.c_str());
}

MLogger::~MLogger() {
    aut.close();
}

void MLogger::Error(string text) {
    aut<<"ERROR: "<<text<<"\n";
    cout<<"ERROR: "<<text<<"\n";
}

void MLogger::Print(string text) {
    aut<<text<<"\n";
    cout<<text<<"\n";
}
