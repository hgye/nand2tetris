#include <string>
#include <bitset>
#include <ofstream>

#ifndef CODEWRITER_H
#define CODEWRITER_H

namespace nand2tetris{

    namespace vm{

        class codeWriter{
        public:
            explicit codeWriter(std::ofstream & os){out_ = os;}
            ~codeWriter(){out_.close();}

            void setFileName(std::string filename);

            void writeArithmetic(std::string command);

            void writePushPop(std::string cmd, std::string seg, int index);

            void close();

        private:
            std::ofstream out_;
        };
    }
}

#endif /* CODEWRITER_H */
