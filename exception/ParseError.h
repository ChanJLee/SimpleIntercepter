//
// Created by chan on 2018/8/21.
//

#ifndef SIMPLEINTERPRETER_PARSEERROR_H
#define SIMPLEINTERPRETER_PARSEERROR_H


class ParseError
{
private:
	const char* mMsg;
public:
	ParseError(const char *msg)
		: mMsg(msg)
	{}

	const char *getMsg() const
	{
		return mMsg;
	}
};


#endif //SIMPLEINTERPRETER_PARSEERROR_H
