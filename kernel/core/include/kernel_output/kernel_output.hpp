#pragma once
#include "../framework.h"

namespace sion64 {
    class kernel_output {
    public:
        // Low-level UART
        static void putC(char c);
        static void putS(const char* str);

        // Number output
        static void putD(s64 num);
        static void putX(u64 num);

        // String / padding helpers
        static int  str_len(const char* str);
        static int  num_len(u64 value);
        static int  hex_len(u64 value);
        static void put_pad(int width, int len);

        // va_list formatter (printf-like)
        static void vprintf(const char* fmt, va_list args);

        // Log functions
        static void vlog(const char* prefix, const char* fmt, va_list args);
        static void log(const char* prefix, const char* fmt, ...);
        static void log_etc(const char* prefix, const char* fn,const char* file, s64 line, const char* fmt, ...);
    };
}

#define printSL(fmt, ...) \
    sion64::kernel_output::log_etc(_YELLOW_COLOR_PASER("[~] "), __func__, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define printSE(fmt, ...) \
    sion64::kernel_output::log_etc(_RED_COLOR_PASER("[!] "), __func__, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define printSI(fmt, ...) \
    sion64::kernel_output::log_etc(_GREEN_COLOR_PASER("[*] "), __func__, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
