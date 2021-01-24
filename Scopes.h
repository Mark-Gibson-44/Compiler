#pragma once
#include "Types.h"
#include <map>
#include <iostream>
#include <string>


class Scope
{
public:
	Scope* outer;//pointer to scope Preceding it, Global scopes outer will point to nullptr
	std::map<std::string, Ty*> scopeVars;
	Scope(Scope* current = nullptr)
	{
		outer = current;
	}

	/*
	Function that determines if a variable name has been declared before use
	First identifies if in current scope otherwise check outer scopes
	*/
	bool inScope(std::string& varName)
	{
		auto f = scopeVars.find(varName);
		bool ret = f != scopeVars.end();
		//Checks if ret is true first as if so
		//Will short circuit and no need to check outer scopes
		if (ret != true && this->outer != nullptr)
			ret = ret && outer->inScope(varName);
		

		return ret;
	}
	void logVars(Scope* s)
	{
		
		for (auto a: s->scopeVars)
		{
			std::cout << a.first << " Of type : " << typeToString(a.second->t) << std::endl;
		}
		if (s->outer == nullptr)
			return;
		logVars(s->outer);

	}
	void addVar(std::string id, Ty* t)
	{
		scopeVars[id] = t;
	}
	
};