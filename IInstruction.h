/**
 * @file IInstruction.h
 * @author Bradley Sullivan (bradleysullivan@nevada.unr.edu)
 * @brief Defines the IInstruction interface. Different Assembly architecture
 *        classes should inherit from this interface.
 * @version 0.1
 * @date 2022-01-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IINSTRUCTION_H
#define IINSTRUCTION_H

#include <iostream>

class IInstruction {
public:
    virtual void parse(char[], uint32_t) = 0;
    virtual std::string execute() = 0;
};

#endif //IINSTRUCTION_H