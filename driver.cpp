#include <iostream>
#include "instructionLoader.h"
#include "armInstruction.h"

int main(void) {
    InstructionLoader loader(new ARM, std::string("Programming-Project-1.txt"));
    loader.load();
    std::string output = loader.execute();
    std::cout << output << std::endl;
    loader.save("out.txt");
    return 0;
}