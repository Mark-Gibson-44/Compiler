#pragma once
#include "Types.h"

#include <functional>



class ArithmeticOperatorNode  {
public:
	
	std::function<size_t(varTy, varTy)> op;
	ArithmeticOperatorNode(std::function<size_t(varTy, varTy)> op) : op(op){}
	size_t calculate(varTy left, varTy right)
	{
		return op(left, right);
	}
	
};
class booleanOperatorNode {
public:

	std::function<size_t(varTy, varTy)> op;
	booleanOperatorNode(std::function<size_t(varTy, varTy)> op) : op(op) {}
	size_t calculate(varTy left, varTy right)
	{
		return op(left, right);
	}

};

