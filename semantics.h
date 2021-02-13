#pragma once
#include "Scopes.h"
#include "Lexer.h"
#include <memory>
#include <stack>
class Semantics
{
	Scope Global;
	Scope* current;//Pointer to the deepest scope at a given point in a program
	std::vector<ArithmeticOperatorNode> mathOps;
	std::vector<booleanOperatorNode> logicOps;
		//Int refers to precedence;
	void addScope()
	{
		Scope *deep = new Scope();//create a new scope
		deep->outer = current;//point the next outer scope to be the one currently pointing to
		current = deep;//set the current to be the new one which will be the deepest;
	}
	int deduceArithOper(std::string op)
	{
		char opList[] = { '+', '-', '/', '*' };
		for (int i = 0; i < 4; i++)
		{
			if (opList[i] == op[0])
			{
				return i;
			}
		}
	}
	int deduceBoolOper(std::string& op)
	{
		const char* bools[] = { "&&", "||"};
		for (int i = 0; i < 4; i++)
		{
			if (!strcmp(op.c_str(), bools[i]))
			{
				return i;
			}
		}
	}
	void typeChecking();
	void evaluateDeclaration(std::string t, std::string a, bool assign=false, std::string li = "")
	{
		if (current->inScope(a))
			return;
		if (assign)
		{
			auto as = new varTy(deduceType(t), stoi(li));
			current->addVar(a, as);
			return;
		}
		auto b = new varTy( deduceType(t) );
		current->addVar(a,b);

	}
	void evaluateReference(std::string var, std::string ass)
	{
		if (current->inScope(var))
			current->getVar(var)->assign(stoi(ass));
			return;
	}
	
	/*
	TODO create function that generalises equals sign and decomposes the rightside incase is more that one right side arg
	*/
	int evaluateEqu(varTy* left, std::vector<std::pair<Tokens, std::string>> p) {
		/*
		Construct a Tree with the lowest precedence on top
		*/
		
	}

	
	bool isLiteral(Tokens t)
	{
		return t == Tok_numeric_literal;
	}
	int evalArithmeticOp(std::string& op, std::string& left, std::string& right)
	{
		int OpPosition = deduceArithOper(op);
		std::cout << mathOps[OpPosition].calculate(*current->getVar(left), *current->getVar(right)) << std::endl << std::endl;
		return mathOps[OpPosition].calculate(*current->getVar(left), *current->getVar(right));
	}
	void evalBoolOp(std::string& op, std::string& left, std::string& right)
	{
		std::cout << "BOOL";
		int OpPosition = deduceBoolOper(op);
		std::cout << logicOps[OpPosition].calculate(*current->getVar(left), *current->getVar(right)) << std::endl << std::endl;
	}
	void jmp(bool stmt)
	{
		/*if stmt jump to end of if*/
	}
public:
	Semantics(std::vector<std::pair<Tokens, std::string>> p) {
		ArithmeticOperatorNode add = ArithmeticOperatorNode([](auto a, auto b) {return a + b; });
		ArithmeticOperatorNode minus = ArithmeticOperatorNode([](auto a, auto b) {return a - b; });
		ArithmeticOperatorNode divide = ArithmeticOperatorNode([](auto a, auto b) {return a / b; });
		ArithmeticOperatorNode mul = ArithmeticOperatorNode([](auto a, auto b) {return a * b; });
		booleanOperatorNode and_log([](auto a, auto b) {return a && b; });
		booleanOperatorNode or_log([](auto a, auto b) {return a || b; });
		
		mathOps.push_back(add);
		mathOps.push_back(minus);
		mathOps.push_back(divide);
		mathOps.push_back(mul);
		logicOps.push_back(and_log);
		logicOps.push_back(or_log);
		current = &Global;
		for (int i = 0; i < p.size()-2; i++)
		{
			if (p[i].first == Tok_varName && p[i-1].first == Tok_type_decl)
				evaluateDeclaration(p[i-1].second, p[i].second, (p[i+2].first == Tok_numeric_literal), p[i+2].second);
			
			if (p[i].first == Tok_varName && p[i - 1].first != Tok_type_decl && p[i+1].first == Tok_equ)
				evaluateReference(p[i].second, p[i + 2].second);
			if (p[i].first == Tok_arithmetic_op)
				evalArithmeticOp(p[i].second, p[i - 1].second, p[i + 1].second);
				
			if (p[i].first == Tok_bool_op)
				evalBoolOp(p[i].second, p[i - 1].second, p[i + 1].second);
				continue;
		}
		current->logVars(current);
	}
};