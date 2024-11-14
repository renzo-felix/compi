cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)


add_executable(untitled1 exp.cpp
        parser.cpp
        scanner.cpp
        token.cpp
        visitor.cpp
        main.cpp
        imp_type.cpp
        gencode.cpp
        imp_value.cpp
        imp_value_visitor.hh)


#add_executable(untitled1 environment.hh imp.cpp imp_codegen.cpp imp_interpreter.cpp imp_parser.cpp imp_type.cpp
      #         imp_printer.cpp imp_typechecker.cpp imp_value.cpp test_imp_fun.cpp)

#add_executable(untitled1 svm.cpp svm_parser.cpp svm_run.cpp )
