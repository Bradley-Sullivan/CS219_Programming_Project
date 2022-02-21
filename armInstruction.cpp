#include "armInstruction.h"

/**
 * @brief Parses Assembly instructions from character buffer
 * 
 * @param buffer Buffer containing instruction set loaded from .txt file
 * @param bufSize Size of character buffer
 */
void ARM::parse(char buffer[], uint32_t bufSize) {
    std::string hexConv;
    int opCt = 0, i = 0;
    INSTRUCTION temp;
    uint32_t regIdx;
    clrInst(temp);

    while (i < (int) bufSize) {
        for (; opCt == 0 && buffer[i] != 32 && buffer[i] != 10 && i < (int) bufSize; i++) {
            temp.operation += buffer[i];
        }
        if (buffer[i] == 32) {
            while (buffer[i] == 32) i++;
            if (buffer[i] == 'r' || buffer[i] == 'R') {
                regIdx = getRegIdx(buffer, i + 1);
                temp.op[opCt] = regIdx;
                temp.regVal[opCt] = true;
                opCt++;
                i += 2;
            }
            else {
                for (; buffer[i] != 32 && buffer[i] != 10 && i < (int) bufSize; i++) {
                    hexConv += buffer[i];
                }
                temp.op[opCt] = hexStrToInt(hexConv);
                hexConv.clear();
                opCt++;
                if (opCt == 3) opCt = 0;
            }
        }
        if (opCt != 0 && (buffer[i] == 10 || i >= (int) bufSize)) {
            set.push_back(temp);
            clrInst(temp);
            opCt = 0;
        }
        else if (opCt == 0) i++;
    }
}

/**
 * @brief Parses specified register index from char buffer
 * 
 * @param buffer Input character buffer
 * @param i Current buffer index
 * @return uint32_t Parsed register index
 */
uint32_t ARM::getRegIdx(char buffer[], int i) {
    int k = i + 1, regIdx;
    while (buffer[k] > 48 && buffer[k] <= 57) k++;
    switch (k - i) {
        case 1:
            regIdx = buffer[k - 1] - '0';
            break;
        case 2: 
            regIdx = (10 * (buffer[k - 2] - '0')) + (buffer[k - 1] - '0');
            break;
        default:
            std::cout << "regIdx err" << std::endl;
            break;
    
    }
    return regIdx;
}

/**
 * @brief Basic instruction execution
 * 
 * @return std::string Necessary output for printing to console built from buildOutput()
 */
std::string ARM::execute() {
    uint32_t rVal;
    for (auto& x : set) {
        if (x.operation != "MOV") {
            if (x.regVal[0]) { rVal = r[(int) x.op[0]]; x.op[0] = rVal; }
            if (x.regVal[1]) { rVal = r[(int) x.op[1]]; x.op[1] = rVal; }
            if (x.regVal[2]) { rVal = r[(int) x.op[2]]; x.op[2] = rVal; }
        }        
        if (x.operation == "ADD") {
            result.push_back(x.op[0] + x.op[1] + x.op[2]);
            if (x.op[0] + x.op[1] + x.op[2] < x.op[0] ||
                x.op[0] + x.op[1] + x.op[2] < x.op[1] ||
                x.op[0] + x.op[1] + x.op[2] < x.op[2]) x.overflow = true;
        }
        else if (x.operation == "SUB") {
            result.push_back(x.op[0] - x.op[1]);
            if (x.op2 > x.op1) x.overflow = true;
        }
        else if (x.operation == "DIV") {
            if (x.op2 != 0) result.push_back(x.op[0] / x.op[1]);
            else result.push_back(0);
        }
        else if (x.operation == "MUL") {
            result.push_back(x.op[0] * x.op[1]);
        }
        else if (x.operation == "LSL") {
            result.push_back(x.op[0] << 1);
        }
        else if (x.operation == "LSR") {
            result.push_back(x.op[0] >> 1);
        }
        else if (x.operation == "ASR") {
            if (!MSBChk(x.op[0])) result.push_back(x.op[0] >> 1);
            else result.push_back((x.op[0] >> 1) ^ (uint32_t) (8 * pow(16, (intToHexStr(x.op[0]).length() - 3))));
        }
        else if (x.operation == "AND") {
            result.push_back(x.op[0] & x.op[1]);
        }   
        else if (x.operation == "OR" || x.operation == "ORR") {
            result.push_back(x.op[0] | x.op[1]);
        }
        else if (x.operation == "EOR" || x.operation == "XOR") {
            result.push_back(x.op[0] ^ x.op[1]);
        }
        else if (x.operation == "NOT") {
            result.push_back(~x.op[0]);
        }
        else if (x.operation == "MOV") {
            if (x.regVal[0]) r[x.op[0]] = x.op[1];
            else if (x.regVal[0] && x.regVal[1]) r[x.op[0]] = r[x.op[1]];
            result.push_back(x.op[1]);
        }
    }
    return buildOutput();
}

bool ARM::MSBChk(uint32_t x) {
    std::string hex = intToHexStr(x);
    if (hex[2] == '8' || hex[2] == '9' ||
        hex[2] == 'A' || hex[2] == 'B' ||
        hex[2] == 'C' || hex[2] == 'D' ||
        hex[2] == 'E' || hex[2] == 'F') return true;
    else return false;
}

/**
 * @brief Structures output string for printing
 * 
 * @return std::string Output string to be displayed to console
 */
std::string ARM::buildOutput() {
    std::stringstream out;
    out << "\n";
    for (int i = 0; i < (int) set.size(); i++) {
        //Insert some operation checking for including the correct outputs/operands
        out << "Operation       : " << set[i].operation << "\n";
        out << "Operator 1      : " << intToHexStr(set[i].op[0]) << "\n";
        out << "Operator 2      : " << intToHexStr(set[i].op[1]) << "\n";
        out << "Operator 3      : " << intToHexStr(set[i].op[2]) << "\n";
        out << "Result          : ";
        if (set[i].operation == "MOV") out << intToHexStr(result[i]) << " ==> R" << set[i].op[0];
        else out << intToHexStr(result[i]);
        if (set[i].overflow) out << " (!!OVERFLOW!!)\n";
        else out << "\n";
        out << std::endl;
    }
    return out.str();
}

/**
 * @brief Converts an ASCII string of hexadecimal numbers to uint32_t
 * 
 * @param hex String containing the ASCII hex number
 * @return uint32_t Converted hex value in decimal
 */
uint32_t ARM::hexStrToInt(std::string hex) {
    uint32_t x = 0;
    if (hex[0] == '0' && hex[1] == 'x') {
        for (int i = 2; i < (int) hex.length(); i++) {
            if (hex[i] >= 65 && hex[i] <= 70) x += (10 + (hex[i] - 65)) * (pow(16, (hex.length() - 1) - i));
            else if (hex[i] >= 97 && hex[i] <= 102) x += (10 + (hex[i] - 97)) * (pow(16, (hex.length() - 1) - i));
            else if (hex[i] >= 48 && hex[i] <= 57) x += (hex[i] - 48) * (pow(16, (hex.length() - 1) - i));
        }
    }
    else {
        std::cout << "Number is not in hex format. Returning 0" << std::endl;
        return 0;
    }

    return x;
}

/**
 * @brief Converts a uint32_t to an ASCII hexadecimal string
 * 
 * @param x Decimal number to be converted
 * @return std::string Converted hex ASCII string
 */
std::string ARM::intToHexStr(uint32_t x) {
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

/**
 * @brief Simple test for alpha-numeric characters
 * 
 * @param c Character to be tested
 * @return true Is an alpha-numeric character
 * @return false Is not an alpha-numeric character
 */
bool ARM::isAlphaNum(char c) {
    if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return true;
    else return false;
}

void ARM::clrInst(INSTRUCTION& x) {
    for (int i = 0; i < 3; i++) {
        x.regVal[i] = false;
        x.op[i] = 0;
    }
    x.overflow = false;
    x.operation.clear();
}