//
// Created by chan on 2018/8/23.
//

#include "ASTNode.h"

ASTNode::ASTNode(Token *const token, ASTNode::Type type)
	: token(token), type(type)
{}

ASTNode::~ASTNode()
{
	delete token;
}
