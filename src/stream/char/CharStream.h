//
// Created by chan on 2018/8/21.
//

#ifndef SIMPLEINTERPRETER_CHARSTREAM_H
#define SIMPLEINTERPRETER_CHARSTREAM_H


#include "../Stream.h"

class CharStream: public Stream
{
private:
	int mCurrentPosition = -1;
	const char* mStr;
	int mLen;
public:
	explicit CharStream(const char *mStr);
	virtual ~CharStream();
public:
	char next() override;

	void back() override;
};


#endif //SIMPLEINTERPRETER_CHARSTREAM_H
