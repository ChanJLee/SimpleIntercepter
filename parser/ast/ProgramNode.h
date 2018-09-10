//
// Created by chan on 2018/9/9.
//

#ifndef SIMPLEINTERPRETER_PROGRAMNODE_H
#define SIMPLEINTERPRETER_PROGRAMNODE_H


#include "ASTNode.h"
class ProgramNode: public ASTNode
{
public:
	ASTNode* block;
public:
	ProgramNode(Token *id, ASTNode* block);
	virtual ~ProgramNode();
};


#endif //SIMPLEINTERPRETER_PROGRAMNODE_H
