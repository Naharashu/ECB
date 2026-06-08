#ifndef GENERATOR_ECB_H
#define GENERATOR_ECB_H

#include <sstream>
#include <vector>
#include <cstdint>
#include "ecb.h"
#include <array>

#define STACK_SIZE 4096
#define CALL_STACK_SIZE 16384
#define MEMORY_SIZE 65536

enum variable_type : uint8_t {
    BYTE_T,
    SHORT_T,
    INT_T,
    LONG_T,
    BOOL_T,
    STRING_T
};

enum opcodes : uint8_t {
    NOP,
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    EXIT
};

#define VM_EXIT_OK 0
#define VM_EXIT_FAILURE 1
#define VM_EXIT_STACK_OVERFLOW 2
#define VM_EXIT_CALL_STACK_OVERFLOW 3

struct vm {
    std::array<uint8_t, MEMORY_SIZE> memory;
    bool zf = false;
    bool less = false;
    bool bigger = false;

    std::array<int64_t, 32> reg;
    uint32_t sp = 0;
    uint32_t csp = 0;
    uint32_t pc = 0;
    
    std::array<uint32_t, STACK_SIZE> stack;
    std::array<uint32_t, CALL_STACK_SIZE> callstack;

    int run();
    void load_program(const std::vector<uint8_t> &program);
};

#endif