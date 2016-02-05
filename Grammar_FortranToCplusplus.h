#ifndef GRAMMAR_FORTRANTOCPLUSPLUS_H_INCLUDED
#define GRAMMAR_FORTRANTOCPLUSPLUS_H_INCLUDED

#include "SymbolReader.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Grammar_FortranToCplusplus
{
public:
    Grammar_FortranToCplusplus(char* filename);

    void parse();

private:
    void declarations();
    void init_var();
    void comments();

    void command_list();
    void assignment();
    void if_else();
    void loop();

    std::string E();
    std::string T();
    std::string F();

    void L();
    void RelOp();

    ofstream f;

    SymbolReader reader;

    vector<std::string> str_list;
    vector<std::string> str_diff;
};

#endif // GRAMMAR_FORTRANTOCPLUSPLUS_H_INCLUDED
