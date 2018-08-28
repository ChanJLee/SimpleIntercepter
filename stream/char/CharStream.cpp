//
// Created by chan on 2018/8/21.
//

#include "CharStream.h"
#include "../../exception/EOFError.h"
#include <string>

char CharStream::next()
{
	if (!hasNext()) {
		throw EOFError("End of stream");
	}

	return mStr[++mCurrentPosition];
}

void CharStream::back()
{
	--mCurrentPosition;
}

CharStream::CharStream(const char *mStr)
	: mStr(mStr), mCurrentPosition(-1)
{}

bool CharStream::hasNext()
{
	if (mStr == NULL) {
		return false;
	}

	return mCurrentPosition + 1 >= 0 && mCurrentPosition + 1 < strlen(mStr);
}
