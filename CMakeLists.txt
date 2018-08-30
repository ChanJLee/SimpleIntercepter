cmake_minimum_required(VERSION 3.6)
project(SimpleInterpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp token/Token.h interpreter/Interpreter.cpp interpreter/Interpreter.h stream/Stream.h stream/char/CharStream.cpp stream/char/CharStream.h exception/ParseError.h exception/EOFError.h parser/Parser.cpp parser/Parser.h parser/ast/BinOpNode.cpp parser/ast/BinOpNode.h lexer/Lexer.cpp lexer/Lexer.h parser/ast/ASTNode.cpp parser/ast/ASTNode.h parser/ast/NumNode.cpp parser/ast/NumNode.h parser/ast/UnaryNode.cpp parser/ast/UnaryNode.h utils/CharUtils.h)
add_executable(SimpleInterpreter ${SOURCE_FILES})