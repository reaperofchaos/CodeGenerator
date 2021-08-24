cmake_minimum_required(VERSION 3.0)
set(PROJECTNAME "CodeGenerator")
project(CodeGenerator)
include(CheckCCompilerFlag)

set(CMAKE_HOST_SYSTEM_PROCESSOR "arm64")

add_executable(${PROJECTNAME} main.cpp FileReader.cpp FileCreator.cpp CPPFileCreator.cpp PythonFileCreator.cpp)
