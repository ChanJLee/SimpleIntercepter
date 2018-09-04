//
// Created by chan on 2018/9/4.
//

#include "NoOpNode.h"
#include "StatementNode.h"

NoOpNode::NoOpNode()
	: StatementNode(ASTNode::Type::NO_OP)
{}
