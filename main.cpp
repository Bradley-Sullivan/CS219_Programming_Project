/**
 * @file main.cpp
 * @author Bradley Sullivan (bradleysullivan@nevada.unr.edu)
 * @brief CS-219 Programming Project 1
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include "instructionHandler.h"

#define filename "Programming-Project-1.txt"

int main(void) {
    InstructionHandler instructions;
    if (instructions.load(filename) == -1) {
        std::cout << "Error loading instructions from file. Exiting program.\n" << std::endl;
        return 0;
    }
    instructions.printOutput();
    return 0;
}