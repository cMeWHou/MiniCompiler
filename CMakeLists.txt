# CMake configuration
cmake_minimum_required(VERSION 3.0.0)

project(MiniCompiler VERSION 0.1.0)

# Script variables
set(LEXER_SRC   "Lexer.c"           "Dictionary.c")
set(PARSER_SRC  "Parser.c"          "Node.c")
set(VM_SRC      "VirtualMachine.c"  "Compiler.c"    "Stack.c")
set(MAIN_SRC    "Main.c")

set(SRCS        ${LEXER_SRC} ${PARSER_SRC} ${VM_SRC} ${MAIN_SRC})

# Script properties
add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}\\include\\")
