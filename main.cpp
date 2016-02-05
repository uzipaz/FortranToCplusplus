#include "SymbolReader.h"
#include "Grammar_FortranToCplusplus.h"

int main()
{

  /*  int i;
    SymbolReader reader("input.txt");

    i = 1;

    while(!reader.hasReadAll())
    {

        cout << "TOKEN " << i << ": " << reader.getSymbol() << '\n';

        i++;

        reader.nextSymbol();
    }*/


   Grammar_FortranToCplusplus g("input.txt");
    g.parse();

    return 0;
}
