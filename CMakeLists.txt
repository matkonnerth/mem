cmake_minimum_required(VERSION 3.0)

project(blockallocator C)

option(ENABLE_ASAN off "build with address sanitizer enabled")

set(C_COMPILE_DEFS -std=c99 -pipe -Wall -Wextra -Wpedantic -Werror 
                    -Wno-static-in-inline # clang doesn't like the use of static inline methods inside static inline methods
                    -Wno-overlength-strings # may happen in the nodeset compiler when complex values are directly encoded
                    -Wno-unused-parameter # some methods may require unused arguments to cast to a method pointer
                    -Wmissing-prototypes -Wstrict-prototypes -Wredundant-decls
                    -Wformat -Wformat-security -Wformat-nonliteral
                    -Wuninitialized -Winit-self
                    -Wcast-qual
                    -Wstrict-overflow
                    -Wnested-externs
                    -Wmultichar
                    -Wundef
                    -Wc++-compat
                    -Wsign-conversion
                    -Wconversion
                    -Wshadow
                    -fno-strict-aliasing # fewer compiler assumptions about pointer types
                    -fexceptions
                    -Wswitch-enum)

if(${ENABLE_ASAN})
    set(${C_COMPILE_DEFS} -g -fsanitize=address -fsanitize=leak -fsanitize=undefined)
endif()

add_library(BlockAllocator SHARED
    src/BlockAllocator.c)
target_include_directories(BlockAllocator PUBLIC include)