//
// Created by chan on 2018/8/19.
//

#ifndef SIMPLEINTERPRETER_STREAM_H
#define SIMPLEINTERPRETER_STREAM_H


class Stream
{
public:
	virtual char next() = 0;

	virtual void back(int len) = 0;

	virtual bool hasNext() = 0;
};


#endif //SIMPLEINTERPRETER_STREAM_H
