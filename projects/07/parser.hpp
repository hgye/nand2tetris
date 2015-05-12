#include <fstream>
#include <string>
#include <vector>
// for trim
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#ifndef PARSER_H
#define PARSER_H

namespace nand2tetris{

    namespace vm{

        class parser{
        public:
            explicit parser(std::string fileName);
            ~parser();

            bool hasMoreCommands();
            void advance();

            bool effectiveLine() const;

            enum cTypes {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF,
                         C_FUNCTION, C_RETURN, C_CALL, C_ERROR};
            cTypes commandType();

            std::string command();
            std::string arg1();
            int arg2();

        private:
            bool checkSym(std::string &s);

            std::ifstream input_;
            std::string current_;
            //std::vector<std::vector<std::string> > tokens_;
            std::vector<std::string> tokens_;


        };
    }
}

#endif /* PARSER_H */
