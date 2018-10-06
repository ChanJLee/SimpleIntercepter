//
// Created by chan on 2018/10/6.
//

#ifndef SIMPLEINTERPRETER_LOG_H
#define SIMPLEINTERPRETER_LOG_H

#include <iostream>

#ifdef DEBUG
#define __LOG(...) printf(__VA_ARGS__)
#else
#define __LOG(...) (void*) 0
#endif

#define LOG(...) __LOG(__VA_ARGS__)

#endif //SIMPLEINTERPRETER_LOG_H
