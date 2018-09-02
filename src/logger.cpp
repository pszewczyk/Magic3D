#include "logger.h"

MLogger::MLogger(std::string filename) {
    aut.open(filename.c_str());
}

MLogger::~MLogger() {
    aut.close();
}

void MLogger::Error(std::string text) {
    aut<<"ERROR: "<<text<<"\n";
    std::cout<<"ERROR: "<<text<<"\n";
}

void MLogger::Print(std::string text) {
    aut<<text<<"\n";
    std::cout<<text<<"\n";
}
