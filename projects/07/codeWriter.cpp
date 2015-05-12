#include <iostream>
#include <map>
#include "codeWriter.hpp"

namespace nand2tetris{

    namespace vm{

        void codeWriter::setFileName(const std::string & filename){
            if(out_) out_.close();
            out_.open(filename);
        }

        void codeWriter::writeArithmetic(std::string cmd){
            if(cmd == "neg" || cmd == "not"){
                return;
            }
            else{
                out_ << "@SP" << std::endl
                     << "A=M-1" << std::endl
                     << "D=M" << std::endl
                     << "A=A-1" << std::endl
                     << "M=M+D" << std::endl
                     << "D=A" << std::endl
                     << "@SP" << std::endl
                     << "M=D+1" << std::endl;

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
                         << "A=M" << std::endl
                         << "M=D" << std::endl
                         << "@SP" << std::endl
                         << "M=M+1" << std::endl;
                }

                return;
            }

            if (cmd == "pop"){
                return;
            }

        }

    }
}
