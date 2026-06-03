#ifndef LEXER_ECB_H
#define LEXER_ECB_H

#include <cstdint>
#include <string>
#include <vector>
enum token_type : uint8_t {
    INT,
    ID,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EQ,
    EQUAL,
    L_BRACKET,
    R_BRACKET,
    L_BRACE,
    R_BRACE,
    FLOAT,
    STRING,
    TRUE,
    FALSE,
    DEFINE,
    RETURN,
    GOTO,
    IF,
    ELIF,
    ELSE,
    PHI,
    EOF_
} token_type;

struct token {
    enum token_type t;
    std::string str_val;
    int64_t i;
    std::string id;
    uint64_t l;
    uint64_t c;

    static token make(enum token_type t_, std::string s, int64_t i_, std::string id_, uint64_t l, uint64_t c) {
        return token{t_, s, i_, id_, l,c};
    }
};

struct lexer {
    std::vector<token> lexed;
    std::string code;
    void lex() {
        uint64_t line = 0;
        uint64_t char_ = 0;
        uint64_t size = code.size();
        for(uint64_t i=0;i<size;) {
            uint8_t c = code[i];
            switch (c) {
                case '+': {
                    i++;
                    lexed.push_back(token::make(PLUS, "", 0, "", l, ++char_));
                }
            }
        }
    }
};

#endif