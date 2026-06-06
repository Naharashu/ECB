#ifndef GENERATOR_ECB_H
#define GENERATOR_ECB_H

#include <sstream>
#include <vector>
#include <cstdint>
#include "ecb.h"

enum variable_type : uint8_t {
    BYTE_T,
    HALF_T,
    WORD_T,
    LONG_T,
    BOOL_T,
    STRING_T
};

struct generator {
    std::ostringstream data;
    std::ostringstream bss;
    std::ostringstream generated;

    void init() {
        data << "section .data\n";
        bss << "section .bss\n";

        generated << "section .text\n";
        generated << "global _start\n";
        generated << "_start:\n";
        generated << "\tcall _main\n";
        generated << "\tmov rax, 60\n";
        generated << "\txor rdi, rdi\n";
        generated << "\tsyscall\n";
    }

    void emit(std::ostringstream &s, std::string val) {
        s << val << '\n'; // raw emition
    }

    void comptime_val(std::string &name, std::string &val) {
        generated << "%define " << name << ' ' << val << '\n';
    }

    void mov_int(reg r, std::string &val) {
        generated << "mov " << register_(r) << ' ' << val << '\n';
    }

    void mov_var(reg r, std::string &var) {
        generated << "mov " << register_(r) << " [" << var << ']' << '\n';
    }

    void ret(uint8_t n=0) {
        generated << "mov rax " << n << '\n';
        generated << "ret\n";
    }

    void declare_var_val(enum variable_type t, std::string &name, std::string &val) {
        std::string type = " db ";
        switch(t) {
            case BYTE_T:
            case BOOL_T:
            case STRING_T:
            break;
            case HALF_T: type = " dw "; break;
            case WORD_T: type = " dd "; break;
            case LONG_T: type = " dq "; break;
        }
        if(t==STRING_T) data << name << type << val << ", 0" << '\n';
        else data << name << type << val << '\n';
    }

    void declare_var_bss(enum variable_type t, std::string &name, uint64_t &size) {
        std::string type = " resb ";
        switch(t) {
            case BYTE_T:
            case BOOL_T:
            case STRING_T:
            break;
            case HALF_T: type = " resw "; break;
            case WORD_T: type = " resd "; break;
            case LONG_T: type = " resq "; break;
        }
        bss << name << type << size << '\n';
    }

    std::string result() {
        return bss.str() + data.str() + generated.str();
    }
};

#endif