// Easy Compiler Backend
// Made by Naharashu
// With love :3

#ifndef ECB_H
#define ECB_H

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

enum opcode : uint8_t {
    nop,
    ld,
    add,
    sub,
    mul,
    div_,
    ret
};

enum class reg : uint8_t {
    rax,
    rbx,
    rcx,
    rdx,
    rsi,
    rdi,
    rbp,
    rsp,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15
};

struct value_ {
    enum Value : uint8_t {
        Reg,
        Imm, 
        Var
    } value;
    reg reg;
    int64_t imm=0; 
    std::string varname="";
};



struct Inst {
    opcode op;
    value_ dst;
    value_ lhs;
    value_ rhs;

    std::vector<value_> extra;

    static Inst make_binary(opcode &o, value_ &d, value_ &a, value_ &b) {
        return Inst{o, d, a, b, {}};
    }

    static Inst make_unary(opcode &o, value_ &d, value_ &a) {
        return Inst{o, d, a, {}, {}};
    }

    static Inst make_inst(opcode &o, value_ &d, value_ &a, value_ &b, std::vector<value_> &e) {
        return Inst{o, d, a, b, e};
    }

};

struct IRblock {
    enum Block_type : uint8_t {
        Main,
        func,
        var,
        class_,
        array_,
        goto_,
        call,
    } Block_type;
    std::vector<Inst> data;
    std::string name;
};


inline std::string register_(reg r) {
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


#endif