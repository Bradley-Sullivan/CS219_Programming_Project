/**
 * @file instructionHandler.h
 * @author Bradley Sullivan (bradleysullivan@nevada.unr.edu)
 * @brief Defines the InstructionHandler class
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

typedef struct INSTRUCTION {
    std::string operation;
    uint32_t op1;
    uint32_t op2;
} INSTRUCTION;

class InstructionHandler {
    std::vector<INSTRUCTION> set;
    std::vector<uint32_t> result;

public:
    int load(std::string);
    void parse(char[], uint32_t);
    void execute(INSTRUCTION);
    uint32_t hexStrToInt(std::string);
    std::string intToHexStr(uint32_t);
    bool isAlphaNum(char);

    friend std::ostream &operator<< (std::ostream &out, const INSTRUCTION &inst);
    
    void printOutput();
    
};