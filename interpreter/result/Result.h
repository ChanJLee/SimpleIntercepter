//
// Created by chan on 2018/9/13.
//

#ifndef SIMPLEINTERPRETER_RESULT_H
#define SIMPLEINTERPRETER_RESULT_H


#include "../../token/Token.h"

struct Result
{
	union Value
	{
		int i;
		double r;
	};

	Token::TokenType type;
	Value value;
};

template <typename T>
inline Result _BUILD_IN_VALUE_TO_RESULT(Token::TokenType type, T value) {
	Result result = {
		.type = type
	};

	if (type == Token::TokenType::TYPE_REAL) {
		result.value.r = value;
		return result;
	}

	result.value.i = value;
	return result;
}

template <typename T>
inline T _RESULT_TO_BUILD_IN_VALUE(Result result) {
	return (result.type == Token::TokenType::TYPE_REAL ? result.value.r : result.value.i);
}

#ifndef RESULT_TO_BUILD_IN_VALUE_
#define RESULT_TO_BUILD_IN_VALUE_(result) \
	(result.type == Token::TokenType::TYPE_REAL ? _RESULT_TO_BUILD_IN_VALUE<double>(result) : _RESULT_TO_BUILD_IN_VALUE<int>(result))
#define RESULT_TO_BUILD_IN_VALUE RESULT_TO_BUILD_IN_VALUE_

#define BUILD_IN_VALUE_TO_RESULT_(type, value) \
	type == Token::TokenType::TYPE_REAL ? _BUILD_IN_VALUE_TO_RESULT<double>(type, value) : _BUILD_IN_VALUE_TO_RESULT<int>(type, value)
#define BUILD_IN_VALUE_TO_RESULT BUILD_IN_VALUE_TO_RESULT_
#endif



#endif //SIMPLEINTERPRETER_RESULT_H
