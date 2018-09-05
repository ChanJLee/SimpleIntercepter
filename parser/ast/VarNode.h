//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_VAR_H
#define SIMPLEINTERPRETER_VAR_H


#include "ASTNode.h"
#include "../../token/IdToken.h"
class VarNode: public ASTNode
{
public:
	VarNode(IdToken *token);

};


#endif //SIMPLEINTERPRETER_VAR_H
