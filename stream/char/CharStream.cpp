//
// Created by chan on 2018/8/21.
//

#include "CharStream.h"
#include <string>

char CharStream::next()
{
	if (mCurrentPosition + 1 >= mLen) {
		return EOF;
	}

	return mStr[++mCurrentPosition];
}

void CharStream::back()
{
	if (mCurrentPosition >= -1) {
		--mCurrentPosition;
	}
}

CharStream::CharStream(const char *mStr)
	: mStr(mStr), mCurrentPosition(-1)
{
	mLen = (int) (mStr == nullptr ? 0 : strlen(mStr));
}

CharStream::~CharStream()
{
	mStr = nullptr;
}
