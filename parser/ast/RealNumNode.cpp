//
// Created by chan on 2018/9/6.
//

#include "RealNumNode.h"

RealNumNode::RealNumNode(RealNumToken *token)
	: ASTNode(token, ASTNode::Type::REAL_NUM)
{

}
