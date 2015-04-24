#include <iostream>
#include <map>
#include "codeWriter.hpp"

namespace nand2tetris{

    namespace vm{

        void codeWriter::setFileName(std::string filename){
            out_.open(filename);
        }

        void codeWriter::writeArithmetic(std::string cmd){
            if(cmd == "neg" || cmd == "not"){
                return;
            }
            else{
                out_ << "@SP" << std::endl
                     << "MA=M-1" << std::endl
                     << "D=M" << std::endl
                     << "A=A-1" << std::endl
                     << "M=M+D" << std::endl;

                // if(cmd == "add"){
                //     out << << std::endl
                // }

                return;
            }

        }

        void codeWriter::writePushPop(std::string cmd, std::string seg,
                                      int index){
            if(cmd == "push"){
                if(seg == "constant"){
                    out_ << "@" << index << std::endl
                         << "D=A" << std::endl
                         << "@SP" << std::endl
                         << "M=D" << std::endl
                         << "D=A+1" << std::endl
                         << "M=D" << std::endl;
                }

                return;
            }

            if (cmd == "pop"){
                return;
            }

        }

    }
}
