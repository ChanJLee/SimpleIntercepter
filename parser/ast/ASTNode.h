//
// Created by chan on 2018/8/23.
//

#ifndef SIMPLEINTERPRETER_ASTNODE_H
#define SIMPLEINTERPRETER_ASTNODE_H


#include "../../token/Token.h"
class ASTNode
{
public:
	Token* const token;
public:
	ASTNode(Token *const token);
	virtual ~ASTNode();
};


#endif //SIMPLEINTERPRETER_ASTNODE_H
