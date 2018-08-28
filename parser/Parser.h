//
// Created by chan on 2018/8/22.
//

#ifndef SIMPLEINTERPRETER_PARSER_H
#define SIMPLEINTERPRETER_PARSER_H


#include "ast/ASTNode.h"
#include "../lexer/Lexer.h"

class Parser
{
private:
	Lexer mLexer;
	Token *mCurrentToken = nullptr;
public:
	Parser(Stream *stream);
	ASTNode *exp();
private:
	ASTNode *term();
	ASTNode *factor();
	void eat(int type);
	void eat(int type, const char* errorMsg);
};


#endif //SIMPLEINTERPRETER_PARSER_H
