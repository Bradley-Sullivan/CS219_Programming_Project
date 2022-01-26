#ifndef INSTRUCTIONLOADER_H
#define INSTRUCTIONLOADER_H

#include <iostream>
#include <fstream>
#include "IInstruction.h"

class InstructionLoader {
    IInstruction* i;
    std::string filename, exeOutput;
    char* buffer;
    uint32_t bufSize;

public:
    InstructionLoader(IInstruction* x, std::string y) : i{x}, filename{y} {};
    ~InstructionLoader() { delete buffer; }
    int load();
    int save(std::string);
    std::string execute();

};

#endif //INSTRUCTIONLOADER_H