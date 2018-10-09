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
	delete id;
}

FormalParametersNode::FormalParametersNode(const std::vector<Parameter *> &parameters)
	: ASTNode(nullptr, ASTNode::Type::FORMAL_PARAMETER), parameters(parameters)
{

}

FormalParametersNode::~FormalParametersNode()
{
	std::for_each(parameters.cbegin(), parameters.cend(), [](FormalParametersNode::Parameter *parameter)
	{
		delete parameter;
	});
}
