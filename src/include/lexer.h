#ifndef LEXER_ECB_H
#define LEXER_ECB_H

#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>
enum token_type : uint8_t {
    INT,
    ID,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    OR_,
    AND_,
    EQ,
    EQUAL,
    NOT_EQUAL,
    LESS,
    BIGGER,
    LEQ,
    BEQ,
    AND_L,
    OR_L,
    NOT,
    L_BRACKET,
    R_BRACKET,
    L_BRACE,
    R_BRACE,
    DOT,
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
    double f;
    uint64_t l;
    uint64_t c;

    static token make(enum token_type t_, std::string s, int64_t i_, uint64_t l, uint64_t c, double f=0) {
        return token{t_, s, i_, f, l,c};
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
            if(isalpha(c)==0) {
                std::string id;
                while(((isalpha(code[i])==0)||code[i]=='_'||(isdigit(code[i])==0))&&i<size) {
                    id.push_back(code[i]);
                    i++;
                    char_++;
                }
                lexed.push_back(token::make(ID, id, 0, line, char_));
                break;
            }
            if(isdigit(c)==0) {
                std::string number;
                bool float_ = false;
                while((code[i]=='.'||(isdigit(code[i])==0))&&i<size) {
                    if(code[i]=='.') float_=true;
                    number.push_back(code[i]);
                    i++;
                    char_++;
                }

                char* endptr;
                if(float_) {
                    double val = strtod(number.c_str(), &endptr);
                    lexed.push_back(token::make(FLOAT, "", 0, line, char_, val));
                } else {
                    int64_t val = strtoll(number.c_str(), &endptr, 10);
                    lexed.push_back(token::make(INT, "", val, line, char_));
                }
                break;
            }
            uint8_t n = i + 1 < size ? code[i+1] : 0;
            switch (c) {
                case '\t':
                case '\r':
                case ' ':
                    i++;
                    char_++;
                    break;
                case '+': {
                    i++;
                    
                    lexed.push_back(token::make(PLUS, "", 0, line, char_++));
                    break;
                }
                case '-': {
                    i++;
                    
                    lexed.push_back(token::make(MINUS, "", 0, line, char_++));
                    break;
                }
                case '*': {
                    i++;
                    
                    lexed.push_back(token::make(STAR, "", 0, line, char_++));
                    break;
                }
                case '/': {
                    i++;
                    
                    if(n=='/') {
                        while(i<size&&code[i]!='\n') {
                            i++;
                        }
                        break;
                    }
                    if(n=='*') {
                        while(i+1<size&&code[i]!='*'&&code[i+1]!='/') {
                            i++;
                        }
                        break;
                    }
                    lexed.push_back(token::make(SLASH, "", 0, line, char_++));
                    break;
                }
                case '(': {
                    i++;
                    
                    lexed.push_back(token::make(L_BRACKET, "", 0, line, char_++));
                    break;
                }
                case ')': {
                    i++;
                    
                    lexed.push_back(token::make(R_BRACKET, "", 0, line, char_++));
                    break;
                }
                case '{': {
                    i++;
                    
                    lexed.push_back(token::make(L_BRACE, "", 0, line, char_++));
                    break;
                }
                case '}': {
                    i++;
                    
                    lexed.push_back(token::make(R_BRACE, "", 0, line, char_++));
                    break;
                }
                case '=': {
                    i++;
                    
                    if(n=='=') {
                        i++;
                        
                        lexed.push_back(token::make(EQUAL, "", 0, line, char_++));
                        break;
                    }
                    lexed.push_back(token::make(EQ, "", 0, line, char_++));
                    break;
                }
                case '!': {
                    i++;
                    
                    if(n=='=') {
                        i++;
                        
                        lexed.push_back(token::make(NOT_EQUAL, "", 0, line, char_++));
                        break;
                    }
                    lexed.push_back(token::make(NOT, "", 0, line, char_++));
                    break;
                }
                case '<': {
                    i++;
                    
                    if(n=='=') {
                        i++;
                        
                        lexed.push_back(token::make(LEQ, "", 0, line, char_++));
                        break;
                    }
                    lexed.push_back(token::make(LESS, "", 0, line, char_++));
                    break;
                }
                case '>': {
                    i++;
                    
                    if(n=='=') {
                        i++;
                        
                        lexed.push_back(token::make(BEQ, "", 0, line, char_++));
                        break;
                    }
                    lexed.push_back(token::make(BIGGER, "", 0, line, char_++));
                    break;
                }
                case '|': {
                    i++;
                    
                    if(n=='|') {
                        i++;
                        
                        lexed.push_back(token::make(OR_L, "", 0, line, char_++));
                        break;
                    }
                    lexed.push_back(token::make(OR_, "", 0, line, char_++));
                    break;
                }
                case '&': {
                    i++;
                    
                    if(n=='&') {
                        i++;
                        
                        lexed.push_back(token::make(AND_L, "", 0, line, char_++));
                        break;
                    }
                    lexed.push_back(token::make(AND_, "", 0, line, char_++));
                    break;
                }
                case '.': {
                    i++;
                    lexed.push_back(token::make(DOT, "", 0, line, char_++));
                    break;
                }
                case '\n': {
                    line++;
                    char_=0;
                    break;
                }
            }
        }
        lexed.push_back(token::make(EOF_, "", 0, 0, 0));
    }
};

#endif