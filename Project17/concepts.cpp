#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define EOF_CODE 99

enum CharClass { LETTER, DIGIT, UNKNOWN, EOF_CHAR };
CharClass charClass;
char nextChar;
int nextToken;
string lexeme;
istream* inputSource = nullptr;

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (inputSource && inputSource->get(nextChar)) {
        if (isalpha(nextChar)) charClass = LETTER;
        else if (isdigit(nextChar)) charClass = DIGIT;
        else charClass = UNKNOWN;
    }
    else {
        charClass = EOF_CHAR;
    }
}

void getNonBlank() {
    while (isspace(nextChar)) {
        getChar();
    }
}

int lookup(char ch) {
    switch (ch) {
    case '(': addChar(); return LEFT_PAREN;
    case ')': addChar(); return RIGHT_PAREN;
    case '+': addChar(); return ADD_OP;
    case '-': addChar(); return SUB_OP;
    case '*': addChar(); return MULT_OP;
    case '/': addChar(); return DIV_OP;
    case '=': addChar(); return ASSIGN_OP;
    default: addChar(); return EOF_CODE;
    }
}

int lex() {
    lexeme.clear();
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar(); getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar(); getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar(); getChar();
        while (charClass == DIGIT) {
            addChar(); getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        nextToken = lookup(nextChar);
        getChar();
        break;
    case EOF_CHAR:
        lexeme = "EOF";
        nextToken = EOF_CODE;
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

vector<pair<int, string>> tokenize(const string& input) {
    vector<pair<int, string>> tokens;
    istringstream inputStream(input);
    inputSource = &inputStream;

    getChar();
    do {
        lex();
        tokens.emplace_back(nextToken, lexeme);
    } while (nextToken != EOF_CODE);

    return tokens;
}

map<string, string> createSymbolTable(const vector<pair<int, string>>& tokens) {
    map<string, string> table;
    for (const auto& token : tokens) {
        if (token.first == IDENT) {
            table[token.second] = "variable";
        }
    }
    return table;
}

int main() {
    ifstream file("front.in");
    if (file.is_open()) {
        inputSource = &file;
        getChar();
        do {
            lex();
        } while (nextToken != EOF_CODE);
        file.close();
    }
    else {
        cout << "front.in not found, skipping file input.\n";
    }

    string input = "(sum + 47) / total = 5";
    cout << "\nTokenizing from string: " << input << endl;
    vector<pair<int, string>> tokens = tokenize(input);

    cout << "\nTokens:\n";
    for (const auto& token : tokens) {
        cout << "Token: " << token.first << ", Lexeme: " << token.second << endl;
    }

    auto symbolTable = createSymbolTable(tokens);
    cout << "\nSymbol Table:\n";
    for (const auto& entry : symbolTable) {
        cout << entry.first << ": " << entry.second << endl;
    }

    return 0;
}
https://github.com/toaaramadanewis1111/Project15/blob/dea1bf4952fd836f93675073744deaab97a000d5/Project15/concepts.cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define L_PAREN 25
#define R_PAREN 26
#define EXP_OP 27
#define SEMICOLON 28
#define FOR 29
#define L_BRACE 30
#define R_BRACE 31
#define End_OF_File -1

int charClass;
string lexeme;
char nextChar;
int nextToken;
string input;
size_t pos = 0;

void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);
string Token_type(int token);

int main() {
    cout << "Enter an expression:   ";
    getline(cin, input);

    getChar();
    do {
        lex();
    } while (nextToken != End_OF_File);

    return 0;
}

string Token_type(int token) {
    switch (token) {
    case INT_LIT: return "INTEGER LITERAL";
    case IDENT: return "IDENTIFIER";
    case ASSIGN_OP: return "ASSIGNMENT OPERATOR";
    case ADD_OP: return "ADDITION OPERATOR";
    case SUB_OP: return "SUBTRACTION OPERATOR";
    case MULT_OP: return "MULTIPLICATION OPERATOR";
    case DIV_OP: return "DIVISION OPERATOR";
    case L_PAREN: return "LEFT PARENTHESIS";
    case R_PAREN: return "RIGHT PARENTHESIS";
    case EXP_OP: return "EXPONENT OPERATOR";
    case SEMICOLON: return "SEMICOLON";
    case FOR: return "FOR";
    case L_BRACE: return "LEFT BRACE";
    case R_BRACE: return "RIGHT BRACE";
    case End_OF_File: return "END OF FILE";
    default: return "UNKNOWN TOKEN";
    }
}

int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = L_PAREN;
        break;
    case ')':
        addChar();
        nextToken = R_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    case ';':
        addChar();
        nextToken = SEMICOLON;
        break;
    case '{':
        addChar();
        nextToken = L_BRACE;
        break;
    case '}':
        addChar();
        nextToken = R_BRACE;
        break;
    default:
        addChar();
        nextToken = End_OF_File;
        break;
    }
    return nextToken;
}

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (pos < input.length()) {
        nextChar = input[pos++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = End_OF_File;
    }
}

void getNonBlank() {
    while (isspace(nextChar) && charClass != End_OF_File)
        getChar();
}

int lex() {
    lexeme = "";
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while ((charClass == LETTER || charClass == DIGIT) && charClass != End_OF_File) {
            addChar();
            getChar();
        }
        if (lexeme == "for") {
            nextToken = FOR;
        }
        else {
            nextToken = IDENT;
        }
        break;

    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT && charClass != End_OF_File) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

    case End_OF_File:
        nextToken = End_OF_File;
        lexeme = "End_OF_File";
        break;
    }

    if (nextToken != End_OF_File) {
        cout << "Next token is: " << nextToken << " (" << Token_type(nextToken)
            << "), Next lexeme is '" << lexeme << "'" << endl;
    }
    return nextToken;
}

Transcom % 1552005
https://github.com/JilanHany/Project16/tree/8e81a3320ca539d7b130202f5bf8844ff6bcdfca/Project16
#include <stdio.h>
#include <ctype.h>
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int nextToken;
FILE* in_fp;
void addChar();
void getChar();
void getNonBlank();int lex();
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define MULT_OP 23
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
int main() {
    if ((in_fp = fopen("input.txt", "r")) == NULL)
        printf("ERROR - cannot open input.txt \n");
    else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }
}
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else {
        printf("Error - lexeme is too long \n");
    }
}
void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;else if (isdigit(nextChar))
            charClass = DIGIT;
            else
    }
    else {
        charClass = UNKNOWN;
        charClass = EOF;
    }
}
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}
int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}
