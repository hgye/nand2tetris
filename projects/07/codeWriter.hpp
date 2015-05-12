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

        private:
            std::ofstream out_;
        };
    }
}

#endif /* CODEWRITER_H */
