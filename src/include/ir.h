#ifndef IR_H
#define IR_H

#include <cstdint>
enum token : uint8_t {
    INT,
    ID,
    EQ,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    L_BRACKET,
    R_BRACKET,
    
} token;

#endif