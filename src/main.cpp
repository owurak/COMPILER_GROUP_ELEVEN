/*
Integration note:
The previous main.cpp used a scanner interface incompatible with the agreed
Lexer/getNextToken API. This file was replaced and tested by Member 1.

AI disclosure: AI assistance was used for entry-point boilerplate only.
The integration was reviewed and tested by the member.
*/

#include <fstream>
#include <iostream>
#include <sstream>

#include "lexer/lexer.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source-file>\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Error: cannot open file '" << argv[1] << "'\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    Lexer lexer(buffer.str());

    int count = 0;
    int errors = 0;

    while (true) {
        Token t = lexer.getNextToken();

        if (t.type == TokenType::END_OF_FILE) {
            std::cout << "END_OF_FILE " << t.line << ":" << t.column << "\n";
            break;
        }

        std::cout << tokenTypeToString(t.type) << "(" << t.lexeme << ") "
                  << t.line << ":" << t.column << "\n";

        count++;

        if (t.type == TokenType::INVALID) {
            errors++;
        }
    }

    std::cerr << "Total tokens: " << count
              << ", invalid: " << errors << "\n";

    return errors == 0 ? 0 : 2;
}