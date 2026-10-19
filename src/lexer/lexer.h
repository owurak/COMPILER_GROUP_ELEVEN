#pragma once
#include <string>
#include "token.h"

// MEMBER 1 - Lexer interface

class Lexer {
public:
    explicit Lexer(const std::string& source);
    Token getNextToken();
    bool isAtEnd() const;
private:
    std::string src;
    size_t pos;
    int line;
    int column;
    char peek() const;
    char advance();
    void skipWhitespaceAndComments();
    Token readIdentifierOrKeyword();
    Token readNumber();
};