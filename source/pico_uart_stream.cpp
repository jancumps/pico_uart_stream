module;

#include "hardware/uart.h"

#include <array>
#include <ranges>
#include <string>

export module pico_uart_stream;

export namespace pico_uart_stream {

class uartostream {
public:
    uartostream(uart_inst_t *uart) : uart(uart) {}

    uartostream& operator << (const char* msg) {
        // write to UART
        uart_puts(uart, msg);
        return *this;
    }

    uartostream& operator << (const std::string& msg) {
        uart_puts(uart, msg.c_str());
        return *this;
    }

private:
    uart_inst_t * uart;
};

class uartistream {
public:
    uartistream(uart_inst_t *uart) : uart(uart) {}
  
    uartistream& operator >> (std::string& msg) { // blocking
        char c  = 0;
        // msg.clear(); no. If the string has info, add to it.
        do { 
            c = uart_getc(uart);
            if (c != 255) {
                msg += c;
            }
        } while (c != '\n');
        return *this;
    }

private:
    uart_inst_t * uart;
};

class uartiostream: public uartistream, public uartostream {
public:    
    uartiostream(uart_inst_t *uart) : uartistream(uart), uartostream(uart) {}
};

} // namespace pico_uart_stream