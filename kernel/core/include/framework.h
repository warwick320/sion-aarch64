#pragma once
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef long long s64;

typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)

#define UART_BASE 0x10000000
#define UART_ADDR ((volatile u8*)UART_BASE) // 1바이트인 이유 -> UART가 한글자씩 처리해서

#define MTIMECMP_BASE 0x02004000
#define MTIMECMP_ADDR ((volatile u64*)MTIMECMP_BASE)

#define MTIME_BASE 0x0200BFF8
#define MTIME_ADDR ((volatile u64*)MTIME_BASE)

#define INTERRUPT_REASON_TIMER 0x8000000000000007ULL

#define INT64_MAX_DIGITS 20 
// Reset
#define __END             "\033[0m"

// Text Style
#define __BOLD            "\033[1m"
#define __DIM             "\033[2m"
#define __ITALIC          "\033[3m"
#define __UNDERLINE       "\033[4m"
#define __BLINK           "\033[5m"
#define __REVERSE         "\033[7m"
#define __HIDDEN          "\033[8m"
#define __STRIKE          "\033[9m"

// Style Off
#define __NO_BOLD         "\033[22m"
#define __NO_ITALIC       "\033[23m"
#define __NO_UNDERLINE    "\033[24m"
#define __NO_BLINK        "\033[25m"
#define __NO_REVERSE      "\033[27m"
#define __NO_HIDDEN       "\033[28m"
#define __NO_STRIKE       "\033[29m"

// Foreground (Normal)
#define __BLACK           "\033[30m"
#define __RED             "\033[31m"
#define __GREEN           "\033[32m"
#define __YELLOW          "\033[33m"
#define __BLUE            "\033[34m"
#define __MAGENTA         "\033[35m"
#define __CYAN            "\033[36m"
#define __WHITE           "\033[37m"
#define __DEFAULT_FG      "\033[39m"

// Foreground (Bright)
#define __BRIGHT_BLACK    "\033[90m"
#define __BRIGHT_RED      "\033[91m"
#define __BRIGHT_GREEN    "\033[92m"
#define __BRIGHT_YELLOW   "\033[93m"
#define __BRIGHT_BLUE     "\033[94m"
#define __BRIGHT_MAGENTA  "\033[95m"
#define __BRIGHT_CYAN     "\033[96m"
#define __BRIGHT_WHITE    "\033[97m"

// Alias
#define __GRAY            __BRIGHT_BLACK

// Background (Normal)
#define __BG_BLACK        "\033[40m"
#define __BG_RED          "\033[41m"
#define __BG_GREEN        "\033[42m"
#define __BG_YELLOW       "\033[43m"
#define __BG_BLUE         "\033[44m"
#define __BG_MAGENTA      "\033[45m"
#define __BG_CYAN         "\033[46m"
#define __BG_WHITE        "\033[47m"
#define __DEFAULT_BG      "\033[49m"

// Background (Bright)
#define __BG_BRIGHT_BLACK   "\033[100m"
#define __BG_BRIGHT_RED     "\033[101m"
#define __BG_BRIGHT_GREEN   "\033[102m"
#define __BG_BRIGHT_YELLOW  "\033[103m"
#define __BG_BRIGHT_BLUE    "\033[104m"
#define __BG_BRIGHT_MAGENTA "\033[105m"
#define __BG_BRIGHT_CYAN    "\033[106m"
#define __BG_BRIGHT_WHITE   "\033[107m"

#define _RED_COLOR_PASER(str) __RED str __END
#define _GREEN_COLOR_PASER(str) __GREEN str __END
#define _YELLOW_COLOR_PASER(str) __YELLOW str __END


#define S64_VER_BUILD "107"
#define S64_VER "0.0.0"
