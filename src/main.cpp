#include "include/ecb.h"
#include "include/generator.h"
#include <iostream>
#include <string>

int main() {
    generator g;
    g.init();
    g.declare_var_bss(SHORT_T, "x", 1);
    g.start_label("main");
    g.mov_int(reg::rax, "30");
    g.add_reg_val(reg::rax, "10");
    g.set_var_val_reg("x", reg::rax);
    g.mov_var(reg::rax, "x");
    g.ret();
    g.end_label();
    std::cout << g.result();
    return 0;
}