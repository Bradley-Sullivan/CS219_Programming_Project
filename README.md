# CS-219 Programming Project 3
### Project Overview
This program aims to emulate basic ARM Assembly language instructions with C++.

Supported Instructions:
- ADD, SUB, MUL, DIV
- AND, OR (ORR), XOR (EOR), NOT
- LSL, LSR, ASR
- MOV

Supported Operand Formats:
- OPCODE Rd, #IMM
    - MOV (only)
- OPCODE Rd, Rn, Rm
    - ADD, SUB, AND, ORR, XOR
- OPCODE Rd, Rn
    - ASR, LSR, LSL

There should be sufficient modularity for future expansion/extension with a separate instruction loader/writer and dedicated ARM instruction class.


## Build Environment
- Written in Visual Studio Code
- Compiled with g++ 9.3.0
- Built with GNU Make 4.2.1
- Tested on Windows 10 WSLv2 Ubuntu 20.04

## Installation
This program has been designed and tested on WSLv2 Ubuntu 20.04.

An installation of Linux or WSL is recommended.

## Build Instructions
Built with Make on Linux using the included makefile.

1. Navigate to the program directory
2. Execute the `make` command in the terminal
    - No additional arguments/options necessary

## Usage
1. Navigate to the program directory
2. Execute `./instruction` in the terminal

All console output will be stored in the .txt file `out.txt`


## Author
Bradley Sullivan - CS 219.1001

bradleysullivan@nevada.unr.edu

Git Repository: https://github.com/Bradley-Sullivan/CS219_Programming_Project





