#include <iostream>
#include <string>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "parser.hpp"
#include "codeWriter.hpp"
//#include "symbolTable.h"
//#include "vmtranslator.hpp"

namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace

/*
namespace nand2tetris{
    namespace vm{


        void translator::work(){

            parser::cTypes ct;

            while(parser_.hasMoreCommands()){
                parser_.advance();

                if(! parser_.effectiveLine())
                    continue;

                ct = parser_.commandType();

                if(ct == parser::C_ARITHMETIC)
                    codeWriter_.writeArithmetic(parser_.arg1());

                if(ct == parser::C_POP || ct == parser::C_PUSH)
                    codeWriter_.writePushPop(parser_.cmd(),
                                             parser_.arg1(),
                                             parser_.arg2());
            }
        }
    } // namespace vm
} // namespace nand2tetris
*/

size_t parse_cmdline(int argc, char** argv, std::string &dir)
{
    try
    {
        /** Define and parse the program options
         */
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Print help messages")
            ("input, i",  po::value(&dir), "input dir");


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

void work(nand2tetris::vm::parser & parser_,
          nand2tetris::vm::codeWriter & codeWriter_){

    using namespace nand2tetris::vm;

    parser::cTypes ct;

    while(parser_.hasMoreCommands()){
        parser_.advance();

        if(! parser_.effectiveLine())
            continue;

        ct = parser_.commandType();

        if(ct == parser::C_ARITHMETIC)
            codeWriter_.writeArithmetic(parser_.arg1());

        if(ct == parser::C_POP || ct == parser::C_PUSH)
            codeWriter_.writePushPop(parser_.command(),
                                     parser_.arg1(),
                                     parser_.arg2());
    }
}

int main(int argc, char** argv)
{
    //try{
        std::string dir;

        if(SUCCESS != parse_cmdline(argc, argv, dir))
            return -1;

        namespace fs = boost::filesystem;
        fs::path input_dir(dir);

        if( !fs::exists(input_dir) ) {
            std::cout << dir << " :directory does not exit!!" << std::endl;
            return -1;
        }

        if( !fs::is_directory(input_dir)) {
            std::cout << dir << " is not directory!!" << std::endl;
            return -1;
        }

        // fs::path::iterator it;
        const std::string vmsuffix = ".vm";
        const std::string asmsuffix = ".asm";
        nand2tetris::vm::codeWriter codeWriter;

        for(fs::directory_iterator it(input_dir); it != fs::directory_iterator(); ++it) {
            if(it->path().extension() == vmsuffix) {
                fs::path p = fs::basename(it->path()) + (asmsuffix);
                std::cout << p << std::endl;

                std::cout << p.c_str() << std::endl;

                nand2tetris::vm::parser parser(fs::absolute(it->path()).string());
                codeWriter.setFileName(p.string());
                work(parser, codeWriter);
            }
        }

        std::cout<< "here" << std::endl;
        //}
    // catch(std::invalid_argument e){
    //     std::cerr << "Error input " <<
    //         e.what() <<  std::endl;

    // }

} // main
