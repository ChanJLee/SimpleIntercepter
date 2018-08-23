//
// Created by chan on 2018/8/23.
//

#ifndef SIMPLEINTERPRETER_NUMNODE_H
#define SIMPLEINTERPRETER_NUMNODE_H


#include "ASTNode.h"
#include "../../token/Token.h"
class NumNode: public ASTNode
{
public:
	Token token;
	NumNode(const Token<int> &token);
	virtual ~NumNode();
};


#endif //SIMPLEINTERPRETER_NUMNODE_H
