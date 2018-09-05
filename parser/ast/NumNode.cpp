//
// Created by chan on 2018/8/23.
//

#include "NumNode.h"

NumNode::~NumNode()
{
}

NumNode::NumNode(NumToken *token)
	: ASTNode(token, ASTNode::Type::NUM)
{

}
