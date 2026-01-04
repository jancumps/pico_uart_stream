module;

#include "hardware/uart.h"

#include <array>
#include <ranges>
#include <string>

export module pico_uart_stream;

export namespace pico_uart_stream {

class uartostream {
public:
    uartostream(uart_inst_t *uart) : uart_(uart) {}

    uartostream& operator << (const char* msg) {
        // write to UART
        uart_puts(uart_, msg);
        return *this;
    }

    uartostream& operator << (const std::string& msg) {
        uart_puts(uart_, msg.c_str());
        return *this;
    }

private:
    uart_inst_t * uart_;
};

class uartistream {
public:
    uartistream(uart_inst_t *uart) : uart_(uart) {}
  
    uartistream& operator >> (std::string& msg) { // blocking
        char c  = 0;
        // msg.clear(); no. If the string has info, add to it.
        do { 
            c = uart_getc(uart_);
            if (c < 254) { // discard occurances of 254 and 255 that are sometimes in the input buffer before starting
                msg += c;
            }
        } while (c != '\n');
        return *this;
    }

private:
    uart_inst_t * uart_;
};

class uartiostream: public uartistream, public uartostream {
public:    
    uartiostream(uart_inst_t *uart) : uartistream(uart), uartostream(uart) {}
};

} // namespace pico_uart_stream