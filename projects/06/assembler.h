#include "parser.h"
#include "code.h"
#include "symbolTable.h"

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

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


        class assembler{
        public:

        assembler(parser &p, code &c, symbolTable &s):

            parser_(p), code_(c), symbolTable_(s), last_(0), lastVarAddr_(16) {}
            ~assembler(){};

            void firstScan();
            void secondScan();

            /* void setParser(parser &p){ parser_ = p;} */
            /* void setCode(code &c) {code_ = c;} */
            /* void setSymbolTable(symbolTable &s){symbolTable_ = s;} */

        private:
            void outAcommand();
            void outCcommand();

            std::fstream outs_;
            parser& parser_;
            code& code_;
            symbolTable& symbolTable_;
            int last_;
            int lastVarAddr_;
        };
    }
}

#endif /* ASSEMBLER_H */
