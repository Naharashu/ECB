#ifndef AST_ECB_H
#define AST_ECB_H

#include "ecb.h"
#include <cstdint>
#include <cstring>
#include <array>
#include <type_traits>
#include <valarray>



std::vector<uint8_t> slice64(uint64_t i) {
    std::vector<uint8_t> res;
    for(int j=0;j<8;j++) res.emplace_back(uint8_t((i >> 8*(7 - i)) & 0xFF));
    return res;
}

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual std::vector<uint8_t> gen() {
        return {};
    }
};

struct ValueNode : ASTNode { 
    uint64_t i=0;
    bool minus=false;
    explicit ValueNode(uint64_t i_, bool m=false) : i(i_), minus(m) {}
    std::vector<uint8_t> gen() override {
        if(!minus) {
            return slice64(i);
        } else {
            return slices(
        }
    }
}

#endif