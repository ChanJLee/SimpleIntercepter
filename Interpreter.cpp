//
// Created by chan on 2018/8/19.
//

#include "Interpreter.h"
#include "ParseError.h"
#include "RuntimeError.h"
#include <string>
#include <cstddef>

int Interpreter::exp()
{
	int result = term();
	while (true) {
		char ch = mStream->next();
		if (ch == '+') {
			result += term();
		}
		else if (ch == '-') {
			result -= term();
		}
		else {
			// other char
			// back
			// check if invalid
			mStream->back();
			break;
		}
	}

	return result;
}

int Interpreter::term()
{
	int result = factor();
	while (true) {
		char ch = mStream->next();
		if (ch == '/') {
			int rhs = term();
			if (rhs == 0) {
				throw RuntimeError("div by 0");
			}
			result /= term();
		}
		else if (ch == '*') {
			result *= term();
		}
		else {
			// other char
			// back
			// check if invalid
			mStream->back();
			break;
		}
	}

	return result;
}

int Interpreter::factor()
{
	char ch = mStream->next();
	if (ch == '(') {
		int result = exp();
		ch = mStream->next();
		if (ch != ')') {
			throw ParseError("need ')'");
		}
		return result;
	}

	std::string number;
	while (ch >= '0' && ch <= '9') {
		number += ch;
		if (!mStream->hasNext()) {
			break;
		}
		ch = mStream->next();
	}

	if (number.empty()) {
		throw ParseError("invalid char: " + ch);
	}

	mStream->back();
	return std::atoi(number.c_str());
}