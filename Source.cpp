
#include "Parser.h"
int main()
{
	Lexer t("testLang.txt");
	Parser p(t.getLexed());
}