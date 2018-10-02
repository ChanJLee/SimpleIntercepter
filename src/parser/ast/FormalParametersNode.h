//
// Created by chan on 2018/9/16.
//

#ifndef SIMPLEINTERPRETER_FORMATPARAMETERS_H
#define SIMPLEINTERPRETER_FORMATPARAMETERS_H


#include <vector>
#include "ASTNode.h"
class FormalParametersNode: ASTNode
{
public:
	struct Parameter
	{
		Token *id;
		Token::TokenType type;
		Parameter(Token *id, Token::TokenType type);
		virtual ~Parameter();
	};

	std::vector<Parameter*> parameters;
public:
	FormalParametersNode(const std::vector<Parameter*> &parameters);
};


#endif //SIMPLEINTERPRETER_FORMATPARAMETERS_H
