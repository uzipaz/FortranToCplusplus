#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include "SymbolReader.h"
#include <iostream>

class Grammar
{
public:
    Grammar(SymbolReader reader)
    {
        this->reader = reader;
    }

    virtual void parse() = 0;

protected:
    SymbolReader reader;

private:

};

#endif // GRAMMAR_H_INCLUDED
