#include "armInstruction.h"

void ARM::parse(char buffer[], uint32_t bufSize) {
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
                    control = 5;
                }
                break;
            case 3:
                if (isAlphaNum(buffer[i])) hexConv += buffer[i];
                if (buffer[i + 1] == 32) {
                    temp.op2 = hexStrToInt(hexConv);
                    hexConv.clear();
                    control = 4;
                }
                else if (buffer[i + 1] == 10 || i == bufSize - 1) {
                    temp.op2 = hexStrToInt(hexConv);
                    hexConv.clear();
                    control = 5;
                }
                break;
            case 4:
                if (isAlphaNum(buffer[i])) hexConv += buffer[i];
                if (buffer[i + 1] == 10 || buffer[i + 1] == 32 || i == bufSize - 1) {
                    temp.op3 = hexStrToInt(hexConv);
                    hexConv.clear();
                    control = 5;
                }
                break;
            case 5:
                set.push_back(temp);
                temp.operation.clear();
                temp.op1 = 0;
                temp.op2 = 0;
                temp.op3 = 0;
                control = 1;
                break;
        }
        while (buffer[i + 1] == 32) i++;
    }
}

void ARM::execute() {
    return;
}

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

bool ARM::isAlphaNum(char c) {
    if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return true;
    else return false;
}