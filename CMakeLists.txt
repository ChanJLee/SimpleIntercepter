cmake_minimum_required(VERSION 3.6)
project(SimpleInterpreter)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DDEBUG)

set(SOURCE_FILES main.cpp token/Token.h interpreter/Interpreter.cpp interpreter/Interpreter.h stream/Stream.h stream/char/CharStream.cpp stream/char/CharStream.h exception/ParseError.h parser/Parser.cpp parser/Parser.h parser/ast/BinOpNode.cpp parser/ast/BinOpNode.h lexer/Lexer.cpp lexer/Lexer.h parser/ast/ASTNode.cpp parser/ast/ASTNode.h parser/ast/IntNumNode.cpp parser/ast/IntNumNode.h parser/ast/UnaryNode.cpp parser/ast/UnaryNode.h utils/CharUtils.h parser/ast/CompoundStatementNode.cpp parser/ast/CompoundStatementNode.h parser/ast/StatementNode.cpp parser/ast/StatementNode.h parser/ast/NoOpStatementNode.cpp parser/ast/NoOpStatementNode.h parser/ast/AssignStatementNode.cpp parser/ast/AssignStatementNode.h parser/ast/VarNode.cpp parser/ast/VarNode.h token/IntNumToken.cpp token/IntNumToken.h token/IdToken.cpp token/IdToken.h token/RealNumToken.cpp token/RealNumToken.h parser/ast/RealNumNode.cpp parser/ast/RealNumNode.h parser/ast/ProgramNode.cpp parser/ast/ProgramNode.h parser/ast/BlockNode.cpp parser/ast/BlockNode.h parser/ast/DeclarationsNode.cpp parser/ast/DeclarationsNode.h interpreter/st/SymbolTable.cpp interpreter/st/SymbolTable.h interpreter/symbol/Symbol.cpp interpreter/symbol/Symbol.h)
add_executable(SimpleInterpreter ${SOURCE_FILES})