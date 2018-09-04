//
// Created by chan on 2018/9/4.
//

#include "CompoundNode.h"
#include <algorithm>

CompoundNode::CompoundNode(const std::vector<StatementNode *> &statements)
	: StatementNode(ASTNode::Type::COMPOUND), statements(statements)
{
}

CompoundNode::~CompoundNode()
{
	std::for_each(statements.cbegin(), statements.cend(), [](StatementNode *child) ->
	{
		if (child != nullptr) {
			delete child;
		}
	});
}
