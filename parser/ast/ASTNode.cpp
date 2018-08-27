//
// Created by chan on 2018/8/23.
//

#include "ASTNode.h"
ASTNode::ASTNode(Token *const token)
	: token(token)
{}

ASTNode::~ASTNode()
{
	delete token;
}
