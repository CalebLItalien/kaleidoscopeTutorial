#ifndef LEXER_H
#define LEXER_H

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Different types of tokens the lexer can recognize
enum Token {
    // end of file
    tok_eof = -1,
    
    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,

    // error
    // tok_error = -99,
};

extern std::string IdentifierStr;
extern double NumVal;

int gettok();

#endif // LEXER_H
