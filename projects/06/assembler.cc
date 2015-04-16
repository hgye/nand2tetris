#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "parser.h"
#include "code.h"

namespace
{
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;

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
        std::cerr << "Unhandled Exception reached the top of main: "
                  << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;

    }

    return SUCCESS;

}

int main(int argc, char** argv)
{
    try{
        std::string ifile;
        std::string ofile;

        if(SUCCESS != parse_cmdline(argc, argv, ifile, ofile))
            return -1;

        std::fstream outs(ofile, std::ofstream::out);

        namespace na = nand2tetris::assembler;

        nand2tetris::assembler::parser parser(ifile);
        nand2tetris::assembler::code code;

        std::string symbol;
        std::string comp;
        std::string dest;
        std::string jump;

        std::bitset<3> bit_dest;
        std::bitset<7> bit_comp;
        std::bitset<3> bit_jump;

        while(parser.hasMoreCommands()){

            parser.advance();

            nand2tetris::assembler::parser::cTypes ct;
            ct = parser.commandType();

            if(ct == na::parser::A_COMMAND){
                symbol = parser.symbol();

                std::bitset<16> bit_out(std::stoi(symbol));
                bit_out.reset(15);
                std::cout << bit_out.to_string() << std::endl;

                outs << bit_out.to_string() << std::endl;

            }else if( ct == na::parser::C_COMMAND){

                dest = parser.dest();
                comp = parser.comp();
                jump = parser.jump();

                bit_dest = code.dest(dest);
                bit_comp = code.comp(comp);
                bit_jump = code.jump(jump);

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
                std::cout << bit_out.to_string() << std::endl;

                outs << bit_out.to_string() << std::endl;
            }else{
                //std::cout << "ct is "<< ct << std::endl;
                continue;
            }
        }

        std::cout << "End of input file" << std::endl;
        outs.close();
        return SUCCESS;


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
