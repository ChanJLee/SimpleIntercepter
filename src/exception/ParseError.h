//
// Created by chan on 2018/8/21.
//

#ifndef SIMPLEINTERPRETER_PARSEERROR_H
#define SIMPLEINTERPRETER_PARSEERROR_H

#include <exception>
#include <string>

class ParseError: public std::exception
{
public:
	const std::string msg;
public:
	ParseError(const std::string &msg)
		: msg(msg)
	{}
};


#endif //SIMPLEINTERPRETER_PARSEERROR_H
