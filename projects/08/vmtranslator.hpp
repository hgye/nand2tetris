#include "parser.hpp"
#include "codeWriter.hpp"

#ifndef VM_TRANSLATOR_H
#define VM_TRANSLATOR_H

namespace nand2tetris{
    namespace vm{

        class translator{
        public:
            void work();

        private:
            parser parser_;
            codeWriter codeWriter_;
        };
    }
}

#endif /* VM_TRANSLATOR_H */
