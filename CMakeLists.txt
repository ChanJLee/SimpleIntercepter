cmake_minimum_required(VERSION 3.6)
project(SimpleInterpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Token.h Interpreter.cpp Interpreter.h Stream.h StdIOStream.cpp StdIOStream.h)
add_executable(SimpleInterpreter ${SOURCE_FILES})