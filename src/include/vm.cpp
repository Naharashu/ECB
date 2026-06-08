#include "vm.h"
#include <cstdint>
#include <vector>

void vm::load_program(const std::vector<uint8_t> &program) {
    for(uint32_t i=0;(i<memory.size()&&i<program.size());i++) {
        memory[i] = program[i];
    }
}

int vm::run() {
    #define FETCH (this->memory[i++])
    for(uint32_t i=0;i<memory.size();) {
        uint8_t opcode = FETCH;
        switch (opcode) {
            case NOP: continue;
            case MOV: {
                uint8_t r = FETCH;
            }
            case EXIT: {
                return (int)this->reg[FETCH%31];
            }
        }
    }
    #undef FETCH
    return VM_EXIT_FAILURE;
}