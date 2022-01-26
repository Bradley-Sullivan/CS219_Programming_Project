#include <iostream>
#include "instructionLoader.h"
#include "armInstruction.h"

int main(void) {
    InstructionLoader loader(new ARM, std::string("Programming-Project-1.txt"));
    if (loader.load() == 0) {
        std::string output = loader.execute();
        std::cout << output << std::endl;
        if (loader.save("out.txt") == 0) std::cout << "Output saved successfully." << std::endl;
        else std::cout << "Could not save output." << std::endl;
    }
    else {
        std::cout << "Unable to load provided instruction set. File unreachable. Exiting program\n" << std::endl;
    }
    
    return 0;
}