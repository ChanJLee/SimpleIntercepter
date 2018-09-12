//
// Created by chan on 2018/9/11.
//

#include "SyntaxChecker.h"
#include "../token/IdToken.h"
#include "../exception/ParseError.h"
#include "../parser/ast/AssignStatementNode.h"

SyntaxChecker::SyntaxChecker(ProgramNode *tree)
	: mTree(tree)
{

}

void SyntaxChecker::check()
{
	checkBlock(mTree->block);
}

void SyntaxChecker::checkBlock(BlockNode *node)
{
	checkDeclarations(node->declarations);
	checkCompoundStatement((CompoundStatementNode *) node->compoundStatementNode);
}

void SyntaxChecker::checkDeclarations(DeclarationsNode *node)
{
	std::for_each(
		node->declarations.cbegin(),
		node->declarations.cend(),
		[this](DeclarationsNode::Declaration *declaration)
		{
			if (declaration != nullptr) {
				IdToken *id = (IdToken *) declaration->id;
				putSymbol(id->value, declaration->type);
			}
		});
}

void SyntaxChecker::checkCompoundStatement(CompoundStatementNode *node)
{
	std::for_each(node->statements.cbegin(), node->statements.cend(), [this](StatementNode *statement)
	{
		if (statement->type == ASTNode::Type::COMPOUND) {
			checkCompoundStatement((CompoundStatementNode *) statement);
			return;
		}

		if (statement->type == ASTNode::Type::ASSIGN) {
			checkAssignStatement((AssignStatementNode *) statement);
			return;
		}

		if (statement->type == ASTNode::Type::NO_OP) {
			/* DO NOTHING */
			return;
		}

		String msg = "unknown statement, type is";
		msg += statement->type;
		throw ParseError(msg);
	});
}

void SyntaxChecker::putSymbol(const SyntaxChecker::String &key, Token::TokenType value)
{
	Iterator it = mGlobalSymbolTable.find(key);
	if (it != mGlobalSymbolTable.end()) {
		String msg = "define " + key + " twice";
		throw ParseError(msg);
	}

	if (value == Token::TokenType::TYPE_REAL) {
		mGlobalSymbolTable[key] = Symbol::REAL;
	}
	else if (value == Token::TokenType::TYPE_INTEGER) {
		mGlobalSymbolTable[key] = Symbol::INT;
	}

	String msg = "unknown type: ";
	msg += value;
	throw ParseError(msg);
}

Symbol SyntaxChecker::getSymbol(const SyntaxChecker::String &key)
{

	Iterator it = mGlobalSymbolTable.find(key);
	if (it == mGlobalSymbolTable.end()) {
		return Symbol::UNDEFINED;
	}

	return it->second;
}

void SyntaxChecker::checkAssignStatement(AssignStatementNode *node)
{
	VarNode *lv = node->lv;
	Symbol symbol = checkVar(lv);
	checkExp(node->rv, symbol);
}

Symbol SyntaxChecker::checkVar(VarNode *node)
{
	IdToken *id = (IdToken *) node->token;
	Symbol type = getSymbol(id->value);
	if (type == Symbol::UNDEFINED) {
		String msg = "undefined symbol " + id->value;
		throw ParseError(msg);
	}
	return type;
}

void SyntaxChecker::checkExp(ASTNode *node, Symbol prefer)
{
}