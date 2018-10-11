//
// Created by chan on 2018/8/29.
//

#ifndef SIMPLEINTERPRETER_UNARYNODE_H
#define SIMPLEINTERPRETER_UNARYNODE_H


#include "ASTNode.h"
class UnaryNode: public ASTNode
{
public:
	ASTNode* child;
public:
	UnaryNode(Token *token,  ASTNode* child);
	~UnaryNode() override;
};


#endif //SIMPLEINTERPRETER_UNARYNODE_H
