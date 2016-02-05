#include "SymbolReader.h"

SymbolReader::SymbolReader(char* filename)
{
    f.open(filename);
    if (!f.is_open())
        std::cout << "Couldn't open input file\n";

    this->nextSymbol();
}

SymbolReader::SymbolReader()
{

}

SymbolReader::SymbolReader(SymbolReader& reader)
{
}

void SymbolReader::readFromFile(char* filename)
{
    f.open(filename);
    if (!f.is_open())
        std::cout << "Couldn't open input file\n";

    this->nextSymbol();
}

void SymbolReader::nextSymbol()
{
    int i, j, k;
    char currentChar;
    bool IsMatch = false, ignoreFlag = true;

    initList(MatchStatus, NumOfKeywords + 2, true);
    initList(currentSymbol.symbol, StrSizeKeywords, '\0');

    while (ignoreFlag && !hasReadAll()) // First ignore unnecessary symbols
    {
        f.get(currentChar);

        ignoreFlag = false;
        for (int i = 0; i < NumOfIgnoreKeys && !ignoreFlag; i++)
            if (currentChar == ignoreChar[i])
                ignoreFlag = true; // if matches, then we have to ignore this symbol, otherwise we cannot
    }

    for (i = 0; i < StrSizeKeywords - 1 && !f.eof() && !IsMatch; i++)
    {
        currentChar = tolower(currentChar); // convert to lowercase

        //For all keywords and symbols

        for (j = 0, k = j + 2; j < NumOfKeywords && !IsMatch; j++, k++)
        {
            // 'k' Ignoring the regular expressions
            if (MatchStatus[k] == true)
            {
                if (i < (signed)strlen(keyword[j]) - 1) // Added signed cast for the purpose of removing warning at code compilation
                {
                    if (currentChar == keyword[j][i])
                        currentSymbol.symbol[i] = currentChar;

                    else MatchStatus[k] = false;
                }

                else
                {
                    if (currentChar == keyword[j][i])
                    {
                        currentSymbol.symbol[i] = currentChar;

                        currentSymbol.type = KEYWORD;
                        IsMatch = true; // We have a match!

                        MatchStatus[0] = false;
                        MatchStatus[1] = false;
                    }

                    else MatchStatus[k] = false;
                }
            }
        }

        // Identifier
        if (MatchStatus[0] == true)
        {
            if (i == 0)
            {
                if (isalpha(currentChar))
                    currentSymbol.symbol[i] = currentChar;

                else MatchStatus[0] = false;
            }

            else
            {
                if (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_')
                    currentSymbol.symbol[i] = currentChar;

                else
                {
                    //if (currentSymbol.type != KEYWORD)
                        currentSymbol.type = IDENT;

                    IsMatch = true;
                    f.putback(currentChar);
                }; // We have a match!
            }
        }

        // Const (Remaining: Floating point values, signed constants)
        if (MatchStatus[1] == true)
        {
            if (i == 0)
            {
                if (isdigit(currentChar))
                    currentSymbol.symbol[i] = currentChar;

                else if (currentChar == '-' || currentChar == '+')
                    currentSymbol.symbol[i] = currentChar;

                else MatchStatus[1] = false;
            }

            else
            {
                if (isdigit(currentChar))
                    currentSymbol.symbol[i] = currentChar;

                else
                {
                    currentSymbol.type = CONST;
                    IsMatch = true; // We have a match!
                    f.putback(currentChar);
                }
            }
        }

        if (!IsMatch)
            f.get(currentChar);
    }

    currentSymbol.symbol[i] = '\0';
}

bool SymbolReader::symbol(char* str)
{
    return !strcmp(str, currentSymbol.symbol); // Return true if equal else return false
}

bool SymbolReader::type(abstract_type t)
{
    return t == currentSymbol.type;
}

char* SymbolReader::getSymbol()
{
    return currentSymbol.symbol;
}

bool SymbolReader::hasReadAll()
{
    return f.eof();
}

SymbolReader::~SymbolReader()
{
    if (f.is_open())
        f.close();
}


