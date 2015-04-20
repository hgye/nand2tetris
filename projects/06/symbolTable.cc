#include "symbolTable.h"

namespace nand2tetris{
    namespace assembler{
        void symbolTable::addEntry(std::string sym, int addr){
            symbolMap.insert({sym, addr});
        }

        bool symbolTable::contains(std::string sym) const {
            if(symbolMap.find(sym) == symbolMap.end())
                return false;
            else
                return true;
        }

        int symbolTable::getAddress(std::string sym) {
            return symbolMap[sym];
        }
    }
}
