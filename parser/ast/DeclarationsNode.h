//
// Created by chan on 2018/9/9.
//

#ifndef SIMPLEINTERPRETER_DECLARATIONSNODE_H
#define SIMPLEINTERPRETER_DECLARATIONSNODE_H


#include <vector>
#include "ASTNode.h"

class ProcedureNode;

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
	std::vector<ProcedureNode *> procedures;
public:

	DeclarationsNode();
	DeclarationsNode(const std::vector<Declaration *> &declarations, const std::vector<ProcedureNode *> &procedures);
	virtual ~DeclarationsNode();
};


#endif //SIMPLEINTERPRETER_DECLARATIONSNODE_H
