#pragma once
#include "Scopes.h"
#include "Lexer.h"

class Semantics
{
	Scope Global;
	Scope* current;//Pointer to the deepest scope at a given point in a program
	void addScope()
	{
		Scope *deep = new Scope();//create a new scope
		deep->outer = current;//point the next outer scope to be the one currently pointing to
		current = deep;//set the current to be the new one which will be the deepest;
	}
	void typeChecking();
	void evaluateDeclaration(std::string t, std::string a, bool assign=false, std::string li = "")
	{
		if (current->inScope(a))
			return;
		if (assign)
		{
			auto as = new Ty(deduceType(t), stoi(li));
			current->addVar(a, as);
			return;
		}
		auto b = new Ty( deduceType(t) );
		current->addVar(a,b);

	}
	void evaluateReference(std::string var, std::string ass)
	{
		if (current->inScope(var))
			//set value to variable
			return;
	}
public:
	Semantics(std::vector<std::pair<Tokens, std::string>> p) {
		current = &Global;
		for (int i = 0; i < p.size()-2; i++)
		{
			if (p[i].first == Tok_varName && p[i-1].first == Tok_type_decl)
				evaluateDeclaration(p[i-1].second, p[i].second, (p[i+2].first == Tok_numeric_literal), p[i+2].second);
			if (p[i].first == Tok_equ && p[i - 1].first == Tok_varName)
				evaluateReference(p[i - 1].second, p[i + 1].second);
		}
		current->logVars(current);
	}
};