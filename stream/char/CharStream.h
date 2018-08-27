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
public:
	CharStream(const char *mStr);
public:
	char next();
	void back(int len);
	bool hasNext();
};


#endif //SIMPLEINTERPRETER_CHARSTREAM_H
