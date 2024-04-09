cmake_minimum_required(VERSION 3.28)
project(Code)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    -O2
    -lm
    -Wall
    -Wextra
    -march=native
    -fno-asm
    -ffast-math
    -fuse-ld=lld
)
