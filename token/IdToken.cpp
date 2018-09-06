//
// Created by chan on 2018/9/5.
//

#include "IdToken.h"
IdToken::IdToken(const std::string &value)
	: IdToken(value, IdToken::IdTokenType::NONE)
{}

IdToken::IdToken(const std::string &value, IdToken::IdTokenType type)
	: Token(TokenType::TYPE_ID), value(value), type(type)
{

}
