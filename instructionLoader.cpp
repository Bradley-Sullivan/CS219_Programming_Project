#include "instructionLoader.h"

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

std::string InstructionLoader::execute() {
    exeOutput = i->execute();
    return exeOutput;
}