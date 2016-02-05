#include "Grammar_FortranToCplusplus.h"

Grammar_FortranToCplusplus::Grammar_FortranToCplusplus(char* filename)
{
    reader.readFromFile(filename);
    f.open("result.txt");
}

void Grammar_FortranToCplusplus::parse()
{
    //reader.nextSymbol();

    f << "int main() {\n";

    declarations();

    command_list();

    f << "return 0;\n}\n";
}

void Grammar_FortranToCplusplus::declarations()
{
    //reader.nextSymbol();

    string type;

    if (reader.symbol("integer"))
        type = "int";
    else if (reader.symbol("real"))
        type = "double";
    else if (reader.symbol("logical"))
        type = "bool";
    else if (reader.symbol("character"))
        type = "char";
    else if (reader.symbol("!"))
    {
        comments();

        declarations();
        return;
    }

    else if (reader.symbol("\n"))
    {
        f << reader.getSymbol();
        reader.nextSymbol();

        declarations();

        return;
    }

    else return;

    reader.nextSymbol();

    if (reader.symbol(","))
    {
        reader.nextSymbol();
        if (reader.symbol("parameter"))
        {
            reader.nextSymbol();
            f << "const ";
        }

        else if (reader.symbol("dimension"))
        {
            reader.nextSymbol();
            if (reader.symbol("("))
            {
                reader.nextSymbol();

                //int difference = 1, size, to, from;
                //if (reader.type(CONST))
                //{
                std::string to = E(), size = to, from, difference = "1";
                    //to = atoi(reader.getSymbol());
                    //size = to;

                    //reader.nextSymbol();

                    if (reader.symbol(":"))
                    {
                        reader.nextSymbol();
                        //if (reader.type(CONST))
                        //{
                            from = E();
                            //from = atoi(reader.getSymbol());
                            //reader.nextSymbol();


                            size = from + "-" + to + "+1";

                            //size = from - to + 1;

                            difference = to;
                            //difference = to - 0;
                        //}
                    }
               // }

                if (reader.symbol(")"))
                {
                    reader.nextSymbol();
                }

                if (reader.symbol(":"))
                {
                    reader.nextSymbol();
                    if (reader.symbol(":"))
                    {
                        reader.nextSymbol();

                        f << type << " ";
                        if (reader.type(IDENT))
                        {
                            str_list.push_back(reader.getSymbol());
                            str_diff.push_back(difference);

                            f << reader.getSymbol() << "[" << size << "]";
                            reader.nextSymbol();
                        }

                        while (reader.symbol(","))
                        {
                            reader.nextSymbol();
                            if (reader.type(IDENT))
                            {
                                str_list.push_back(reader.getSymbol());
                                str_diff.push_back(difference);

                                f << ", " << reader.getSymbol() << "[" << size << "]";
                                reader.nextSymbol();
                            }
                        }

                        if (reader.symbol("\n"))
                        {
                            reader.nextSymbol();
                            f << ";" << '\n';

                            declarations();
                            return;
                        }

                        else if (reader.symbol("!"))
                        {
                            comments();

                            declarations();
                            return;
                        }
                    }
                }
            }
        }
    }

    f << type << " ";

    if (reader.symbol(":"))
    {
        reader.nextSymbol();
        if (reader.symbol(":"))
        {
            reader.nextSymbol();

            if (reader.type(IDENT))
            {
                f << reader.getSymbol();
                reader.nextSymbol();
                init_var();
            }

            while (reader.symbol(","))
            {
                reader.nextSymbol();
                if (reader.type(IDENT))
                {
                    f << ", " << reader.getSymbol();
                    reader.nextSymbol();
                    init_var();
                }
            }

            if (reader.symbol("\n"))
            {
                reader.nextSymbol();
                f << ";" << '\n';

                declarations();
            }

            else if (reader.symbol("!"))
            {
                f << "; ";
                comments();

                declarations();
                return;
            }
        }
    }
}

std::string Grammar_FortranToCplusplus::E()
{
    std::string str;
    str = T();

    while (reader.symbol("+") || reader.symbol("-"))
    {
        //f << reader.getSymbol();
        str = str + reader.getSymbol();

        reader.nextSymbol();
        str = str + E();
    }

    return str;
}

std::string Grammar_FortranToCplusplus::T()
{
    std::string str;

    str = F();

    while (reader.symbol("*") || reader.symbol("/"))
    {
        //f << reader.getSymbol();
        str = str + reader.getSymbol();

        reader.nextSymbol();
        str = str + T();
    }

    return str;
}

std::string Grammar_FortranToCplusplus::F()
{
    std::string str;
    if (reader.type(CONST))
    {
        //f << reader.getSymbol();
        str = reader.getSymbol();
        reader.nextSymbol();
    }

    else if (reader.type(IDENT))
    {
        string id = reader.getSymbol();
        str = str + id;
        //f << reader.getSymbol();

        reader.nextSymbol();

        if (reader.symbol("=")) // Assignment
        {
            //f << reader.getSymbol();
            str = str + "=";
            reader.nextSymbol();

            str = str + E();
        }

        else if (reader.symbol("("))
        {
            //f << "[";
            str = str + "[";
            reader.nextSymbol();

            // array element access, needs to be completed

            //if (reader.type(IDENT) || reader.type(CONST))
            //{
                //f << reader.getSymbol() << " ";
                //reader.nextSymbol();

                str = str + E();

                int index = 0;
                bool found = false;
                for (int i = 0; i < str_list.size() && !found; i++)
                    if (!strcmp(id.c_str(), str_list[i].c_str()))
                    {
                        found = true;
                        index = i;
                    }

                if (found)
                {
                    //f << "- " << str_diff[index];
                    str = str + "-" + str_diff[index];
                }


                if (reader.symbol(")"))
                {
                    //f << "]";
                    str = str + "]";
                    reader.nextSymbol();

                    if (reader.symbol("=")) // Assignment
                    {
                        //f << reader.getSymbol();
                        str = str + reader.getSymbol();
                        reader.nextSymbol();

                        str = str + E();
                    }
                }
            //}
        }
    }

    else if (reader.symbol("("))
    {
        //f << reader.getSymbol();
        str = "(";
        reader.nextSymbol();

        str = str + E();

        if (reader.symbol(")"))
        {
            //f << reader.getSymbol();
            str = str + ")";
            reader.nextSymbol();
        }
    }

    else if (reader.symbol("-"))
    {
        //f << reader.getSymbol();
        str = "-";
        reader.nextSymbol();

        str = str + E();
    }

    return str;
}

void Grammar_FortranToCplusplus::init_var()
{
    if (reader.symbol("="))
    {
        f << " " << reader.getSymbol() << " ";
        reader.nextSymbol();

        f << E();
    }
}

void Grammar_FortranToCplusplus::comments()
{
    if (reader.symbol("!"))
    {
        f << "// ";
        reader.nextSymbol();

        while (!reader.symbol("\n"))
        {
            f << reader.getSymbol() << " ";
            reader.nextSymbol();
        }

        f << "\n";
        reader.nextSymbol();
    }
}

void Grammar_FortranToCplusplus::command_list()
{
    assignment();
    if_else();
    loop();

    if (reader.symbol("!"))
    {
        comments();
        command_list();
    }

    else if (reader.symbol("\n"))
    {
        f << "\n";
        reader.nextSymbol();

        command_list();
    }

    else if (reader.symbol("if") || reader.symbol("do") || reader.type(IDENT))
    {
        command_list();
    }

}

void Grammar_FortranToCplusplus::assignment()
{
    if (reader.type(IDENT))
    {
        f << E();

        f << "; ";
        if (reader.symbol("\n"))
        {
            f << "\n";
            reader.nextSymbol();
        }

        else if (reader.symbol("!"))
        {
            comments();
        }

        //command_list();
    }
}

void Grammar_FortranToCplusplus::if_else()
{
    if (reader.symbol("if"))
    {
        f << reader.getSymbol() << " ";
        reader.nextSymbol();

        if (reader.symbol("("))
        {
            f << reader.getSymbol();
            reader.nextSymbol();

            L();

            if (reader.symbol(")"))
            {
                f << reader.getSymbol();
                reader.nextSymbol();

                if (reader.symbol("then"))
                {
                    f << "{ ";
                    reader.nextSymbol();

                    if (reader.symbol("\n"))
                    {
                        f << "\n";
                        reader.nextSymbol();
                    }

                    else if (reader.symbol("!"))
                    {
                        comments();
                    }

                    command_list();

                    f << "} \n";

                    if (reader.symbol("else"))
                    {
                        f << "else ";
                        reader.nextSymbol();

                        if (reader.symbol("if"))
                        {
                            if_else();
                        }

                        else
                        {
                            f << "{\n ";
                            command_list();
                            f << "} \n";
                        }
                    }

                    if (reader.symbol("end"))
                    {
                        reader.nextSymbol();
                        if (reader.symbol("if"))
                        {
                            reader.nextSymbol();
                        }

                    }
                }
            }
        }

        //command_list();
    }
}

void Grammar_FortranToCplusplus::loop()
{
    string init, fin, step = "1", comp = " <= ", counter = "+";
    if (reader.symbol("do"))
    {
        f << "for (";
        reader.nextSymbol();

        if (reader.type(IDENT))
        {
            init = reader.getSymbol();
            f << reader.getSymbol();
            reader.nextSymbol();

            if (reader.symbol("="))
            {
                f << "=";
                reader.nextSymbol();

                f << E();

                f << "; ";
            }

            if (reader.symbol(","))
            {
                f << init;
                reader.nextSymbol();

                fin = reader.getSymbol();
                reader.nextSymbol();

                if (reader.symbol(","))
                {
                    reader.nextSymbol();
                    step = reader.getSymbol();

                    reader.nextSymbol();
                }

                int a = atoi(step.c_str());

                if (a < 0)
                {
                    comp = " >= ";
                    counter = "";
                }


                f << comp << fin << "; " << init << "=" << init << counter << step << ")\n{";

                //reader.nextSymbol();
                command_list();

                if (reader.symbol("end"))
                {
                    reader.nextSymbol();
                    if (reader.symbol("do"))
                    {
                        reader.nextSymbol();
                        f << "}\n";
                    }
                }
            }
        }

        //command_list();
    }
}

void Grammar_FortranToCplusplus::L()
{
    if (reader.symbol("."))
    {
        reader.nextSymbol();
        if (reader.symbol("not"))
        {
            f << "!";
            reader.nextSymbol();
            reader.nextSymbol();
        }
    }

    f << E();
    RelOp();
    f << E();

    if (reader.symbol("."))
    {
        reader.nextSymbol();
        while (reader.symbol("or") || reader.symbol("and"))
        {
            if (reader.symbol("or"))
            {
                f << " || ";
            }

            else f << " && ";

            reader.nextSymbol(); // ignore the other dot
            reader.nextSymbol();
            L();
        }
    }
}

void Grammar_FortranToCplusplus::RelOp()
{
    if (reader.symbol("."))
    {
        reader.nextSymbol();
        if (reader.symbol("gt"))
            f << ">";

        else if (reader.symbol("lt"))
            f << "<";

        else if (reader.symbol("le"))
            f << "<=";

        else if (reader.symbol("eq"))
            f << "==";

        else if (reader.symbol("ne"))
            f << "!=";

        else if (reader.symbol("ge"))
            f << ">=";

        reader.nextSymbol();
        reader.nextSymbol();
    }

    else
    {
        if (reader.symbol("/"))
        {
            f << "!";
            reader.nextSymbol();

            if (reader.symbol("="))
            {
                f << "=";
                reader.nextSymbol();
            }
        }

        else if (reader.symbol("<") || reader.symbol(">") || reader.symbol("="))
        {
            f << reader.getSymbol();
            reader.nextSymbol();

            if (reader.symbol("="))
            {
                f << "=";
                reader.nextSymbol();
            }
        }
    }
}




