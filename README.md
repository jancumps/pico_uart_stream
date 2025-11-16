# pico_uart_stream library
Raspberry Pico library that lets you stream text from and to UART.  
Goal: have C++ style streaming, at no runtime overhead. This is embedded friendly code.
```cpp
u << "hello world!\n" ;  
```
It's intended for object oriented designs, where streaming is a common practice.

## documentation:
[1: usage and example](https://community.element14.com/products/raspberry-pi/b/blog/posts/c-write-your-own-stream-class---part-2-pico-uart-io-stream-embedded-friendly-c)  
[2: verify that this does not cause runtime overhead](https://community.element14.com/technologies/code_exchange/b/blog/posts/c-write-your-own-stream-class---part-1a-the-cost-of-objects-can-be-zero-embedded-friendly-c)  


## Example: stream a text to UART, then echo any received data via in and out stream:  
Check [usage and example](https://community.element14.com/products/raspberry-pi/b/blog/posts/c-write-your-own-stream-class---part-2-pico-uart-io-stream-embedded-friendly-c) for the complete example code.   
```cpp
import pico_uart_stream;

// UART defines
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

void pico_init_uart() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
    gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));
}

int main() {
    pico_init_uart();
    pico_uart_stream::uartiostream u(UART_ID);
    u << "hello world!\n" ;  

    while (true) {
        std::string s;
        u >> s;
        u << s;
    }
}
```
## Adding the lib to your Raspberry Pico project
The repository has its own makefile. you add it by fetching from it in your ```CMakeFiles.txt```. It is then available to your code as library stepper.
```cmake
# your CMakeFiles.txt

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts -fcommon -fno-rtti -fno-exceptions")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ... 

FetchContent_Declare(pico_uart_stream
  GIT_REPOSITORY "https://github.com/jancumps/pico_uart_stream.git"
  GIT_TAG "origin/main"
)
FetchContent_MakeAvailable(pico_uart_stream)

# ...

# add stepper as a library to your executable
add_executable(your_project)
# ...
target_link_libraries(your_project
        pico_stdlib
        hardware_uart
        pico_uart_stream
)
```
That is all it takes to integrate this design in your project.


## toolchain requirements: 
- CMake 3.28 or higher
- GCC 14.3 or higher
- Pico C SDK 2.1.1
- tested with Pico 1, Pico-W, Pico2, Pico2-W (ARM and RISC-V)