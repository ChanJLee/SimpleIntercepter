//
// Created by chan on 2018/9/6.
//

#ifndef SIMPLEINTERPRETER_REALNUMNODE_H
#define SIMPLEINTERPRETER_REALNUMNODE_H


#include "ASTNode.h"
#include "../../token/RealNumToken.h"
class RealNumNode: public ASTNode
{
public:
	explicit RealNumNode(RealNumToken * token);
};


#endif //SIMPLEINTERPRETER_REALNUMNODE_H
