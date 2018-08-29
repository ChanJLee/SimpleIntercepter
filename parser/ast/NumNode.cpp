//
// Created by chan on 2018/8/23.
//

#include "NumNode.h"

NumNode::~NumNode()
{
}
NumNode::NumNode(Token *const token)
	: ASTNode(token, ASTNode::Type::NUM)
{

}
