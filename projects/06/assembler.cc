#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "parser.h"
#include "code.h"
#include "symbolTable.h"
#include "assembler.h"

namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace


namespace nand2tetris{
    namespace assembler{

        void assembler::firstScan(){

            parser::cTypes ct;

            while(parser_.hasMoreCommands()){
                parser_.advance();
                last_++;

                ct = parser_.commandType();

                if(ct != parser::L_COMMAND) continue;

                if(!symbolTable_.contains(parser_.symbol()))
                   symbolTable_.addEntry(parser_.symbol(), last_);
            }
        }

        void assembler::secondScan(){

            parser::cTypes ct;


            while(parser_.hasMoreCommands()){

                parser_.advance();

                ct = parser_.commandType();

                if(ct == parser::A_COMMAND){
                    outAcommand();
                }else if( ct == parser::C_COMMAND){
                    outCcommand();

                }else {
                    //std::cout << "ct is "<< ct << std::endl;
                    continue;
                }
            }

            std::cout << "End of input file" << std::endl;
            outs_.close();
            return;

        }

        void assembler::outAcommand(){

            std::string symbol = parser_.symbol();
            bool firstisnum = symbol[0];

            std::bitset<16> bit_out;

            if(firstisnum) {
                std::bitset<16> bit_tmp(std::stoi(symbol));
                bit_out = bit_tmp;
            }
            else{ // symbol
                if(buildInSym.find(symbol) == buildInSym.end() &&
                   !symbolTable_.contains(symbol))
                    symbolTable_.addEntry(symbol, lastVarAddr_++);

                std::bitset<16> bit_tmp( symbolTable_.getAddress(symbol) );
                bit_out = bit_tmp;
            }

            bit_out.reset(15);
            // std::cout << bit_out.to_string() << std::endl;

            outs_ << bit_out.to_string() << std::endl;

        }

        void assembler::outCcommand(){

            std::string comp = parser_.comp();
            std::string dest = parser_.dest();
            std::string jump = parser_.jump();

            std::bitset<3> bit_dest = code_.dest(dest);
            std::bitset<7> bit_comp = code_.comp(comp);
            std::bitset<3> bit_jump = code_.jump(jump);

            std::bitset<16> bit_out(bit_comp.to_string() +
                                    bit_dest.to_string() +
                                    bit_jump.to_string());


            // std::cout << "bit_dest.to_string(): " << bit_dest.to_string()
            //           << "bit_comp.to_string(): " << bit_comp.to_string()
            //           << "bit_jump.to_string(): " << bit_jump.to_string()
            //           << "bit_out: " << bit_out
            //           << std::endl;

            bit_out.set(15);
            bit_out.set(14);
            bit_out.set(13);
            //std::cout << bit_out.to_string() << std::endl;

            outs_ << bit_out.to_string() << std::endl;

        }
    }
} // namespace


size_t parse_cmdline(int argc, char** argv, std::string &ifile, std::string &ofile)
{
    try
    {
        /** Define and parse the program options
         */
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Print help messages")
            ("input,f",  po::value(&ifile), "input filename")
            ("out,o",  po::value(&ofile), "output filename");

        po::variables_map vm;
        po::positional_options_description p;
        p.add("input", -1);

        try
        {
            po::store(po::command_line_parser(argc, argv).
                      options(desc).positional(p).run(),
                      vm);
            //parse_command_line(argc, argv, desc),
            //        vm); // can throw

            /** --help option
             */
            if ( vm.count("help")  )
            {
                std::cout << "Basic Command Line Parameter App" << std::endl
                          << desc << std::endl;
                return SUCCESS;
            }

            po::notify(vm); // throws on error, so do after help in case
            // there are any problems
        }
        catch(po::error& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }

        if (vm.count("input"))
        {
            std::cout << "Input files are: "
                      << vm["input"].as< std::string >() << "\n";
        }

        // application code here //

    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached the top of parser_cmdline: "
                  << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;

    }

    return SUCCESS;

} // parser_cmdline

int main(int argc, char** argv)
{
    try{
        std::string ifile;
        std::string ofile;

        if(SUCCESS != parse_cmdline(argc, argv, ifile, ofile))
            return -1;

        std::fstream outs(ofile, std::ofstream::out);

        namespace na = nand2tetris::assembler;

        na::parser parser(ifile);
        na::code code;
        na::symbolTable symbolTable;
        na::assembler worker(parser, code, symbolTable);

        // na::parser::cTypes ct;
        //worker.setParser(parser);
        worker.firstScan();
        worker.secondScan();

        std::cout<< "here" << std::endl;
    }
    catch(std::invalid_argument e){
        std::cerr << "Error input " <<
            e.what() <<  std::endl;

    }
    ////////////////////////////////////////
    // catch(std::exception e){           //
    //     std::cerr << "exception e " << //
    //         e.what() << std::endl;     //
    // }                                  //
    ////////////////////////////////////////

} // main
