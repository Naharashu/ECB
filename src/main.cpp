#include "include/ecb.h"
#include "include/generator.h"
#include <string>

int main() {
    generator g;
    g.init();
    g.emit(g.generated, std::string("_main:"));
    return 0;
}