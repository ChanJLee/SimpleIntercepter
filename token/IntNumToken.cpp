//
// Created by chan on 2018/9/5.
//

#include "IntNumToken.h"

IntNumToken::IntNumToken(int value)
	: Token(Token::TokenType::TYPE_INT_NUM), value(value)
{}
