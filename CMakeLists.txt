cmake_minimum_required(VERSION 3.16)
project(ChangeCipher)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChangeCipher main.cpp MyCipher.h MyCipher.cpp)