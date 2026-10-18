/*
AI disclosure: Starter outline only. 
The logic in this file was written by Shalom Mantey Addison.
*/

#include <cctype> 
#include <iostream> 
#include <string> 
#include <unordered_set> 
#include <vector>

using namespace std;
enum class TokenType { 
    Keyword, 
    Identifier, 
    Integer, 
    Operator, 
    Semicolon, 
    LeftParen, 
    RightParen, 
    Unknown 
};

struct Token { TokenType type; string value; 
};

string tokenTypeName(TokenType type) { 
    switch (type) { 
        case TokenType::Keyword:    return "KEYWORD"; 
        case TokenType::Identifier: return "IDENTIFIER"; 
        case TokenType::Integer:    return "INTEGER"; 
        case TokenType::Operator:   return "OPERATOR"; 
        case TokenType::Semicolon:  return "SEMICOLON"; 
        case TokenType::LeftParen:  return "LEFT_PAREN"; 
        case TokenType::RightParen: return "RIGHT_PAREN"; 
        default:                    return "UNKNOWN";
                  }
}