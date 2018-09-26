//
// Created by chan on 2018/8/22.
//

#include "Parser.h"
#include "../exception/ParseError.h"
#include "ast/BinOpNode.h"
#include "ast/IntNumNode.h"
#include "ast/UnaryNode.h"
#include "ast/NoOpStatementNode.h"
#include "ast/AssignStatementNode.h"
#include "ast/RealNumNode.h"
#include "ast/ProceduresNode.h"
#include "ast/FormalParametersNode.h"
#include "../memory/LocalRef.h"

Parser::Parser(Lexer *lexer)
	: mLexer(lexer)
{
	mCurrentToken = mLexer->next();
}

ASTNode *Parser::exp()
{
	ASTNode *lhs = term();
	while (mCurrentToken->type == Token::TokenType::TYPE_SUB ||
		mCurrentToken->type == Token::TokenType::TYPE_PLUS) {
		Token *token = mCurrentToken;
		eat(token->type);
		lhs = new BinOpNode(token, lhs, term());
	}
	return lhs;
}

ASTNode *Parser::term()
{
	ASTNode *lhs = factor();
	while (mCurrentToken->type == Token::TokenType::TYPE_REAL_DIV ||
		mCurrentToken->type == Token::TokenType::TYPE_INT_DIV ||
		mCurrentToken->type == Token::TokenType::TYPE_MUL) {
		Token *token = mCurrentToken;
		eat(token->type);
		lhs = new BinOpNode(token, lhs, factor());
	}
	return lhs;
}

ASTNode *Parser::factor()
{
	Token *token = mCurrentToken;
	if (token->type == Token::TokenType::TYPE_LEFT_BRACKET) {
		eat(Token::TokenType::TYPE_LEFT_BRACKET);
		ASTNode *result = exp();
		eat(Token::TokenType::TYPE_RIGHT_BRACKET, "missing )");
		return result;
	}

	if (token->type == Token::TokenType::TYPE_INT_NUM) {
		eat(Token::TokenType::TYPE_INT_NUM);
		return new IntNumNode((IntNumToken *) token);
	}

	if (token->type == Token::TokenType::TYPE_PLUS) {
		eat(Token::TokenType::TYPE_PLUS);
		return new UnaryNode(token, factor());
	}

	if (token->type == Token::TokenType::TYPE_SUB) {
		eat(Token::TokenType::TYPE_SUB);
		return new UnaryNode(token, factor());
	}

	if (token->type == Token::TokenType::TYPE_ID) {
		return variable();
	}

	if (token->type == Token::TokenType::TYPE_REAL_NUM) {
		eat(Token::TokenType::TYPE_REAL_NUM);
		return new RealNumNode((RealNumToken *) token);
	}

	std::string msg = "invalid token, type is";
	msg += std::to_string(token->type);
	throw ParseError(msg);
}

void Parser::eat(int type)
{
	try {
		eat(type, "");
	}
	catch (const ParseError &error) {
		std::string msg = "invalid state, need is: ";
		msg += std::to_string(type);
		msg += ", and current is ";
		msg += std::to_string(mCurrentToken->type);
		throw ParseError(msg);
	}
}

void Parser::eat(int type, const std::string &msg)
{
	if (mCurrentToken->type == type) {
		mCurrentToken = mLexer->next();
		return;
	}

	throw ParseError(msg);
}

ProgramNode *Parser::program()
{
	eat(Token::TokenType::TYPE_PROGRAM, "miss PROGRAM header");
	LocalRef<Token> id(mCurrentToken);
	eat(Token::TokenType::TYPE_ID, "missing PROGRAM id");
	eat(Token::TokenType::TYPE_SEMI, "missing ';' after PROGRAM id");
	LocalRef<BlockNode> blockNode(block());
	LocalRef<ProgramNode> programNode(new ProgramNode(id.get(), blockNode.get()));
	eat(Token::TokenType::TYPE_DOT, "missing .");
	id.release();
	blockNode.release();
	return programNode.release();
}

StatementNode *Parser::compound()
{
	eat(Token::TokenType::TYPE_BEGIN);
	std::vector<StatementNode *> statements;
	StatementNode *child = statement();
	statements.push_back(child);
	while (mCurrentToken->type == Token::TokenType::TYPE_SEMI) {
		eat(Token::TokenType::TYPE_SEMI);
		child = statement();
		statements.push_back(child);
	}

	eat(Token::TokenType::TYPE_END);
	return new CompoundStatementNode(statements);;
}

StatementNode *Parser::statement()
{
	if (mCurrentToken->type == Token::TokenType::TYPE_BEGIN) {
		return compound();
	}

	if (mCurrentToken->type == Token::TokenType::TYPE_ID) {
		return assignStatement();
	}

	return empty();
}

StatementNode *Parser::assignStatement()
{
	VarNode *lv = variable();
	Token *op = mCurrentToken;
	eat(op->type);
	return new AssignStatementNode(lv, op, exp());
}

StatementNode *Parser::empty()
{
	return new NoOpStatementNode();
}

VarNode *Parser::variable()
{
	auto *var = new VarNode((IdToken *const) mCurrentToken);
	eat(Token::TokenType::TYPE_ID);
	return var;
}

ProgramNode *Parser::parse()
{
	ProgramNode *root = program();
	eat(Token::TokenType::TYPE_EOF, "eof error");
	return root;
}

BlockNode *Parser::block()
{
	LocalRef<DeclarationsNode> declarationsNode(declarations());
	LocalRef<ProceduresNode> proceduresNode(procedures());
	LocalRef<StatementNode> statementNode(compound());
	return new BlockNode(
		declarationsNode.release(),
		proceduresNode.release(),
		statementNode.release()
	);
}

DeclarationsNode *Parser::declarations()
{
	if (mCurrentToken->type != Token::TokenType::TYPE_VAR) {
		return new DeclarationsNode();
	}

	// VAR
	// a : REAL;
	// b : REAL;
	// BEGIN
	// ...
	// END
	eat(Token::TokenType::TYPE_VAR);
	std::vector<LocalRef<DeclarationsNode::Declaration>> declarations;
	while (mCurrentToken->type == Token::TokenType::TYPE_ID) {
		Token *id = mCurrentToken;
		eat(Token::TokenType::TYPE_ID);

		std::vector<Token *> ids;
		ids.push_back(id);

		// a, b, c, d : REAL
		while (mCurrentToken->type == Token::TokenType::TYPE_COMMA) {
			eat(Token::TokenType::TYPE_COMMA);
			id = mCurrentToken;
			ids.push_back(id);
			eat(Token::TokenType::TYPE_ID, "missing id after ','");
		}

		eat(Token::TokenType::TYPE_COLON, "missing ':' after declaration");
		if (mCurrentToken->type != Token::TokenType::TYPE_REAL &&
			mCurrentToken->type != Token::TokenType::TYPE_INTEGER) {
			throw ParseError("missing type after declaration");
		}

		Token *idTypeToken = mCurrentToken;
		Token::TokenType varType = idTypeToken->type;
		eat(mCurrentToken->type);
		delete idTypeToken;
		std::for_each(ids.cbegin(), ids.cend(), [&](Token *token)
		{
			declarations
				.push_back(LocalRef<DeclarationsNode::Declaration>(new DeclarationsNode::Declaration(token, varType)));
		});

		// eat ;
		if (mCurrentToken->type != Token::TokenType::TYPE_SEMI) {
			break;
		}
		eat(Token::TokenType::TYPE_SEMI);
	}

	std::vector<DeclarationsNode::Declaration *> vec;
	std::for_each(declarations.begin(), declarations.end(), [&](LocalRef<DeclarationsNode::Declaration> &ref)
	{
		vec.push_back(ref.release());
	});
	return new DeclarationsNode(vec);
}

ProceduresNode *Parser::procedures()
{
	if (mCurrentToken->type != Token::TokenType::TYPE_PROCEDURE) {
		return new ProceduresNode();
	}

	std::vector<ProceduresNode::Procedure *> vec;
	while (mCurrentToken->type == Token::TokenType::TYPE_PROCEDURE) {
		eat(Token::TokenType::TYPE_PROCEDURE);
		if (mCurrentToken->type != Token::TokenType::TYPE_ID) {
			throw ("missing id after PROCEDURE");
		}
		auto *idToken = (IdToken *) mCurrentToken;
		eat(Token::TokenType::TYPE_ID);
		FormalParametersNode *formalParametersNode = nullptr;
		if (mCurrentToken->type == Token::TokenType::TYPE_LEFT_BRACKET) {
			eat(Token::TokenType::TYPE_LEFT_BRACKET);
			formalParametersNode = formalParameters();
			eat(Token::TokenType::TYPE_RIGHT_BRACKET, "missing ')' after formal parameter list");
		}
		eat(Token::TokenType::TYPE_SEMI, "missing ';' after id or formal parameter list");
		vec.push_back(new ProceduresNode::Procedure(idToken, formalParametersNode, block()));
		eat(Token::TokenType::TYPE_SEMI, "missing ';' after block");
	}
	return new ProceduresNode(vec);
}

FormalParametersNode *Parser::formalParameters()
{
	std::vector<FormalParametersNode::Parameter *> vec;
	while (mCurrentToken->type != Token::TokenType::TYPE_RIGHT_BRACKET) {
		if (mCurrentToken->type != Token::TokenType::TYPE_ID) {
			throw ParseError("formal parameters must start with a id token");
		}
		auto *id = (IdToken *) mCurrentToken;
		eat(Token::TokenType::TYPE_ID);
		eat(Token::TokenType::TYPE_COLON, "missing ':' after id token");
		if (mCurrentToken->type != Token::TokenType::TYPE_REAL &&
			mCurrentToken->type != Token::TokenType::TYPE_INTEGER) {
			throw ParseError("unknown type in formal parameters");
		}
		vec.push_back(new FormalParametersNode::Parameter(id, mCurrentToken->type));
		eat(mCurrentToken->type);

		// has more value
		if (mCurrentToken->type == Token::TokenType::TYPE_SEMI) {
			eat(Token::TokenType::TYPE_SEMI);
		}
	}

	return new FormalParametersNode(vec);
}
