#include <string>
#include <bitset>
#include <fstream>

#ifndef CODEWRITER_H
#define CODEWRITER_H

namespace nand2tetris{

    namespace vm{

        class codeWriter{
        public:
            codeWriter(){};
            ~codeWriter(){out_.close();}

            void setFileName(const std::string & filename);

            void writeArithmetic(std::string command);

            void writePushPop(std::string cmd, std::string seg, int index);

            void close();

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

        };
    }
}

#endif /* CODEWRITER_H */
