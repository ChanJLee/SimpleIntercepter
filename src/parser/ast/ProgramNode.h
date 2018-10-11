//
// Created by chan on 2018/9/9.
//

#ifndef SIMPLEINTERPRETER_PROGRAMNODE_H
#define SIMPLEINTERPRETER_PROGRAMNODE_H


#include "ASTNode.h"
#include "BlockNode.h"
class ProgramNode: public ASTNode
{
public:
	BlockNode* block;
public:
	ProgramNode(Token *id, BlockNode* block);
	~ProgramNode() override;
};


#endif //SIMPLEINTERPRETER_PROGRAMNODE_H
