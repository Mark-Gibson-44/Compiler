#pragma once
#include "Lexer.h"

typedef enum
{
	Stmt = 1,
	Expr = 2,
	Fun = 3
}ParseTokens;

class Parser
{

	std::string Tok_List_toString(std::vector<Tokens> t)
	{
		std::string ret = "";
		for (auto a : t)
		{
			
			int temp = a;
			auto g = std::to_string(temp);
			ret += (g);
			ret += '_';
		}
		return ret;
	}
	void evalParsed(std::vector<Tokens> t)
	{
		std::cout << Tok_List_toString(t) << std::endl;
	}
public:
	Parser(std::vector<Tokens> Lexeme)
	{
		std::vector<Tokens> curParse;
		for (auto a : Lexeme)
		{
			if (a == Tok_semi)
			{
				evalParsed(curParse);
				curParse.clear();
			}
			else
				curParse.push_back(a);
		}
		//Parse stuff idk
	}
};