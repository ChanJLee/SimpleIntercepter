//
// Created by chan on 2018/8/22.
//

#ifndef SIMPLEINTERPRETER_PARSER_H
#define SIMPLEINTERPRETER_PARSER_H


#include "ast/ASTNode.h"
#include "../lexer/Lexer.h"
#include "ast/StatementNode.h"
#include "ast/VarNode.h"
#include "ast/DeclarationsNode.h"
#include "ast/BlockNode.h"
#include "ast/ProgramNode.h"

class Parser
{
private:
	Lexer mLexer;
	Token *mCurrentToken = nullptr;
public:
	Parser(Stream *stream);
	ProgramNode *parse();
private:
	ProgramNode *program();
	BlockNode *block();
	DeclarationsNode* declarations();
	StatementNode *compound();
	StatementNode *statement();
	StatementNode *assignStatement();
	StatementNode *empty();
	VarNode * variable();
	ASTNode *exp();
	ASTNode *term();
	ASTNode *factor();
	void eat(int type);
	void eat(int type, const std::string& msg);
};


#endif //SIMPLEINTERPRETER_PARSER_H
