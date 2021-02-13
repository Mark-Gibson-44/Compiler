
#include "Parser.h"
#include "semantics.h"

int main()
{
	Lexer t("testLang.txt");
	
	//t.LogTokens();
	//t.varInfo();
//	Parser p(t.getLexed());
	//p.logParseTokens();
	
	Semantics s(t.getLexed());
	

	
}