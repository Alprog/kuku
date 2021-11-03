
#include "Grammar.h"

int main()
{
    Grammar grammar;

    grammar.RegTerminals("id +- */ ( ) ε");

    grammar.RegNonTerminal("Exp", "Term Exp'");
    grammar.RegNonTerminal("Exp'", "+- Term Exp'", "ε");


    grammar.RegNonTerminal("Term", "Factor */ Factor");
    grammar.RegNonTerminal("Factor", "( Exp )", "id");

    grammar.Finish();

    return 0;
}