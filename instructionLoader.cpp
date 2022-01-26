#include "instructionLoader.h"

/**
 * @brief Reads in instruction set from .txt file and stores in char buffer
 * 
 * @return int Read status
 */
int InstructionLoader::load() {
    std::fstream file;
    file.open(filename, std::fstream::in);
    if (file.is_open()) {
        file.seekg(0, file.end);
        bufSize = file.tellg();
        file.seekg(0, file.beg);

        buffer = new char[bufSize];

        file.read(buffer, bufSize);

        i->parse(buffer, bufSize);
    }
    else {
        return -1;
    }
    file.close();
    return 0;
}

/**
 * @brief Writes instruction execution output to file
 * 
 * @param outputFilename File to be written to. If file does not exist, one is created.
 * @return int Write status
 */
int InstructionLoader::save(std::string outputFilename) {
    std::fstream file;
    file.open(outputFilename, std::fstream::out);
    if (file.is_open()) {
        file.write(exeOutput.c_str(), exeOutput.size());
    }
    else {
        return -1;
    }
    file.close();
    return 0;
}

/**
 * @brief Fetches execution output from IInstruction pointer.
 * 
 * @return std::string Returns exectution output string
 */
std::string InstructionLoader::execute() {
    exeOutput = i->execute();
    return exeOutput;
}