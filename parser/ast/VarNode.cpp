//
// Created by chan on 2018/9/4.
//

#include "VarNode.h"

VarNode::VarNode(IdToken *token)
	: ASTNode(token, ASTNode::Type::VAR)
{}
