//
// Created by chan on 2018/9/6.
//

#include "RealNumToken.h"
RealNumToken::RealNumToken(double value)
	: Token(Token::TokenType::TYPE_REAL_NUM), value(value)
{}
