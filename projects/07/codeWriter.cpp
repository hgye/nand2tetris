#include <iostream>
#include <map>
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
                out_ << "@SP" << std::endl
                     << "A=M-1" << std::endl;
                if(cmd == "neg")
                    out_ << "M=-M" << std::endl;
                else // not
                    out_ << "M=!M" << std::endl;
                return;
            }

            if(cmd == "add" || cmd == "sub"){
                out_ << "@SP" << std::endl
                     << "A=M-1" << std::endl
                     << "D=M" << std::endl
                     << "A=A-1" << std::endl;

                if(cmd == "add")
                    out_ << "M=M+D" << std::endl;
                else // sub case
                    out_ << "M=M-D" << std::endl;

                out_ << "D=A" << std::endl
                     << "@SP" << std::endl
                     << "M=D+1" << std::endl;
                return;
            }

            if(cmd == "eq" || cmd == "lt" || cmd == "gt") {
                out_ << "@SP" << std::endl
                     << "AM=M-1" << std::endl
                     << "D=M" << std::endl
                     << "A=A-1" << std::endl
                     << "D=M-D" << std::endl
                     << "@label" << label_seq << std::endl;

                if(cmd == "eq")
                    out_ << "D;JEQ" << std::endl;
                else if(cmd == "lt")
                    out_ << "D;JLT" << std::endl;
                else
                    out_ << "D;JGT" <<std::endl;

                out_ << "@SP" << std::endl
                     << "A=M-1" << std::endl
                     << "M=0" << std::endl
                     << "@label" << label_seq+1 << std::endl
                     << "0;JMP" << std::endl
                     << "(label"<< label_seq << ")" << std::endl
                     << "@SP" << std::endl
                     << "A=M-1" << std::endl
                     << "M=-1" << std::endl
                     << "(label"<< label_seq+1 << ")" << std::endl;
                label_seq+=2;
                return;
            }

            if(cmd == "and" || cmd == "or"){
                out_ << "@SP" << std::endl
                     << "A=M-1" << std::endl
                     << "D=M" << std::endl
                     << "A=A-1" << std::endl;

                if(cmd == "and")
                    out_ << "M=M&D" << std::endl;
                else // or
                    out_ << "M=M|D" << std::endl;

                out_ << "@SP" << std::endl
                     << "M=M-1" << std::endl;
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
