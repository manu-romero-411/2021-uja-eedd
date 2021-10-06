cmake_minimum_required(VERSION 3.20)
project(eedd)

set(CMAKE_CXX_STANDARD 11)

add_executable(eedd main.cpp VDinamico.h fecha.cpp fecha.h Dosis.cpp Dosis.h)
