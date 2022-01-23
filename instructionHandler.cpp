/**
 * @file instructionHandler.cpp
 * @author Bradley Sullivan (bradleysullivan@nevada.unr.edu)
 * @brief InstructionHandler class implementation
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "instructionHandler.h"

/**
 * @brief Reads in instructions from .txt file into a buffer that is then parsed
 * 
 * @param filename The .txt file to extract instructions from
 * @return int Successful loading indicator
 */
int InstructionHandler::load(std::string filename) {
    uint32_t bufSize;
    std::string line;
    std::fstream file;
    file.open(filename, std::fstream::in);
    if (file.is_open()) {
        file.seekg(0, file.end);
        bufSize = file.tellg();
        file.seekg(0, file.beg);

        char buffer[bufSize];

        file.read(buffer, bufSize);

        parse(buffer, bufSize);
    }
    else {
        return -1;
    }
    file.close();
    return 0;
}

/**
 * @brief Parses instructions from a char array and stores them in a vector of INSTRUCTION structs
 * 
 * @param buffer Raw character data loaded from .txt file
 * @param bufSize Size of buffer used for iteration
 */
void InstructionHandler::parse(char buffer[], uint32_t bufSize) {
    std::string hexConv;
    INSTRUCTION temp;
    int control = 1;
    for (uint32_t i = 0; i < bufSize || control == 4; i++) {
        switch (control) {
            case 1:
                if (buffer[i] >= 65 && buffer[i] <= 90) temp.operation += buffer[i];
                if (buffer[i + 1] == 32) control = 2;
                break;
            case 2:
                if (isAlphaNum(buffer[i])) hexConv += buffer[i];
                if (buffer[i + 1] == 32) {
                    temp.op1 = hexStrToInt(hexConv); 
                    hexConv.clear();
                    control = 3;
                }
                else if (buffer[i + 1] == 10 || i == bufSize - 1) {
                    temp.op1 = hexStrToInt(hexConv);
                    hexConv.clear();
                    control = 4;
                }
                break;
            case 3:
                if (isAlphaNum(buffer[i])) hexConv += buffer[i];
                if (buffer[i + 1] == 10 || buffer[i + 1] == 32 || i == bufSize - 1) {
                    temp.op2 = hexStrToInt(hexConv);
                    hexConv.clear();
                    control = 4;
                }
                break;
            case 4:
                set.push_back(temp);
                temp.operation.clear();
                temp.op1 = 0;
                temp.op2 = 0;
                control = 1;
                break;
        }
        while (buffer[i + 1] == 32) i++;
    }
}

/**
 * @brief Evaluates/executes instructions based on the operation string
 * 
 * @param x Struct that contains instruction operation/operands
 */
void InstructionHandler::execute(INSTRUCTION x) {
    if (x.operation == "ADD") {
        result.push_back(x.op1 + x.op2);
        std::cout << "Result - " << intToHexStr(x.op1 + x.op2) << std::endl;
    }
    else if (x.operation == "SUB") {
        result.push_back(x.op1 - x.op2);
        std::cout << "Result - " << intToHexStr(x.op1 - x.op2) << std::endl;
    }
    else if (x.operation == "MUL") {
        result.push_back(x.op1 * x.op2);
        std::cout << "Result - " << intToHexStr(x.op1 * x.op2) << std::endl;
    }
    else if (x.operation == "DIV") {
        if (x.op2 != 0) {
            result.push_back(x.op1 / x.op2);
            std::cout << "Result - " << intToHexStr(x.op1 / x.op2) << std::endl;
        }
        else std::cout << "Operation undefined" << std::endl;
    }
    else std::cout << "Unrecognized instruction. Ignored" << std::endl;
}

/**
 * @brief Converts a hex string to Base-10 unsigned 32-bit integer
 * 
 * @param hex Hexadecimal number stored as a string
 * @return uint32_t Converted Base-10 integer
 */
uint32_t InstructionHandler::hexStrToInt(std::string hex) {
    uint32_t x = 0;
    if (hex[0] == '0' && hex[1] == 'x') {
        for (int i = 2; i < (int) hex.length(); i++) {
            switch (hex[i]) {
                case 'A':
                    x += 10 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'B':
                    x += 11 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'C':
                    x += 12 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'D':
                    x += 13 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'E':
                    x += 14 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'F':
                    x += 15 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'a':
                    x += 10 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'b':
                    x += 11 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'c':
                    x += 12 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'd':
                    x += 13 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'e':
                    x += 14 * (pow(16, (hex.length() - 1) - i));
                    break;
                case 'f':
                    x += 15 * (pow(16, (hex.length() - 1) - i));
                    break;
                default:
                    x += (hex[i] - '0') * (pow(16, (hex.length() - 1) - i));
            }
        }
    }
    else {
        std::cout << "Number is not in hex format. Returning 0" << std::endl;
        return 0;
    }

    return x;
}

std::string InstructionHandler::intToHexStr(uint32_t x) {
    uint64_t r, q = x;
    std::string hex;
    if (q == 0) hex.insert(0, 1, '0');
    while (q > 0) {
        r = q % 16;
        q /= 16;
        if (r < 10 && r >= 0) hex.insert(0, 1, r + '0');
        else if (r >= 10 && r < 16) hex.insert(0, 1, (r - 10) + 65);
    }
    hex.insert(0, "0x");
    return hex;
}

bool InstructionHandler::isAlphaNum(char c) {
    if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return true;
    else return false;
}

/**
 * @brief Stream operator overload to easily print contents of an INSTRUCTION struct
 * 
 * @param out ostream object reference
 * @param inst INSTRUCTION struct that will have it's contents printed
 * @return std::ostream& Reference to what will be output to console?
 */
std::ostream &operator<<(std::ostream &out, const INSTRUCTION &inst) {
    out << "\nOperation - " << inst.operation << "\nOperator 1 - " << inst.op1 << "\nOperator 2 - " << inst.op2 << std::endl;
    return out;
}

/**
 * @brief Executes and neatly displays each instruction and its output
 * 
 */
void InstructionHandler::printOutput() {
    std::cout << "-=Printing input instruction set=-" << std::endl;
    std::cout << "Instruction set size: " << set.size() << std::endl;

    for (auto x : set) {
        std::cout << x;
        execute(x);
    }
}