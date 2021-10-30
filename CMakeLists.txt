cmake_minimum_required(VERSION 3.18)
project(eedd)

set(CMAKE_CXX_STANDARD 11)

add_executable(eedd main.cpp VDinamico.h Fecha.cpp Fecha.h Dosis.cpp Dosis.h ListaEnlazada.h Usuario.cpp Usuario.h GestionVacunas.cpp GestionVacunas.h)
