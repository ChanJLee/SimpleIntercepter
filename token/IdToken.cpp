//
// Created by chan on 2018/9/5.
//

#include "IdToken.h"
IdToken::IdToken(const std::string& value)
	: Token(TokenType::TYPE_ID), value(value)
{}
