//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_VAR_H
#define SIMPLEINTERPRETER_VAR_H


#include "ASTNode.h"
class Var: public ASTNode
{
public:
	Var(Token *const token);

};


#endif //SIMPLEINTERPRETER_VAR_H
