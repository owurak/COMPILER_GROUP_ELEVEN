#pragma once
#include <string>

enum class TokenType {
    KEYWORD, IDENTIFIER, INTEGER, FLOAT, STRING,
    OPERATOR, PUNCTUATION, END_OF_FILE, INVALID
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

std::string tokenTypeToString(TokenType type);