#include <string>
#include <map>

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

namespace nand2tetris{
    namespace assembler{

        const std::map<std::string, int> buildInSym = {
            {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4},
            {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}, {"R4", 4},
            {"R5", 5}, {"R6", 6}, {"R7", 7}, {"R8", 8}, {"R9", 9},
            {"R10", 10}, {"R11", 11}, {"R12", 12}, {"R13", 13}, {"R14", 14},
            {"R15", 15},
            {"SCREEN", 16384},
            {"KBD", 24576},
        };

        class symbolTable{
        public:
            symbolTable():symbolMap(buildInSym){};
            ~symbolTable(){};

            void addEntry(std::string symbol, int address);

            bool contains(std::string symbol) const;

            int getAddress(std::string symbol);

        private:
            //int last_address_;
            std::map<std::string, int> symbolMap;

        };
    }
}

#endif /* SYMBOLTABLE_H */
