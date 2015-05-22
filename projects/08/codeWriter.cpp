#include <iostream>
#include <map>
#include <map>
#include "codeWriter.hpp"

namespace nand2tetris{

    namespace vm{

        void codeWriter::setFileName(const std::string & filename){

            std::size_t pos = filename.find(".");
            basename_ = filename.substr(0, pos);

            if(out_) out_.close();
            out_.open(filename);
        }

        void codeWriter::writeArithmetic(std::string cmd){
            if(cmd == "neg" || cmd == "not")
                oneLogicWrite(cmd);

            if(cmd == "and" || cmd == "or")
                twoLogicWrite(cmd);

            if(cmd == "add" || cmd == "sub")
                mathematicsWrite(cmd);

            if(cmd == "eq" || cmd == "lt" || cmd == "gt")
                compareWrite(cmd);

        }

        void codeWriter::writePushPop(std::string cmd, std::string seg,
                                      int index){
            if(cmd == "push"){
                if(seg == "constant")
                    pushConstant(index);

                if(seg == "pointer")
                    pushPointer(index);

                if(seg == "static")
                    pushStatic(index);

                if(seg == "local" || seg == "argument" ||
                   seg == "this" || seg == "that" || seg == "temp")
                    pushCommon(seg, index);

                out_ << "// end of push" << std::endl;
                return;
            }

            if (cmd == "pop"){
                if(seg == "pointer")
                    popPointer(index);
                else if (seg == "static")
                    popStatic(index);
                else
                    popCommon(seg, index);

                out_<< "// end of pop" << std::endl;
                return;
            }

        }

        void codeWriter::writeLabel(std::string label){
            out_ << "(" << label << ")" << std::endl;
        }

        void codeWriter::writeGoto(std::string label){
            out_ << "@" << label << std::endl
                 << "0;JMP" << std::endl;
        }

        void codeWriter::writeIf(std::string label){
            out_ << "@SP" << std::endl
                 << "AM=M-1" << std::endl
                 << "D=M" << std::endl
                 << "@" << label<< std::endl
                 << "D;JNE" << std::endl;
        }


        void codeWriter::writeFunction(std::string functionName, int numLocals){
            out_ << "(" << functionName << ")" << std::endl
                 << "@LCL" <<std::endl
                 << "A=M" << std::endl;

            for(int i = 0; i < numLocals; i++){
                out_ << "M=0" << std::endl
                     << "A=A+1" << std::endl;
            }
        }

        void codeWriter::writeReturn(){
            // R5 is temp, frame pointer
            // FRAME(r5) = LCL
            out_ << "@LCL" << std::endl
                 << "D=M" << std::endl
                 << "@R5" << std::endl
                 << "M=D" << std::endl;

            // RET = *(FRAME-5), r6
            out_ << "@5" << std::endl
                 << "D=A" << std::endl
                 << "@LCL" << std::endl
                 << "A=M-D" << std::endl
                 << "D=M" << std::endl
                 << "@R6" << std::endl
                 << "M=D" << std::endl;

            // *ARG = pop()
            out_ << "@SP" << std::endl
                 << "AM=M-1" << std::endl
                 << "D=M" << std::endl
                 << "@ARG" << std::endl
                 << "A=M" << std::endl
                 << "M=D" << std::endl;
            //<< "@SP" << std::endl
            //   << "M=A-1" << std::endl;

            // SP = ARG + 1
            out_ << "@ARG" << std::endl
                 << "A=M+1" << std::endl
                //<< "A=A+1" << std::endl
                 << "D=A" << std::endl
                 << "@SP" << std::endl
                 << "M=D" << std::endl;

            // THAT = *(FRAME - 1)
            out_ << "@LCL" << std::endl
                 << "A=M-1" << std::endl
                 << "D=M" << std::endl
                 << "@THAT" << std::endl
                 << "M=D" << std::endl;

            // THIS = *(FRAME - 2)
            out_ << "@2" << std::endl
                 << "D=A" <<std::endl
                 << "@LCL" << std::endl
                 << "A=M-D" << std::endl
                 << "D=M" << std::endl
                 << "@THIS" << std::endl
                 << "M=D" << std::endl;

            // ARG = *(FRAME - 3)
            out_ << "@3" << std::endl
                 << "D=A" <<std::endl
                 << "@LCL" << std::endl
                 << "A=M-D" << std::endl
                 << "D=M" << std::endl
                 << "@ARG" << std::endl
                 << "M=D" << std::endl;

            // LCL = *(FRAME - 4)
            out_ << "@4" << std::endl
                 << "D=A" << std::endl
                 << "@R5" << std::endl
                 << "A=M-D" << std::endl
                 << "D=M" << std::endl
                 << "@LCL" << std::endl
                 << "M=D" << std::endl;

            // goto ret
            out_ << "@R6" << std::endl
                 << "A=M" << std::endl
                 << "0;JMP" << std::endl;
        }

        void codeWriter::oneLogicWrite(std::string & cmd){
            out_ << "@SP" << std::endl
                 << "A=M-1" << std::endl;
            if(cmd == "neg")
                out_ << "M=-M" << std::endl;
            else // not
                out_ << "M=!M" << std::endl;
            return;
        }

        void codeWriter::twoLogicWrite(std::string & cmd){
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

            return;
        }

        void codeWriter::compareWrite(std::string & cmd){
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

        void codeWriter::mathematicsWrite(std::string & cmd){
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

        void codeWriter::pushConstant(int & index){
            out_ << "@" << index << std::endl
                 << "D=A" << std::endl
                 << "@SP" << std::endl
                 << "A=M" << std::endl
                 << "M=D" << std::endl
                 << "@SP" << std::endl
                 << "M=M+1" << std::endl;

            return;
        }

        void codeWriter::popPointer(int & index){
            out_ << "@SP" << std::endl
                 << "AM=M-1" << std::endl
                 << "D=M" << std::endl;

            if(index == 0)
                out_ << "@THIS" << std::endl;
            else // index == 1
                out_ << "@THAT" << std::endl;

            out_ << "M=D" << std::endl;

            return;
        }

        void codeWriter::pushPointer(int& index){
            if(index == 0)
                out_ << "@THIS" << std::endl;
            else // index == 1
                out_ << "@THAT" << std::endl;

            out_ << "D=M" << std::endl
                 << "@SP" << std::endl
                 << "M=M+1" << std::endl
                 << "A=M-1" << std::endl
                 << "M=D" << std::endl;
            return;
        }

        void codeWriter::pushStatic(int & index){
            out_ << "@" << basename_ << "." << index << std::endl
                 << "D=M" << std::endl
                 << "@SP" << std::endl
                 << "AM=M+1" << std::endl
                 << "A=A-1" << std::endl
                 << "M=D" <<std::endl;
        }

        void codeWriter::popStatic(int & index){
            out_ << "@SP" << std::endl
                 << "AM=M-1" << std::endl
                //<< "A=A+1" << std::endl
                 << "D=M" << std::endl
                 << "@" << basename_ << "." << index << std::endl
                 << "M=D" << std::endl;
        }

        void codeWriter::pushCommon(std::string & seg, int & index){
            if( seg == "temp"){
                out_ << "@5" << std::endl
                     << "D=A" << std::endl
                     << "@" << index << std::endl
                     << "A=D+A" << std::endl; // D is 5, A is index
            }
            else{
                out_ << "@" << index << std::endl
                     << "D=A" << std::endl;

                if(seg == "local")
                    out_ << "@LCL" << std::endl;
                else if(seg == "argument")
                    out_ << "@ARG" << std::endl;
                else if(seg == "this")
                    out_ << "@THIS" << std::endl;
                else// if(seg == "THAT")
                    out_ << "@THAT" << std::endl;

                out_ << "A=M+D" << std::endl; // M is seg base, D is index
            }

            // after all of this, A is what we want, and M[A] is right
            out_ << "D=M" << std::endl
                 << "@SP" << std::endl
                 << "M=M+1" << std::endl
                 << "A=M-1" << std::endl
                 << "M=D" << std::endl;
            return;
        }

        void codeWriter::popCommon(std::string & seg, int & index){
            // for pop, use two indirect address, use SP last as temp
            if(seg == "temp"){
                out_ << "@5" << std::endl
                     << "D=A" << std::endl
                     << "@" << index << std::endl
                     << "D=A+D" << std::endl;

            }else{
                if(seg == "local")
                    out_ << "@LCL" << std::endl;
                else if(seg == "argument")
                    out_ << "@ARG" << std::endl;
                else if(seg == "this")
                    out_ << "@THIS" << std::endl;
                else // if(seg == "THAT")
                    out_ << "@THAT" << std::endl;

                out_ << "D=M" << std::endl // D is M[LCL] ...
                     << "@" << index << std::endl
                     << "D=A+D" << std::endl;
            }

            // D is temp, indirect address for segment
            out_ << "@SP" << std::endl
                 << "A=M" << std::endl
                 << "M=D" << std::endl // store D in SP
                 << "@SP" << std::endl
                 << "AM=M-1" << std::endl
                 << "D=M" << std::endl
                 << "A=A+1" << std::endl
                 << "A=M" << std::endl
                 << "M=D" << std::endl;

        }
    }
}
