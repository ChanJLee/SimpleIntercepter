//
// Created by chan on 2018/8/21.
//

#ifndef SIMPLEINTERPRETER_CHARSTREAM_H
#define SIMPLEINTERPRETER_CHARSTREAM_H


#include "../Stream.h"
#include <ctype.h>

class CharStream: public Stream
{
private:
	int mCurrentPosition = -1;
	const char* mStr;
	int mLen;
public:
	CharStream(const char *mStr);
public:
	char next();

	void back();
};


#endif //SIMPLEINTERPRETER_CHARSTREAM_H
