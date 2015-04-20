#include <string>
#include <bitset>

#ifndef CODE_H
#define CODE_H

namespace nand2tetris{

    namespace assembler{

        class code{
        public:
            code(){};
            ~code(){};

            std::bitset<3> dest(std::string &d);

            std::bitset<7> comp(std::string &c);

            std::bitset<3> jump(std::string &j);
        };
    }
}

#endif /* CODE_H */
