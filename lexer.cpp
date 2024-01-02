#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

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

static std::string IdentifierStr;
static double NumVal;

// Reads from stdin and groups into tokens
static int gettok() {
    static int LastChar = ' ';

    // skip whitespace
    while (isspace(LastChar)) 
        LastChar = getchar();

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;
        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern") {
            return tok_extern;
        }
        // identifier if not "def" or "extern"
        return tok_identifier;
    }

    // Converts number to double and stores in numval
    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        // bool readDecimal = false;
        do {
            // if (LastChar == '.') {
            //     if (readDecimal) {
            //         return tok_error;
            //     }
            //     readDecimal = true;
            //}
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0); // parsers a floating point number from a string
        return tok_number;
    }

    // Handles comments
    if (LastChar == '#') {
        do 
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF) {
            return gettok();
        }
    }

    // Check for end of file
    if (LastChar == EOF)
        return tok_eof;
    
    // If none of above cases, return characer as ascii value
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}