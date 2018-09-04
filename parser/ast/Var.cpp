//
// Created by chan on 2018/9/4.
//

#include "Var.h"

Var::Var(Token *const token)
	: ASTNode(token, ASTNode::Type::VAR)
{}
