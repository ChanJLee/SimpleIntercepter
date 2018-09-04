//
// Created by chan on 2018/9/4.
//

#ifndef SIMPLEINTERPRETER_NOOPNODE_H
#define SIMPLEINTERPRETER_NOOPNODE_H


#include "ASTNode.h"
#include "StatementNode.h"

class NoOpNode: public StatementNode
{
public:
	NoOpNode();
};


#endif //SIMPLEINTERPRETER_NOOPNODE_H
