//
// Created by chan on 2018/8/21.
//

#include "CharStream.h"
#include "../../e/EOFError.h"
#include <string>

char CharStream::next()
{
	if (!hasNext()) {
		throw EOFError("End of stream");
	}

	return mStr[mCurrentPosition++];
}

void CharStream::back()
{
	if (mCurrentPosition == 0) {
		return;
	}
	--mCurrentPosition;
}

CharStream::CharStream(const char *mStr)
	: mStr(mStr), mCurrentPosition(0)
{}

bool CharStream::hasNext()
{
	if (mStr == NULL) {
		return false;
	}

	return mCurrentPosition < strlen(mStr);
}
