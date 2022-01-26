#include <iostream>
#include <vector>
#include <math.h>
#include "IInstruction.h"


typedef struct INSTRUCTION {
    std::string operation;
    uint32_t op1;
    uint32_t op2;
    uint32_t op3;
} INSTRUCTION;

class ARM : public IInstruction {
    std::vector<INSTRUCTION> set;
    std::vector<uint32_t> result;

protected:
    void parse(char[], uint32_t) override;
    void execute() override;
    uint32_t hexStrToInt(std::string);
    std::string intToHexStr(uint32_t);
    bool isAlphaNum(char);
};