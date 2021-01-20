#pragma once
#include "Lexer.h"

typedef enum
{

	Stmt = 1,
	Expr = 2,
	Fun = 3
}ParseTokens;

std::string ParseTokens_Tostring(ParseTokens a)
{
	switch (a)
	{
	case Stmt:
		return "Stmt"; break;
	case Expr:
		return "Expr"; break;
	case Fun: 
		return "Fun"; break;
	}
}


class Parser
{
	std::vector<ParseTokens> pt;
	std::string Tok_List_toString(std::vector<Tokens> t)
	{
		std::string ret = "";
		for (auto a : t)
		{
			
			ret += to_string(a);
			ret += '_';
		}
		return ret;
	}
	bool isStmt(std::string& f)
	{
		std::regex stmt("^(TypeDeclr_)*Var_name_(Equal_Numeric_literal_)*");
		return std::regex_match(f, stmt);
	}
	bool isExpr(std::string& f)
	{
		std::regex expr("If_Var_name_Bool_Op_Var_name_");
		return std::regex_match(f, expr);
	}
	bool isFunc(std::string& f)
	{
		std::regex expr("Function_(TypeDeclr_)*Var_name_");
		return std::regex_match(f, expr);
	}
	void getParseTokens(std::string& f)
	{
		if (isStmt(f))
		{
			pt.push_back(Stmt);
		}
		if (isExpr(f))
		{
			pt.push_back(Expr);
		}
		if (isFunc(f))
		{
			pt.push_back(Fun);
		}
	}
	void evalParsed(std::vector<Tokens> t)
	{
		auto a = Tok_List_toString(t);
		getParseTokens(a);
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
	void logParseTokens()
	{
		for (auto& a : pt)
		{
			
			std::cout << ParseTokens_Tostring(a) << std::endl;
		}
	} 
};