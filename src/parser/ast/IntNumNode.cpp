//
// Created by chan on 2018/8/23.
//

#include "IntNumNode.h"

IntNumNode::IntNumNode(IntNumToken *token)
	: ASTNode(token, ASTNode::Type::INT_NUM)
{

}
