/*
AI disclosure: Starter outline only. 
The logic in this file was written by Shalom Mantey Addison.
*/

#include <iostream> 
#include <string> 
#include <vector> 
#include "lexer.h"

using namespace std;

int main() { string source = "int age = 23; print(age);";
    vector<Token> tokens = scan(source);

for (const Token& token : tokens) {
    cout << tokenTypeName(token.type)
         << ": " << token.value << endl;
}

return 0;
}