#pragma once
#include <vector>
#include <fstream>
#include <regex>
#include <functional>
#include <iostream>

typedef enum {
	Tok_type_decl = 1,
	Tok_arithmetic_op = 2,
	Tok_varName = 3,
	Tok_bool_op = 4,
	Tok_semi = 5,
	Tok_fun = 6,
	Tok_invalid = 7

} Tokens;

class Lexer
{

public:
	std::vector<Tokens> program;
	std::string curLexeme = "";
	
	bool evalTypeDeclr(std::string lex)
	{
		std::regex Types("^(int|char|bool)$");
		return std::regex_match(lex, Types);
	}
	bool evalArithmeticOp(std::string& lex)
	{
		std::regex ArithOps("^(+|/|-|*)$");
		return std::regex_match(lex, ArithOps);
	}
	bool evalVarName(std::string& lex)
	{
		std::regex VarName("^[a-zA-Z]$");
		return std::regex_match(lex, VarName);
	}
	bool evalBoolOp(std::string& lex)
	{
		std::regex VarName("^(&&|~~)$");
		return std::regex_match(lex, VarName);
	}
	bool evalSemiColon(std::string& lex)
	{
		return lex == ";";
	}
	
	//TODO create a list of funcitonPtrs to iterate Over


	void evalWord(std::string& lexeme)
	{
		//iterate over member Functions
		std::vector<std::function<bool(std::string lex)>> *TokenFunctions = new std::vector<std::function<bool(std::string lex)>>;
		TokenFunctions->push_back(this->evalTypeDeclr);
		TokenFunctions->push_back(this->evalArithmeticOp);
		TokenFunctions->push_back(this->evalVarName);
		TokenFunctions->push_back(this->evalBoolOp);
		int c = 1;
		auto iter = TokenFunctions->begin();
		for (iter; iter != TokenFunctions->end(); ++iter)
		{
			if((*iter)(lexeme))
				this->program.push_back(Tokens(c));
			c++;
		}
		
	}

	Lexer(const char* fName)
	{
		char buff;
		std::fstream f;
		f.open(fName);
		while (f.get(buff))
		{
			
			if (buff == ' ')
			{
				evalWord(curLexeme);
				curLexeme = "";
			}
			else
				curLexeme += buff;

		}
	}
	void LogTokens()
	{
		for (auto a : program)
		{
			std::cout << a << std::endl;
		}
	}
};