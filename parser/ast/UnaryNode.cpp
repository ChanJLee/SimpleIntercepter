//
// Created by chan on 2018/8/29.
//

#include "UnaryNode.h"

UnaryNode::UnaryNode(Token *const token, ASTNode *child)
	: ASTNode(token, ASTNode::Type::UNARY), child(child)
{

}

UnaryNode::~UnaryNode()
{
	if (child != nullptr) {
		delete child;
	}
}
