//
// Created by chan on 2018/8/22.
//

#ifndef SIMPLEINTERPRETER_PARSER_H
#define SIMPLEINTERPRETER_PARSER_H


#include "ast/ASTNode.h"
#include "../lexer/Lexer.h"
#include "ast/StatementNode.h"
#include "ast/VarNode.h"

class Parser
{
private:
	Lexer mLexer;
	Token *mCurrentToken = nullptr;
public:
	Parser(Stream *stream);
	ASTNode *parse();
private:
	ASTNode *program();
	StatementNode *compound();
	StatementNode *statement();
	StatementNode *assignStatement();
	StatementNode *empty();
	VarNode * variable();
	ASTNode *exp();
	ASTNode *term();
	ASTNode *factor();
	void eat(int type);
	void eat(int type, const char *errorMsg);
};


#endif //SIMPLEINTERPRETER_PARSER_H
