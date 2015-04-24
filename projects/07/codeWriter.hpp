#include <string>
#include <bitset>

#ifndef CODEWRITER_H
#define CODEWRITER_H

namespace nand2tetris{

    namespace vm{

        class codeWriter{
        public:
            codeWriter(){};
            ~codeWriter(){};

            void setFileName(std::string filename);

            void writeArithmetic(std::string command);

            void writePushPop(std::string cmd, std::string seg, int index);

            void close();

        private:
            std::string filename_;
        };
    }
}

#endif /* CODEWRITER_H */
