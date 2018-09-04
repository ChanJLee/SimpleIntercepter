cmake_minimum_required(VERSION 3.6)
project(SimpleInterpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp token/Token.h interpreter/Interpreter.cpp interpreter/Interpreter.h stream/Stream.h stream/char/CharStream.cpp stream/char/CharStream.h exception/ParseError.h exception/EOFError.h parser/Parser.cpp parser/Parser.h parser/ast/BinOpNode.cpp parser/ast/BinOpNode.h lexer/Lexer.cpp lexer/Lexer.h parser/ast/ASTNode.cpp parser/ast/ASTNode.h parser/ast/NumNode.cpp parser/ast/NumNode.h parser/ast/UnaryNode.cpp parser/ast/UnaryNode.h utils/CharUtils.h parser/ast/CompoundStatementNode.cpp parser/ast/CompoundStatementNode.h parser/ast/StatementNode.cpp parser/ast/StatementNode.h parser/ast/NoOpNode.cpp parser/ast/NoOpNode.h parser/ast/AssignStatementNode.cpp parser/ast/AssignStatementNode.h parser/ast/Var.cpp parser/ast/Var.h)
add_executable(SimpleInterpreter ${SOURCE_FILES})