//
// Created by chan on 2018/9/9.
//

#include "DeclarationsNode.h"

DeclarationsNode::DeclarationsNode(const std::vector<Declaration *> &declarations,
								   const std::vector<ProcedureNode *> &procedures)
	: ASTNode(nullptr, ASTNode::Type::DECLARATION), declarations(declarations), procedures(procedures)
{

}

DeclarationsNode::~DeclarationsNode()
{
	std::for_each(declarations.cbegin(), declarations.cend(), [](Declaration *declaration)
	{
		if (declaration != nullptr) {
			delete declaration;
		}
	});

	std::for_each(procedures.cbegin(), procedures.cend(), [](ProcedureNode *procedure)
	{
		if (procedure != nullptr) {
			delete procedure;
		}
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
	if (id != nullptr) {
		delete id;
	}
}
