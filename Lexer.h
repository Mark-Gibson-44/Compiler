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
	Tok_numeric_literal = 6,
	Tok_fun = 7,
	Tok_equ = 8,
	Tok_opBrace = 9,
	Tok_if = 10,

	Tok_EOF= 49,
	Tok_invalid = 50
	
} Tokens;
std::string to_string(Tokens t)
{
	switch (t)
	{
	case Tok_semi:
		return "Semi-Colon"; break;
	case Tok_arithmetic_op:
		return "Arithmetic_Op"; break;
	case Tok_bool_op:
		return "Bool_Op"; break;
	case Tok_type_decl:
		return "TypeDeclr"; break;
	case Tok_varName:
		return "Var_name"; break;
	case Tok_numeric_literal:
		return "Numeric_literal"; break;
	case Tok_equ:
		return "Equal"; break;
	case Tok_opBrace:
		return "Open Brace"; break;
	case Tok_EOF:
		return "EndOfFile"; break;
	case Tok_if:
		return "If"; break;
	case Tok_fun:
		return "Function"; break;


	}
}
class Lexer
{
	
public:
	std::vector<Tokens> lexedProgram;
	std::string curLexeme = "";

	bool evalTypeDeclr(std::string& lex)
	{
		std::regex Types("^(int|char|bool)$");
		return std::regex_match(lex, Types);
	}
	bool evalArithmeticOp(std::string& lex)
	{
		std::regex ArithOps("^.\+$");
		return std::regex_match(lex, ArithOps);
	}
	bool evalNumericLiteral(std::string& lex)
	{
		std::regex ArithOps("^[0-9]$");
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
	bool evalEqu(std::string& lex)
	{
		return lex == "=";
	}
	bool evalLBrace(std::string& lex)
	{
		return lex == "{";
	}
	bool evalIf(std::string& lex)
	{
		return lex == "?";
	}
	bool evalFunc(std::string& lex)
	{
		return lex == "def";
	}

	//TODO create a list of funcitonPtrs to iterate Over


	void evalWord(std::string& lexeme)
	{
		//iterate over member Functions
		//std::vector<std::function<bool(std::string& lex)>> *TokenFunctions = new std::vector<std::function<bool(std::string& lex)>>;
		/*
		auto k = { std::mem_fn(&Lexer::evalTypeDeclr), std::mem_fn(&Lexer::evalArithmeticOp), std::mem_fn(&Lexer::evalVarName),std::mem_fn(&Lexer::evalBoolOp) };
		std::string s = "hlp";
		
		auto iter = k.begin();
		iter++;
		auto test = *iter;
		test.operator()((test));
		auto qll = std::mem_fn(&Lexer::evalTypeDeclr);
		for (auto q : k)
		{
			q(s);
		}
		*/
		/*for(iter; iter != TokenFunctions->end(); ++iter)
		{
			if(this->TokenFunctions[0])(lexeme))
				this->program.push_back(Tokens(c));
			c++;
		}*/
		
		if (this->evalTypeDeclr(lexeme))
		{
			lexedProgram.push_back(Tok_type_decl);
			return;
		}
		/*if (this->evalArithmeticOp(lexeme))
		{
			program.push_back(Tok_arithmetic_op);
			return;
		}*/
		if (this->evalVarName(lexeme))
		{
			lexedProgram.push_back(Tok_varName);
			return;
		}
		if (this->evalBoolOp(lexeme))
		{
			lexedProgram.push_back(Tok_bool_op);
			return;
		}
		if (this->evalSemiColon(lexeme))
		{
			lexedProgram.push_back(Tok_semi);
			return;
		}
		if (this->evalNumericLiteral(lexeme))
		{
			lexedProgram.push_back(Tok_numeric_literal);
			return;
		}
		if (this->evalEqu(lexeme))
		{
			lexedProgram.push_back(Tok_equ);
			return;
		}
		if (this->evalLBrace(lexeme))
		{
			lexedProgram.push_back(Tok_opBrace);
			return;
		}
		if (this->evalIf(lexeme))
		{
			lexedProgram.push_back(Tok_if);
			return;
		}
		if (this->evalFunc(lexeme))
		{
			lexedProgram.push_back(Tok_fun);
			return;
		}
	}

	Lexer(const char* fName)
	{
		char buff;
		std::fstream f;
		f.open(fName);
		
		while (f.get(buff))
		{
			
			if (buff == ' ' || buff == '\n')
			{
				evalWord(curLexeme);
				curLexeme = "";
			}
			else
				curLexeme += buff;

		}
		evalWord(curLexeme);
		lexedProgram.push_back(Tok_EOF);
	}
	void LogTokens()
	{
		for (auto a : lexedProgram)
		{
			std::cout << to_string(a) << std::endl;
		}
	}
	std::vector<Tokens> getLexed()
	{
		return this->lexedProgram;
	}
};