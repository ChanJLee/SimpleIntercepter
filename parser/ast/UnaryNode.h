//
// Created by chan on 2018/8/29.
//

#ifndef SIMPLEINTERPRETER_UNARYNODE_H
#define SIMPLEINTERPRETER_UNARYNODE_H


#include "ASTNode.h"
class UnaryNode: public ASTNode
{
private:
	ASTNode* child;
public:
	UnaryNode(Token *const token,  ASTNode* child);
	~UnaryNode();
};


#endif //SIMPLEINTERPRETER_UNARYNODE_H
