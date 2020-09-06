cmake_minimum_required(VERSION 3.17)
project(judger)

set(CMAKE_CXX_STANDARD 11)
add_executable(parse
        initservice.h
        parse.cpp
        exit_code.h
        main.cpp
        filecompare.h
        parse.cpp
        parse.h
        result.h
        utils.h)
