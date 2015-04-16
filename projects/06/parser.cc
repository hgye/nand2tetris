#include <iostream>
#include <boost/algorithm/string.hpp>
#include "parser.h"

namespace nand2tetris{
    namespace assembler{
        parser::parser(std::string fileName): input(fileName){}

        parser::~parser(){
            input.close();
        }

        bool parser::hasMoreCommands(){

            if( (getline(input, current)) != NULL){

                // blank line
                if(current.empty()) return hasMoreCommands();

                return true;
            }
            else
                return false;
        }

        void parser::advance(){

            //////////////////////////////////////////////////////
            // if(!hasMoreCommands())                           //
            // {                                                //
            //     std::cout << "no more command" << std::endl; //
            //     return;                                      //
            // }                                                //
            //////////////////////////////////////////////////////

            // comment line
            auto pos = current.find("//");

            if(pos != std::string::npos)
                current.erase(pos);

            boost::algorithm::trim(current);

            // std::cout << "current line " << current << std::endl;

        }

        parser::cTypes parser::commandType(){

            auto c=current;

            switch (c[0]) {
            case '@':
                return A_COMMAND;
            case '(':
                return L_COMMAND;
            case 'A':
            case 'D':
            case 'M':
            case '0':
            case '1':
            case '-':
            case '!':
                return C_COMMAND;
            default:
                return E_COMMAND;
            }
        }

        std::string parser::symbol(){
            std::string sym;

            parser::cTypes ct = commandType();
            if(ct != A_COMMAND)
                return NULL;

            // first is @,
            sym = current.substr(1);

            return sym;
        }

        std::string parser::dest(){

            if(commandType() != C_COMMAND)
                return "";

            std::size_t pos = current.find("=");
            if(pos == std::string::npos)
                return "";

            // else
            std::string d = current.substr(0, pos);
            //std::cout << "d is " << d << std::endl;
            return d;

        }

        std::string parser::comp(){

            if(commandType() != C_COMMAND)
                return "";

            std::size_t pos1 = current.find("=");

            std::size_t pos2 = current.find(";");
            std::string c = current.substr(pos1+1, pos2);
            //std::cout << "c is " << c << std::endl;
            return c;

        }

        std::string parser::jump(){
            if(commandType() != C_COMMAND)
                return "";

            std::size_t pos = current.find(";");
            if(pos == std::string::npos)
                return "";

            std::string j = current.substr(pos+1);
            //std::cout << "j is " << j << std::endl;
            return j;

        }

    }
}
