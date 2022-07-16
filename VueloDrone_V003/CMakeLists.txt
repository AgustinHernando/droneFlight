cmake_minimum_required(VERSION 3.17)
project(VueloDrone_V00)

set(CMAKE_CXX_STANDARD 14)

add_executable(VueloDrone_V00 main.cpp Ciclo_Hamilton.h Ciclo_Hamilton.tpp Grafos.h Grafos.tpp BusquedaAmplitud.h BusquedaAmplitud.tpp Cola.tpp Cola.h Segmento.h)