cmake_minimum_required(VERSION 3.28)

include(pico_sdk_import.cmake)

project(pio_irq C CXX ASM)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts -fcommon")

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

target_link_libraries( pico_uart_stream
        $<COMPILE_ONLY:pico_stdlib>
        $<COMPILE_ONLY:hardware_uart>
)

