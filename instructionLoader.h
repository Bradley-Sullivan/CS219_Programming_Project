/**
 * @file instructionLoader.h
 * @author Bradley Sullivan (bradleysullivan@nevada.unr.edu)
 * @brief Defines the InstructionLoader class. Responsible for reading instruction sets,
 *        writing execution output, and returning execution output.
 * @version 0.1
 * @date 2022-01-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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