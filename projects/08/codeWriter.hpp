#include <string>
#include <bitset>
#include <fstream>

#ifndef CODEWRITER_H
#define CODEWRITER_H

namespace nand2tetris{

    namespace vm{

        class codeWriter{
        public:
            codeWriter():currentFunc_(""), nestFuncSeq_(0){};
            ~codeWriter(){out_.close();}

            void setFileName(const std::string & filename);
            void close();

            void writeArithmetic(std::string command);

            void writePushPop(std::string cmd, std::string seg, int index);

            void writeInit();
            void writeLabel(std::string label);
            void writeGoto(std::string label);
            void writeIf(std::string label);
            void writeCall(std::string functionName, int numArgs);
            void writeReturn();
            void writeFunction(std::string functionName, int numLocals);

            static unsigned int label_seq;

        private:
            void oneLogicWrite(std::string& cmd);
            void twoLogicWrite(std::string& cmd);
            void compareWrite(std::string& cmd);
            void mathematicsWrite(std::string& cmd);

            void pushConstant(int& index);
            void pushPointer(int& index);
            void pushCommon(std::string& seg, int& index);
            void pushStatic(int & index);

            void popPointer(int& index);
            void popStatic(int& index);
            void popCommon(std::string& seg, int& index);

            std::string basename_;
            std::ofstream out_;
            std::string currentFunc_;
            unsigned int nestFuncSeq_;

        };
    }
}

#endif /* CODEWRITER_H */
