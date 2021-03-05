cmake_minimum_required(VERSION 3.17)
project(Godunov_Shock_Tube)

set(CMAKE_CXX_STANDARD 14 -std=c++14 -g -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -fsanitize=address -O3
        --ffast-math)



add_executable(Godunov_Shock_Tube main.cpp initial.h  sample.h starpu.h starpu.cpp sample.cpp gas.cpp gas.h)