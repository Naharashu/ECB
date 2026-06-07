#ifndef GENERATOR_ECB_H
#define GENERATOR_ECB_H

#include <sstream>
#include <vector>
#include <cstdint>
#include "ecb.h"

enum variable_type : uint8_t {
    BYTE_T,
    SHORT_T,
    INT_T,
    LONG_T,
    BOOL_T,
    STRING_T
};

struct generator {
    std::ostringstream data;
    std::ostringstream bss;
    std::ostringstream text;
    bool inside_label=false;

    void init() {
        data << "section .data\n";
        bss << "section .bss\n";

        text << "section .text\n";
        text << "global _start\n";
        text << "_start:\n";
        text << "\tcall main\n";
        text << "\tmov rdi, rax\n";
        text << "\tmov rax, 60\n";
        text << "\tsyscall\n";
    }

    void emit_tab() {
        if(inside_label) text << '\t';
    }

    void start_label(const std::string &name) {
        text << name << ":\n";
        inside_label = true;
    }

    void end_label() {
        inside_label = false;
    }

    void emit(std::ostringstream &s, std::string val) {
        emit_tab();
        s << val << '\n'; // raw emition
    }

    void comptime_val(const std::string &name, const std::string &val) {
        text << "%define " << name << ' ' << val << '\n';
    }

    void mov_int(reg r, const std::string &val) {
        emit_tab();
        text << "mov " << register_(r) << ", " << val << '\n';
    }

    void mov_var(reg r, const std::string &var) {
        emit_tab();
        text << "mov " << register_(r) << ", [" << var << ']' << '\n';
    }

    void ret() {
        emit_tab();
        text << "ret\n";
    }

    void retn(uint8_t n=0) {
        emit_tab();
        text << "mov rax " << n << '\n';
        emit_tab();
        text << "ret\n";
    }


    void declare_var_val(enum variable_type t, const std::string &name, const std::string &val) {
        std::string type = " db ";
        switch(t) {
            case BYTE_T:
            case BOOL_T:
            case STRING_T:
            break;
            case SHORT_T: type = " dw "; break;
            case INT_T: type = " dd "; break;
            case LONG_T: type = " dq "; break;
        }
        data << '\t';
        if(t==STRING_T) data << name << type << val << ", 0" << '\n';
        else data << name << type << val << '\n';
    }

    void declare_var_bss(enum variable_type t, const std::string &name,const uint64_t &size) {
        std::string type = " resb ";
        switch(t) {
            case BYTE_T:
            case BOOL_T:
            case STRING_T:
            break;
            case SHORT_T: type = " resw "; break;
            case INT_T: type = " resd "; break;
            case LONG_T: type = " resq "; break;
        }
        bss << '\t';
        bss << name << type << size << '\n';
    }

    void set_var_val(const std::string &var, const std::string &val) {
        emit_tab();
        text << "mov [" << var << "], " << val << '\n';
    }
    
    void set_var_val_reg(const std::string &var, reg r) {
        emit_tab();
        text << "mov [" << var << "], " << register_(r) << '\n';
    }

    void add_reg_val(reg r, const std::string &val) {
        emit_tab();
        text << "add " << register_(r) << ", " << val << '\n';
    }

    void sub_reg_val(reg r, const std::string &val) {
        emit_tab();
        text << "sub " << register_(r) << ", " << val << '\n';
    }

    void mul_reg_val(reg r, const std::string &val) {
        emit_tab();
        text << "imul " << register_(r) << ", " << val << '\n';
    }

    void div_reg_val(reg r, const std::string &val) {
        emit_tab();
        text << "xor rdx, rdx\n";
        emit_tab();
        text << "mov rcx, " << val << '\n';
        emit_tab();
        text << "div rcx\n";
    }

    std::string result() {
        return bss.str() + data.str() + text.str();
    }
};

#endif