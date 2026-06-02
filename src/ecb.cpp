#include "include/ecb.h"
#include <ostream>
#include <string>
#include <vector>

struct assembler {

    std::string register_(reg r) {
        switch (r) {
            case reg::rax: return "rax";
            case reg::rbx: return "rbx";
            case reg::rcx: return "rcx";
            case reg::rdx: return "rdx";
            case reg::rsi: return "rsi";
            case reg::rdi: return "rdi";
            case reg::rbp: return "rbp";
            case reg::rsp: return "rsp";
            case reg::r8: return "r8";
            case reg::r9: return "r9";
            case reg::r10: return "r10";
            case reg::r11: return "r11";
            case reg::r12: return "r12";
            case reg::r13: return "r13";
            case reg::r14: return "r14";
            case reg::r15: return "r15";
        }
    }

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

int main() {
    std::vector<IRblock> abc {
        {IRblock::func, {{ld, {value_::Imm, 42}}}}
    }
}