cmake_minimum_required(VERSION 3.21)
project(Casse_Briques C)

set(CMAKE_C_STANDARD 99)

add_executable(Casse_Briques ./code/main.c)

target_link_libraries(Casse_Briques wsock32 Ws2_32)
