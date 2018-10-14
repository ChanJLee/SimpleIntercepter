#include <iostream>
#include "stream/char/CharStream.h"
#include "interpreter/Interpreter.h"
#include "exception/ParseError.h"
#include "semantic/SemanticAnalyzer.h"
#include <fstream>
#include <sstream>

void checkUnit()
{
	Lexer lexer = Lexer(new CharStream("BEGIN"));
	Token *token = lexer.next();
	if (token->type != Token::TokenType::TYPE_BEGIN) {
		std::cerr << "BEGIN failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "BEGIN end" << std::endl;
	}

	lexer = Lexer(new CharStream("END"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_END) {
		std::cerr << "END" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "EOF end" << std::endl;
	}

	lexer = Lexer(new CharStream(";"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_SEMI) {
		std::cerr << "SEMI failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "SEMI end" << std::endl;
	}

	lexer = Lexer(new CharStream("hello"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_ID) {
		std::cerr << "id failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "id end" << std::endl;
	}

	lexer = Lexer(new CharStream("123"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_INT_NUM) {
		std::cerr << "NUMBER failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "NUMBER end" << std::endl;
	}

	lexer = Lexer(new CharStream("."));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_DOT) {
		std::cerr << "TYPE_DOT failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "TYPE_DOT end" << std::endl;
	}

	lexer = Lexer(new CharStream(":"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_COLON) {
		std::cerr << "TYPE_COLON failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "TYPE_COLON end" << std::endl;
	}

	lexer = Lexer(new CharStream(":="));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_ASSIGN) {
		std::cerr << "TYPE_ASSIGN failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "TYPE_ASSIGN end" << std::endl;
	}

	lexer = Lexer(new CharStream("VAR"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_VAR) {
		std::cerr << "TYPE_VAR failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "TYPE_VAR end" << std::endl;
	}

	lexer = Lexer(new CharStream("PROGRAM"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_PROGRAM) {
		std::cerr << "TYPE_PROGRAM failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "TYPE_PROGRAM end" << std::endl;
	}

	lexer = Lexer(new CharStream("DIV"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_INT_DIV) {
		std::cerr << "DIV failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "DIV end" << std::endl;
	}

	lexer = Lexer(new CharStream("INTEGER"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_INTEGER) {
		std::cerr << "INTEGER; failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "INTEGER; end" << std::endl;
	}

	lexer = Lexer(new CharStream("REAL"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_REAL) {
		std::cerr << "real failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "real end" << std::endl;
	}
	lexer = Lexer(new CharStream("PROCEDURE"));
	token = lexer.next();
	if (token->type != Token::TokenType::TYPE_PROCEDURE) {
		std::cerr << "PROCEDURE failed" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "PROCEDURE end" << std::endl;
	}
}

void checkStream()
{
	Lexer lexer = Lexer(new CharStream("BEGIN 1+2/3.0;x:=y END."));
	Token *token = lexer.next();
	if (token->type != Token::TokenType::TYPE_BEGIN) {
		std::cerr << "TYPE_BEGIN failed" << std::endl;
	}

	if ((token = lexer.next())->type != Token::TokenType::TYPE_INT_NUM) {
		std::cerr << "TYPE_INT_NUM end" << std::endl;
	}

	if ((token = lexer.next())->type != Token::TokenType::TYPE_PLUS) {
		std::cerr << "TYPE_PLUS end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_INT_NUM) {
		std::cerr << "TYPE_INT_NUM end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_REAL_DIV) {
		std::cerr << "TYPE_REAL_DIV end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_REAL_NUM) {
		std::cerr << "TYPE_REAL_NUM end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_SEMI) {
		std::cerr << "TYPE_SEMI end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_ID) {
		std::cerr << "TYPE_ID end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_ASSIGN) {
		std::cerr << "TYPE_ASSIGN end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_ID) {
		std::cerr << "TYPE_ID end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_END) {
		std::cerr << "TYPE_END end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_DOT) {
		std::cerr << "TYPE_DOT end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_EOF) {
		std::cerr << "check stream end" << std::endl;
	}
}

void readPas()
{
	std::ifstream infile;
	infile.open("/Users/chan/ClionProjects/SimpleInterpreter/src/test_st.pas");
	std::stringstream ss;
	char ch;
	while (!infile.eof()) {
		infile >> std::noskipws >> ch;
		ss.put(ch);
	}
	infile.close();

	std::string content = ss.str();
	std::cout << content;
	ProgramNode *root = nullptr;
	try {
		Stream *stream = new CharStream(content.c_str());
		Lexer lexer(stream);
		Parser parser(&lexer);
		root = parser.parse();
		SemanticAnalyzer syntaxChecker(root);
		syntaxChecker.check();
		Interpreter interpreter(root);
		interpreter.interpret();
		delete stream;
	}
	catch (const ParseError &error) {
		std::cerr << error.msg << std::endl;
		delete root;
	}
}

void printToken()
{
	std::ifstream infile;
	infile.open("/Users/chan/ClionProjects/SimpleInterpreter/test.pas");
	std::stringstream ss;
	char ch;
	while (!infile.eof()) {
		infile >> std::noskipws >> ch;
		ss.put(ch);
	}
	infile.close();

	std::string content = ss.str();
	std::cout << content << std::endl;

	Lexer lexer = Lexer(new CharStream(content.c_str()));
	Token *token = lexer.next();
	while (token->type != Token::TokenType::TYPE_EOF) {
		switch (token->type) {
			case Token::TokenType::TYPE_PLUS : std::cout << "plus" << std::endl;
				break;
			case Token::TokenType::TYPE_SUB : std::cout << "sub" << std::endl;
				break;
			case Token::TokenType::TYPE_MUL : std::cout << "mul" << std::endl;
				break;
			case Token::TokenType::TYPE_REAL_DIV : std::cout << "float div" << std::endl;
				break;
			case Token::TokenType::TYPE_INT_DIV : std::cout << "int div" << std::endl;
				break;
			case Token::TokenType::TYPE_LEFT_BRACKET : std::cout << "left bracket" << std::endl;
				break;
			case Token::TokenType::TYPE_RIGHT_BRACKET : std::cout << "right bracket" << std::endl;
				break;
			case Token::TokenType::TYPE_INT_NUM : {
				auto *numToken = (IntNumToken *) token;
				std::cout << "int number: " << numToken->value << std::endl;
				break;
			}
			case Token::TokenType::TYPE_REAL_NUM : {
				auto *numToken = (RealNumToken *) token;
				std::cout << "real number: " << numToken->value << std::endl;
				break;
			}
			case Token::TokenType::TYPE_EOF : std::cout << "eof" << std::endl;
				break;
			case Token::TokenType::TYPE_BEGIN : std::cout << "begin" << std::endl;
				break;
			case Token::TokenType::TYPE_END : std::cout << "end" << std::endl;
				break;
			case Token::TokenType::TYPE_DOT : std::cout << "dot" << std::endl;
				break;
			case Token::TokenType::TYPE_COLON : std::cout << "colon" << std::endl;
				break;
			case Token::TokenType::TYPE_ASSIGN : std::cout << "assign" << std::endl;
				break;
			case Token::TokenType::TYPE_SEMI : std::cout << "semi" << std::endl;
				break;
			case Token::TokenType::TYPE_ID : {
				IdToken *idToken = (IdToken *) token;
				std::cout << "id: " << idToken->value << std::endl;
				break;
			}
			case Token::TokenType::TYPE_COMMA : std::cout << "comma" << std::endl;
				break;
			case Token::TokenType::TYPE_PROGRAM : std::cout << "PROGRAM" << std::endl;
				break;
			case Token::TokenType::TYPE_REAL : std::cout << "REAL" << std::endl;
				break;
			case Token::TokenType::TYPE_INTEGER : std::cout << "INTEGER" << std::endl;
				break;
			case Token::TokenType::TYPE_VAR : std::cout << "VAR" << std::endl;
				break;
			case Token::TokenType::TYPE_PROCEDURE : std::cout << "PROCEDURE" << std::endl;
				break;
			default: std::cerr << "unknown error: " << std::endl;
				break;
		}
		token = lexer.next();
	}
}

void testAssign()
{
	std::ifstream infile;
	infile.open("/Users/chan/ClionProjects/SimpleInterpreter/test_assign.pas");
	std::stringstream ss;
	char ch;
	while (!infile.eof()) {
		infile >> std::noskipws >> ch;
		ss.put(ch);
	}
	infile.close();

	std::string content = ss.str();
	std::cout << content << std::endl;

	Lexer lexer = Lexer(new CharStream(content.c_str()));
	Parser parser(&lexer);
	SemanticAnalyzer checker(parser.parse());
	try {
		checker.check();
	}
	catch (const ParseError &e) {
		std::cerr << e.msg << std::endl;
	}
}

void testDefine()
{
	std::ifstream infile;
	infile.open("/Users/chan/ClionProjects/SimpleInterpreter/test_define.pas");
	std::stringstream ss;
	char ch;
	while (!infile.eof()) {
		infile >> std::noskipws >> ch;
		ss.put(ch);
	}
	infile.close();

	std::string content = ss.str();
	std::cout << content << std::endl;

	Lexer lexer = Lexer(new CharStream(content.c_str()));
	Parser parser(&lexer);
	SemanticAnalyzer checker(parser.parse());
	try {
		checker.check();
	}
	catch (const ParseError &e) {
		std::cerr << e.msg << std::endl;
	}
}

int main()
{
//	checkUnit();
//	checkStream();
	readPas();
//	printToken();
//	testAssign();
//	testDefine();

	return 0;
}