//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_VAR_H
#define SIMPLEINTERPRETER_VAR_H


#include "ASTNode.h"
class VarNode: public ASTNode
{
public:
	VarNode(Token *const token);

};


#endif //SIMPLEINTERPRETER_VAR_H
