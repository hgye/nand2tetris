#include <fstream>
#include <string>
#include <map>
// for trim
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#ifndef PARSER_H
#define PARSER_H

namespace nand2tetris{

    namespace assembler{

        class parser{
        public:
            //parser(){};
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
            bool checkSym(std::string &s);

            std::ifstream input;
            std::string current;

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

        };
    }
}

#endif /* PARSER_H */
