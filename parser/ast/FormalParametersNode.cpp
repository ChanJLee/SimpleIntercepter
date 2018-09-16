//
// Created by chan on 2018/9/16.
//

#include "FormalParametersNode.h"


FormalParametersNode::Parameter::Parameter(Token *id, Token::TokenType type)
	: id(id), type(type)
{

}

FormalParametersNode::Parameter::~Parameter()
{
	if (id != nullptr) {
		delete id;
	}
}

FormalParametersNode::FormalParametersNode(const std::vector<Parameter *> &parameters)
	: ASTNode(nullptr, ASTNode::Type::FORMAL_PARAMETER)
{

}
