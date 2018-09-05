#include <iostream>
#include "stream/char/CharStream.h"
#include "interpreter/Interpreter.h"
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
	if (token->type != Token::TokenType::TYPE_NUMBER) {
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
}

void checkStream()
{
	Lexer lexer = Lexer(new CharStream("BEGIN 1+2/3;x:=y END."));
	Token *token = lexer.next();
	if (token->type != Token::TokenType::TYPE_BEGIN) {
		std::cerr << "TYPE_BEGIN failed" << std::endl;
	}

	if ((token = lexer.next())->type != Token::TokenType::TYPE_NUMBER) {
		std::cerr << "TYPE_NUMBER end" << std::endl;
	}

	if ((token = lexer.next())->type != Token::TokenType::TYPE_PLUS) {
		std::cerr << "TYPE_PLUS end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_NUMBER) {
		std::cerr << "TYPE_NUMBER end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_DIV) {
		std::cerr << "TYPE_DIV end" << std::endl;
	}
	if ((token = lexer.next())->type != Token::TokenType::TYPE_NUMBER) {
		std::cerr << "TYPE_NUMBER end" << std::endl;
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

// trim from start
static inline std::string &ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
									std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(),
						 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s)
{
	return ltrim(rtrim(s));
}

void readPas()
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
	std::cout << content;
	Lexer lexer = Lexer(new CharStream(trim(content).c_str()));
	Token *token = lexer.next();
	while (token->type != Token::TokenType::TYPE_EOF) {
		switch (token->type) {
			case Token::TokenType::TYPE_PLUS : std::cout << "plus" << std::endl;
				break;
			case Token::TokenType::TYPE_SUB : std::cout << "sub" << std::endl;
				break;
			case Token::TokenType::TYPE_MUL : std::cout << "mul" << std::endl;
				break;
			case Token::TokenType::TYPE_DIV : std::cout << "div" << std::endl;
				break;
			case Token::TokenType::TYPE_LEFT_BRACKET : std::cout << "left bracket" << std::endl;
				break;
			case Token::TokenType::TYPE_RIGHT_BRACKET : std::cout << "right bracket" << std::endl;
				break;
			case Token::TokenType::TYPE_NUMBER : {
				NumToken *numToken = (NumToken *) token;
				std::cout << "number: " << numToken->value << std::endl;
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
			default: std::cerr << "unknown error: " << std::endl;
				break;
		}

		delete token;
		token = lexer.next();
	}
}

int main()
{
//	checkUnit();
//	checkStream();
	readPas();
	return 0;
}