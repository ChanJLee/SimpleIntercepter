//
// Created by chan on 2018/9/4.
//

#include "CompoundStatementNode.h"
#include <algorithm>

CompoundStatementNode::CompoundStatementNode(const std::vector<StatementNode *> &statements)
	: StatementNode(ASTNode::Type::COMPOUND), statements(statements)
{
}

CompoundStatementNode::~CompoundStatementNode()
{
	std::for_each(statements.cbegin(), statements.cend(), [](const StatementNode *child)
	{
		delete child;
	});
}
