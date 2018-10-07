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
	LocalRef<ASTNode> lhs(term());
	while (mCurrentToken->type == Token::TokenType::TYPE_SUB ||
		mCurrentToken->type == Token::TokenType::TYPE_PLUS) {
		LocalRef<Token> token(mCurrentToken);
		eat(token->type);
		LocalRef<ASTNode> rhs(term());
		lhs.set(new BinOpNode(token.release(), lhs.get(), rhs.release()));
	}
	return lhs.release();
}

ASTNode *Parser::term()
{
	LocalRef<ASTNode> lhs(factor());
	while (mCurrentToken->type == Token::TokenType::TYPE_REAL_DIV ||
		mCurrentToken->type == Token::TokenType::TYPE_INT_DIV ||
		mCurrentToken->type == Token::TokenType::TYPE_MUL) {
		LocalRef<Token> token(mCurrentToken);
		eat(token->type);
		LocalRef<ASTNode> rhs(factor());
		lhs.set(new BinOpNode(token.release(), lhs.release(), rhs.release()));
	}
	return lhs.release();
}

ASTNode *Parser::factor()
{
	LocalRef<Token> token(mCurrentToken);
	if (token->type == Token::TokenType::TYPE_LEFT_BRACKET) {
		eat(Token::TokenType::TYPE_LEFT_BRACKET);
		LocalRef<ASTNode> result(exp());
		eat(Token::TokenType::TYPE_RIGHT_BRACKET, "missing )");
		return result.release();
	}

	if (token->type == Token::TokenType::TYPE_INT_NUM) {
		eat(Token::TokenType::TYPE_INT_NUM);
		return new IntNumNode((IntNumToken *) token.release());
	}

	if (token->type == Token::TokenType::TYPE_PLUS) {
		eat(Token::TokenType::TYPE_PLUS);
		return new UnaryNode(token.release(), factor());
	}

	if (token->type == Token::TokenType::TYPE_SUB) {
		eat(Token::TokenType::TYPE_SUB);
		return new UnaryNode(token.release(), factor());
	}

	if (token->type == Token::TokenType::TYPE_ID) {
		token.release();
		return variable();
	}

	if (token->type == Token::TokenType::TYPE_REAL_NUM) {
		eat(Token::TokenType::TYPE_REAL_NUM);
		return new RealNumNode((RealNumToken *) token.release());
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
	if (mCurrentToken->type != type) {
		throw ParseError(msg);
	}

	if (mCurrentToken->type != Token::TokenType::TYPE_EOF) {
		mCurrentToken = mLexer->next();
	}
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
	std::vector<LocalRef<StatementNode>> statements;
	statements.emplace_back(statement());
	while (mCurrentToken->type == Token::TokenType::TYPE_SEMI) {
		eat(Token::TokenType::TYPE_SEMI);
		statements.emplace_back(statement());
	}

	eat(Token::TokenType::TYPE_END);
	std::vector<StatementNode *> result;
	std::for_each(statements.begin(), statements.end(), [&](LocalRef<StatementNode> &ref)
	{
		result.push_back(ref.release());
	});
	return new CompoundStatementNode(result);;
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
	LocalRef<VarNode> var(new VarNode((IdToken *const) mCurrentToken));
	eat(Token::TokenType::TYPE_ID);
	return var.release();
}

ProgramNode *Parser::parse()
{
	ProgramNode *root = program();
	LocalRef<Token> eof(mCurrentToken);
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
		LocalRef<Token> id(mCurrentToken);
		eat(Token::TokenType::TYPE_ID);

		std::vector<LocalRef<Token>> ids;
		ids.push_back(std::move(id));

		// a, b, c, d : REAL
		while (mCurrentToken->type == Token::TokenType::TYPE_COMMA) {
			eat(Token::TokenType::TYPE_COMMA);
			ids.emplace_back(mCurrentToken);
			eat(Token::TokenType::TYPE_ID, "missing id after ','");
		}

		eat(Token::TokenType::TYPE_COLON, "missing ':' after declaration");
		if (mCurrentToken->type != Token::TokenType::TYPE_REAL &&
			mCurrentToken->type != Token::TokenType::TYPE_INTEGER) {
			throw ParseError("missing type after declaration");
		}

		LocalRef<Token> idTypeToken(mCurrentToken);
		Token::TokenType varType = idTypeToken->type;
		eat(mCurrentToken->type);
		std::for_each(ids.begin(), ids.end(), [&](LocalRef<Token> &token)
		{
			declarations.push_back(LocalRef<DeclarationsNode::Declaration>(
				new DeclarationsNode::Declaration(token.release(), varType)));
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

	std::vector<LocalRef<ProceduresNode::Procedure>> vec;
	while (mCurrentToken->type == Token::TokenType::TYPE_PROCEDURE) {
		eat(Token::TokenType::TYPE_PROCEDURE);
		if (mCurrentToken->type != Token::TokenType::TYPE_ID) {
			throw ("missing id after PROCEDURE");
		}

		LocalRef<IdToken> idToken((IdToken *) mCurrentToken);
		eat(Token::TokenType::TYPE_ID);
		LocalRef<FormalParametersNode> formalParametersNode;
		if (mCurrentToken->type == Token::TokenType::TYPE_LEFT_BRACKET) {
			eat(Token::TokenType::TYPE_LEFT_BRACKET);
			formalParametersNode.set(formalParameters());
			eat(Token::TokenType::TYPE_RIGHT_BRACKET, "missing ')' after formal parameter list");
		}

		eat(Token::TokenType::TYPE_SEMI, "missing ';' after id or formal parameter list");
		LocalRef<BlockNode> blockNode(block());
		vec.push_back(LocalRef<ProceduresNode::Procedure>(new ProceduresNode::Procedure(idToken.release(),
																						formalParametersNode.release(),
																						blockNode.release())));
		eat(Token::TokenType::TYPE_SEMI, "missing ';' after block");
	}

	std::vector<ProceduresNode::Procedure *> result;
	std::for_each(vec.begin(), vec.end(), [&](LocalRef<ProceduresNode::Procedure> &ref)
	{
		result.push_back(ref.release());
	});

	return new ProceduresNode(result);
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
