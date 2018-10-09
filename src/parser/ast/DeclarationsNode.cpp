//
// Created by chan on 2018/9/9.
//

#include "DeclarationsNode.h"

DeclarationsNode::DeclarationsNode(const std::vector<Declaration *> &declarations)
	: ASTNode(nullptr, ASTNode::Type::DECLARATION), declarations(declarations)
{

}

DeclarationsNode::~DeclarationsNode()
{
	std::for_each(declarations.cbegin(), declarations.cend(), [](Declaration *declaration)
	{
		delete declaration;
	});
}

DeclarationsNode::DeclarationsNode()
	: ASTNode(nullptr, ASTNode::Type::DECLARATION)
{}

DeclarationsNode::Declaration::Declaration(Token *id, Token::TokenType type)
	: id(id), type(type)
{}

DeclarationsNode::Declaration::~Declaration()
{
	delete id;
}
