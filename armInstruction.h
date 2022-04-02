/**
 * @file armInstruction.h
 * @author Bradley Sullivan (bradleysullivan@nevada.unr.edu)
 * @brief Defines the ARM instruction class. Responsible for parsing, executing,
 *        converting hex <-> decimal, and returning execution output
 * @version 0.1
 * @date 2022-01-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
    uint32_t op[3];
    int opCt;
    bool overflow, regVal[3];
} INSTRUCTION;

class ARM : public IInstruction {
    std::vector<INSTRUCTION> set;
    std::vector<uint32_t> result;
    uint32_t r[8];

protected:
    void parse(char[], uint32_t) override;
    std::string execute() override;
private:
    std::string buildOutput();
    uint32_t hexStrToInt(std::string);
    std::string intToHexStr(uint32_t);
    bool isAlphaNum(char);
    uint32_t getRegIdx(char[], int);
    bool MSBChk(uint32_t);
    void clrInst(INSTRUCTION&);
public:
    ARM();
};

#endif //ARMINSTRUCITON_H