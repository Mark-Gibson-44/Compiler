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

class Ty
{
public:
	TypeNames t;
	size_t value = 0; //Value of a variable represented by bytes. Might use bitset
	size_t size = 0;//Size in bytes of a given type;
	Ty(TypeNames a)
	{
		t = a;

	}
	void assign(int val)
	{
		this->value = val;
	}


};