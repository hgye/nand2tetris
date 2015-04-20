#include <string>
#include <map>

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

namespace nand2tetris{
    namespace assembler{
        class symbolTable{
        public:
            symbolTable(){};
            ~symbolTable(){};

            void addEntry(std::string symbol, int address);

            bool contains(std::string symbol) const;

            int getAddress(std::string symbol);

        private:
            int last_address_;
            std::map<std::string, int> symbolMap;

        };
    }
}

#endif /* SYMBOLTABLE_H */
