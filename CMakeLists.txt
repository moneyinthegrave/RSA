cmake_minimum_required(VERSION 3.17)
project(RSA)

set(CMAKE_CXX_STANDARD 20)

add_executable(RSA main/main.cpp main/md5.cpp main/md5.h)

