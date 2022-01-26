#ifndef IINSTRUCTION_H
#define IINSTRUCTION_H

#include <iostream>

class IInstruction {
public:
    virtual void parse(char[], uint32_t) = 0;
    virtual std::string execute() = 0;
};

#endif //IINSTRUCTION_H