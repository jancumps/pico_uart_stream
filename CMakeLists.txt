cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts -fcommon -fno-rtti -fno-exceptions")
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(pico_sdk_import.cmake)

project(pico_uart_stream C CXX ASM)

pico_sdk_init()

add_library(pico_uart_stream)
target_sources(pico_uart_stream
        PUBLIC
)
target_sources(pico_uart_stream
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/pico_uart_stream.cpp
)

target_link_libraries(pico_uart_stream
        $<COMPILE_ONLY:hardware_uart>
)
