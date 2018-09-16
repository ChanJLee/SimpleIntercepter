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

/*
 * program : PROGRAM variable SEMI block DOT
 *
 * block : declarations compound_statement
 *
 * declarations : (VAR (variable_declaration SEMI)+)*
 *              | (PROCEDURE ID (LPAREN formal_parameter_list RPAREN)? SEMI block SEMI)*
 *              | empty
 *
 * formal_parameter_list : formal_parameters
 *                       | formal_parameters SEMI formal_parameter_list
 *
 * formal_parameters : ID (COMMA ID)* COLON type_spec
 *
 * variable_declaration : ID (COMMA ID)* COLON type_spec
 *
 * type_spec : INTEGER
 *           | REAL
 *
 * compound_statement: BEGIN statement_list END
 *
 * statement_list : statement
 *                | statement SEMI statement_list
 *
 * statement : compound_statement
 *           | assignment_statement
 *           | empty
 *
 * assignment_statement : variable ASSIGN expr
 *
 * variable : ID
 *
 * empty: An empty production
 *
 * expr : term ((PLUS | MINUS) term)*
 *
 * term : factor ((MUL | INTEGER_DIV | FLOAT_DIV) factor)*
 *
 * factor : PLUS factor
 *        | MINUS factor
 *        | INTEGER_CONST
 *        | REAL_CONST
 *        | LPAREN expr RPAREN
 *        | variable
 * */
class Parser
{
private:
	Lexer mLexer;
	Token *mCurrentToken = nullptr;
public:
	Parser(const Lexer &lexer);
	ProgramNode *parse();
private:
	ProgramNode *program();
	BlockNode *block();
	DeclarationsNode *declarations();
	StatementNode *compound();
	StatementNode *statement();
	StatementNode *assignStatement();
	StatementNode *empty();
	VarNode *variable();
	ASTNode *exp();
	ASTNode *term();
	ASTNode *factor();
	void eat(int type);
	void eat(int type, const std::string &msg);
};


#endif //SIMPLEINTERPRETER_PARSER_H
