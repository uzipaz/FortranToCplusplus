#ifndef SYMBOLREADER_H_INCLUDED
#define SYMBOLREADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#include "miscellaneous.h"

const int NumOfKeywords = 52;
const int NumOfIgnoreKeys = 2;
const int StrSizeKeywords = 32;

enum abstract_type
{
    KEYWORD = 0,
    IDENT = 1,
    CONST = 2
};

struct Symbol
{
    abstract_type type;
    char symbol[StrSizeKeywords];
};

const char keyword[NumOfKeywords][StrSizeKeywords] = {
{"parameter"},
{"dimension"},
{"program"},
{"if"},
{"else"},
{"implicit"},
{"none"},
{"end"},
{"true"},
{"false"},
{"then"},
{"do"},
{"integer"},
{"real"},
{"logical"},
{"complex"},
{"character"},
{"len"},
{"and"},
{"or"},
{"not"},
{"eqv"},
{"neqv"},
{"select"},
{"case"},
{"default"},
{"lt"},
{"le"},
{"eq"},
{"ge"},
{"gt"},
{"ne"},
//{"'"},
//{""""},
{"("},
{")"},
{"*"},
{"+"},
{"-"},
{"/"},
{":"},
{"="},
{"_"},
{"!"},
{"&"},
{"$"},
{";"},
{"<"},
{">"},
{"%"},
{"?"},
{","},
{"."},
{10}
};

const char ignoreChar[NumOfIgnoreKeys] = {32, 9}; // space, newline, horizontal tab

class SymbolReader
{
public:
    SymbolReader();
    SymbolReader(char* filename);
    SymbolReader(SymbolReader& reader);

    void readFromFile(char* filename);

    void nextSymbol();

    char* getSymbol();

    bool symbol(char* str);
    bool type(abstract_type t);

    bool hasReadAll();

    ~SymbolReader();
private:
    Symbol currentSymbol;

    bool MatchStatus[NumOfKeywords + 2]; // Acounting for Regular Expressions (Identifiers, constants)
    ifstream f;
};


#endif // SYMBOLREADER_H_INCLUDED
