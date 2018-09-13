//
// Created by chan on 2018/9/9.
//

#ifndef SIMPLEINTERPRETER_DECLARATIONSNODE_H
#define SIMPLEINTERPRETER_DECLARATIONSNODE_H


#include <vector>
#include "ASTNode.h"

class DeclarationsNode: public ASTNode
{
public:
	struct Declaration
	{
		Token *id;
		Token::TokenType type;
		Declaration(Token *id, Token::TokenType type);
		virtual ~Declaration();
	};

	std::vector<Declaration *> declarations;
public:

	DeclarationsNode();
	DeclarationsNode(const std::vector<Declaration *> &declarations);
	virtual ~DeclarationsNode();
};


#endif //SIMPLEINTERPRETER_DECLARATIONSNODE_H
