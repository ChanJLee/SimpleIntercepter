//
// Created by chan on 2018/8/22.
//

#ifndef SIMPLEINTERPRETER_LEXER_H
#define SIMPLEINTERPRETER_LEXER_H

#include "../stream/Stream.h"
#include "../token/Token.h"

class Lexer
{
private:
	Stream *mStream;
public:
	Lexer(Stream *stream);

	Token* next();

	bool hasNext();

	void back(Token *token);
private:
	Token* nextNumber();
};


#endif //SIMPLEINTERPRETER_LEXER_H
