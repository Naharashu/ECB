#include "ecb.h"
#include <ostream>
#include <string>
#include <vector>

struct assembler {

    

    std::string transpile(Inst a) {
        switch(a.op) {
            case ld: {
                return "mov " + register_(a.dst.reg) + std::to_string(a.lhs.imm);
            }
            case ret: {
                return "ret";
            }
        }
    }

    void compile(std::vector<IRblock> &m) {
        std::ofstream f("out.asm");
        for(auto &b : m) {
            switch(b.Block_type) {
                case IRblock::func: {
                    f << b.name + ": \n";
                    for(auto &a : b.data) {
                        f << transpile(a) << '\n';
                    }
                }
            }
        }
    }
};
