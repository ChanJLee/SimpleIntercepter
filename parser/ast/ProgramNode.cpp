//
// Created by chan on 2018/9/9.
//

#include "ProgramNode.h"

ProgramNode::ProgramNode(Token *const token, BlockNode *block)
	: ASTNode(token, ASTNode::Type::PROGRAM), block(block)
{}

ProgramNode::~ProgramNode()
{
	delete block;
}
