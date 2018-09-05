//
// Created by chan on 2018/8/23.
//

#ifndef SIMPLEINTERPRETER_NUMNODE_H
#define SIMPLEINTERPRETER_NUMNODE_H


#include "ASTNode.h"
#include "../../token/Token.h"
#include "../../token/NumToken.h"

class NumNode: public ASTNode
{
public:
	NumNode(NumToken *token);
	virtual ~NumNode();
};


#endif //SIMPLEINTERPRETER_NUMNODE_H
