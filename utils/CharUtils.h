//
// Created by chan on 2018/8/30.
//

#ifndef SIMPLEINTERPRETER_CHARUTILS_H
#define SIMPLEINTERPRETER_CHARUTILS_H

inline bool is_num(char ch) {
	return ch >= '0' && ch <= '9';
}

inline bool is_alpha(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

#endif //SIMPLEINTERPRETER_CHARUTILS_H
