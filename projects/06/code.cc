#include <iostream>
#include <map>
#include "code.h"

namespace nand2tetris{

    namespace assembler{

        static std::map<std::string, std::bitset<3>> jumpMap = {
            {"", 0x0},
            {"JGT", 0x1},
            {"JEQ", 0x2},
            {"JGE", 0x3},
            {"JLT", 0x4},
            {"JNE", 0x5},
            {"JLE", 0x6},
            {"JMP", 0x7}
        };

        std::map<std::string, std::bitset<7>> computMap = {
            {"0", 0x2a},
            {"1", 0x3f},
            {"-1", 0x3a},
            {"D", 0x0c},
            {"A", 0x30},
            {"M", 0x70},
            {"!D", 0xd},
            {"!A", 0x31},
            {"!M", 0x71},
            {"-D", 0xf},
            {"-A", 0x33},
            {"-M", 0x73},
            {"D+1", 0x1f},
            {"A+1", 0x37},
            {"M+1", 0x77},
            {"D-1", 0xe},
            {"A-1", 0x32},
            {"M-1", 0x72},
            {"D+A", 0x2},
            {"D+M", 0x42},
            {"D-A", 0x13},
            {"D-M", 0x53},
            {"A-D", 0x7},
            {"M-D", 0x47},
            {"D&A", 0x0},
            {"D&M", 0x40},
            {"D|A", 0x15},
            {"D|M", 0x55}
        };

        std::bitset<3> code::dest(std::string &d){
            std::bitset<3> b(0x0);
            for(auto c: d){
                switch(c){
                case 'A':
                    b.set(2);
                    break;
                case 'D':
                    b.set(1);
                    break;
                case 'M':
                    b.set(0);
                    break;
                default:
                    std::cout << "error dest input:" << c << "  "
                              << d << std::endl;
                }
            }

            return b;
        }

        std::bitset<7> code::comp(std::string &j){
            if( computMap.find(j) != computMap.end() )
                return computMap[j];
            else{
                std::cout << "error compute input: " << j << std::endl;
                return 0x0;

            }
        }

        std::bitset<3> code::jump(std::string &j){
            if( jumpMap.find(j) != jumpMap.end() )
                return jumpMap[j];
            else{
                std::cout << "error jump input: " << j << std::endl;
                return 0x0;
            }
        }
    }
}
