cmake_minimum_required(VERSION 3.6)
project(SimpleInterpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp parser/token/Token.h interpreter/Interpreter.cpp interpreter/Interpreter.h stream/Stream.h stream/char/CharStream.cpp stream/char/CharStream.h exception/ParseError.h exception/EOFError.h exception/RuntimeError.h parser/ast/AbstractSyntaxTree.cpp parser/ast/AbstractSyntaxTree.h parser/Parser.cpp parser/Parser.h)
add_executable(SimpleInterpreter ${SOURCE_FILES})