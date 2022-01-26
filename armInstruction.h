#ifndef ARMINSTRUCTION_H
#define ARMINSTRUCTION_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include "IInstruction.h"


typedef struct INSTRUCTION {
    std::string operation;
    uint32_t op1;
    uint32_t op2;
    uint32_t op3;   //third operand is available if needed
} INSTRUCTION;

class ARM : public IInstruction {
    std::vector<INSTRUCTION> set;
    std::vector<uint32_t> result;
    uint32_t r[30];

protected:
    void parse(char[], uint32_t) override;
    std::string execute() override;
    std::string buildOutput();
    uint32_t hexStrToInt(std::string);
    std::string intToHexStr(uint32_t);
    bool isAlphaNum(char);
};

#endif //ARMINSTRUCITON_H