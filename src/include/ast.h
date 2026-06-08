#ifndef AST_ECB_H
#define AST_ECB_H

#include "ecb.h"
#include "generator.h"
#include <cstdint>
#include <cstring>
#include <array>
#include <memory>
#include <string>
#include <type_traits>
#include <valarray>



std::vector<uint8_t> slice64(uint64_t i) {
    std::vector<uint8_t> res;
    for(int j=0;j<8;j++) res.emplace_back(uint8_t((i >> 8*(7 - i)) & 0xFF));
    return res;
}

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void gen(generator& g) {
        return;
    }
};

using astptr = std::unique_ptr<ASTNode>;

struct ValueNode : ASTNode { 
    uint64_t i=0;
    explicit ValueNode(uint64_t i_) : i(i_) {}
    void gen(generator& g) override {
        g.emit(g.text, std::to_string(i));
    }
};

struct AssignVar : ASTNode {
    std::string varname;
    variable_type t;
    std::string value;
    AssignVar(const std::string &name, const variable_type &type, const std::string &val) : varname(name), t(type), value(val) {}
    void gen(generator &g) override {
        g.declare_var_val(t, varname, value);
    }
};

struct Block : ASTNode {
    std::vector<astptr> nodes;
    explicit Block(std::vector<astptr> n) : nodes(std::move(n)) {}
    void gen(generator &g) override {
        for(auto &s : nodes) {
            s->gen(g);
        }
    }
};

struct Function : ASTNode {
    std::string name;
    std::unique_ptr<ASTNode> block;
    
}
 
#endif