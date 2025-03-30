cmake_minimum_required(VERSION 3.28)
project(abx_writer C)

set(CMAKE_C_STANDARD 23)

add_executable(abx_writer src/main.c
		src/bitwise.c)