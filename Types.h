#pragma once

typedef enum {
	Type_int = 0,
	Type_char = 1,
	Type_bool = 2
} TypeNames;

TypeNames deduceType(std::string a)
{

	if (!strcmp(a.c_str(), "int"))
		return Type_int;
	if (!strcmp(a.c_str(), "bool"))
		return Type_char;
	if (!strcmp(a.c_str(), "char"))
		return Type_bool;
}
//Create function to determine type based upon init type
TypeNames inferType(std::string& s);
std::string typeToString(TypeNames f)
{
	switch (f)
	{
	case Type_int:
		return "Int";
	case Type_char:
		return "char";
	case Type_bool:
		return "bool";
	}
}
/*
TODO: Make Vars using templates
*/

class varTy
{
public:
	TypeNames t;
	size_t value = 0; //Value of a variable represented by bytes. Might use bitset
	size_t size = 0;//Size in bytes of a given type;
	bool init = false;
	varTy(TypeNames a)
	{
		t = a;

	}
	varTy(TypeNames a, int liter)
	{
		t = a;
		this->value = liter;
		this->init = true;
	}
	void dumpVal()
	{
		std::cout << "Value is :" << this->value << std::endl;
	}
	void assign(int val)
	{
		this->value = val;
		this->init = true;
	}
	void assign(varTy& t)
	{
		this->value = t.value;
		this->init = true;
	}
	size_t operator+ (varTy right)
	{
		return this->value + right.value;
	}
	size_t operator- (varTy right)
	{
		return this->value - right.value;
	}
	size_t operator/ (varTy right)
	{
		return this->value / right.value;
	}
	size_t operator* (varTy right)
	{
		return this->value * right.value;
	}
	size_t operator&& (varTy right)
	{
		return bool(this->value) * bool(right.value);
	}
	//Edited to act like a short-circuit
	//checks if first value is true, if so return it since its true 
	//otherwise return the other value
	size_t operator|| (varTy right)
	{
		if (bool(this->value))
			return bool(this->value);
		return  bool(right.value);
		
	}



};




