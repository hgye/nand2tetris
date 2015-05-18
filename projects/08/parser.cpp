#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "parser.hpp"

namespace nand2tetris{
    namespace vm{
        parser::parser(std::string fileName): input_(fileName){}

        parser::~parser(){
            input_.close();
        }

        bool parser::hasMoreCommands(){
            if( (getline(input_, current_)) != NULL)
                return true;
            else
                return false;
        }

        void parser::advance(){

            // comment line
            auto pos = current_.find("//");

            if(pos != std::string::npos)
                current_.erase(pos);

            boost::algorithm::trim(current_);

            std::istringstream iss(current_);
            std::vector<std::string> tokens{
                std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{}};

            tokens_ = tokens;

        }

        bool parser::effectiveLine() const {
            return !current_.empty();
        }

        parser::cTypes parser::commandType(){

            std::istringstream line(current_);

            std::string cmd;
            line >> cmd;

            if(cmd == "add" || cmd == "sub" || cmd == "mult" || cmd == "neg" ||
               cmd == "eq" || cmd == "gt" || cmd == "lt" || cmd == "and" ||
               cmd == "or" || cmd == "not")
                return C_ARITHMETIC;

            if (cmd == "push")
                return C_PUSH;

            if (cmd == "pop")
                return C_POP;

            if (cmd == "label")
                return C_LABEL;

            if (cmd == "goto")
                return C_GOTO;

            if(cmd == "if-goto")
                return C_IF;

            if(cmd == "function")
                return C_FUNCTION;

            if(cmd == "call")
                return C_CALL;

            if(cmd == "return")
                return C_RETURN;
            else
                return C_ERROR;
        }

        std::string parser::command(){
            return tokens_[0];
        }

        std::string parser::arg1(){

            parser::cTypes ct = commandType();
            if( ct == C_RETURN )
                return NULL;

            if( ct == C_ARITHMETIC )
                return tokens_[0];
            else
                return tokens_[1];
        }

        int parser::arg2(){

            parser::cTypes ct = commandType();

            if(ct == C_PUSH || ct == C_POP ||
               ct == C_FUNCTION || ct == C_CALL )
                return std::stoi(tokens_[2]);
            else
                return -1;
        }
    }
}
