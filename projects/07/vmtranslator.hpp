#include "parser.h"
#include "code.h"
#include "symbolTable.h"

#ifndef VM_TRANSLATOR_H
#define VM_TRANSLATOR_H

namespace nand2tetris{
    namespace vm{

        class translator{
        public:

            explicit assembler(std::string &ifile, std::string &ofile):
            outs_(ofile), parser_(ifile),last_(0), lastVarAddr_(16) { }

            ~assembler(){
                outs_.close();
            }

            void firstScan();
            void secondScan();

            /* void setParser(parser &p){ parser_ = p;} */
            /* void setCode(code &c) {code_ = c;} */
            /* void setSymbolTable(symbolTable &s){symbolTable_ = s;} */
            //void setOuts(std::fstream &o){outs_ = o;}

        private:
            void outAcommand();
            void outCcommand();

            std::ofstream outs_;
            parser parser_;
            code code_;
            symbolTable symbolTable_;
            int last_;
            int lastVarAddr_;
        };
    }
}

#endif /* VM_TRANSLATOR_H */
