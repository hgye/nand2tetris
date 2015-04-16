#include <fstream>
#include <string>
#include <map>
// for trim
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>


namespace nand2tetris{

    namespace assembler{

        const std::map<std::string, int> buildInSym = {
            {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3}, {"THAT", 4},
            {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}, {"R4", 4},
            {"R5", 5}, {"R6", 6}, {"R7", 7}, {"R8", 8}, {"R9", 9},
            {"R10", 10}, {"R11", 11}, {"R12", 12}, {"R13", 13}, {"R14", 14},
            {"R15", 15},
            {"SCREEN", 16384},
            {"KBD", 24576},
        };

        class parser{
        public:
            explicit parser(std::string fileName);
            ~parser();

            bool hasMoreCommands();
            void advance();

            enum cTypes {A_COMMAND, C_COMMAND, L_COMMAND, N_COMMAND, E_COMMAND};
            cTypes commandType();

            // for A command
            std::string symbol();

            // for C command
            std::string dest();
            std::string comp();
            std::string jump();

        private:
            /*********************************************************************************************************************/
            /* // trim from start                                                                                                */
            /* static inline std::string &ltrim(std::string &s) {                                                                */
            /*     s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));        */
            /*     return s;                                                                                                     */
            /* }                                                                                                                 */
            /*                                                                                                                   */
            /*  // trim from end                                                                                                 */
            /* static inline std::string &rtrim(std::string &s) {                                                                */
            /*     s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end()); */
            /*     return s;                                                                                                     */
            /* }                                                                                                                 */
            /*                                                                                                                   */
            /* // trim from both ends                                                                                            */
            /* static inline std::string &trim(std::string &s) {                                                                 */
            /*     return ltrim(rtrim(s));                                                                                       */
            /* }                                                                                                                 */
            /*********************************************************************************************************************/


            std::ifstream input;
            std::string current;

        };
    }
}
