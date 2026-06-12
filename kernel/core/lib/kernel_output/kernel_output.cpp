#include "core/include/kernel_output/kernel_output.hpp"

using namespace sion64;

void kernel_output::putC(char c) {
    *UART_ADDR = c;
}

void kernel_output::putS(const char* str) {
    while (*str) putC(*str++);
}

void kernel_output::putD(s64 num) {
    char buffer[INT64_MAX_DIGITS];
    int idx = 0;
    u64 abs_num;

    if (num == 0) {
        putC('0');
        return;
    }

    if (num < 0) {
        putC('-');
        abs_num = (u64)(-(num + 1)) + 1;
    } else {
        abs_num = (u64)num;
    }

    while (abs_num > 0) {
        buffer[idx++] = (abs_num % 10) + '0';
        abs_num /= 10;
    }

    while (idx--) putC(buffer[idx]);
}

void kernel_output::putX(u64 num) {
    static constexpr char hex_digits[] = "0123456789abcdef";
    char buffer[16];
    int idx = 0;

    if (num == 0) {
        putC('0');
        return;
    }

    while (num > 0) {
        buffer[idx++] = hex_digits[num % 16];
        num /= 16;
    }

    while (idx--) putC(buffer[idx]);
}

int kernel_output::str_len(const char* str) {
    int n = 0;
    while (str[n]) n++;
    return n;
}

int kernel_output::num_len(u64 value) {
    if (value == 0) return 1;
    int len = 0;
    while (value > 0) { len++; value /= 10; }
    return len;
}

int kernel_output::hex_len(u64 value) {
    if (value == 0) return 1;
    int len = 0;
    while (value > 0) { len++; value /= 16; }
    return len;
}

void kernel_output::put_pad(int width, int len) {
    while (len++ < width) putC(' ');
}

void kernel_output::vprintf(const char* fmt, va_list args) {
    while (*fmt) {
        if (*fmt != '%') {
            putC(*fmt++);
            continue;
        }

        fmt++; // skip '%'
        if (*fmt == '\0') { putC('%'); break; }

        bool left_align = false;
        if (*fmt == '-') { left_align = true; fmt++; }

        int width = 0;
        while (*fmt >= '0' && *fmt <= '9')
            width = width * 10 + (*fmt++ - '0');

        switch (*fmt) {
            case 'd': {
                u64 val = va_arg(args, u64);
                int len = num_len(val) + ((s64)val < 0 ? 1 : 0);
                if (!left_align) put_pad(width, len);
                putD((s64)val);
                if (left_align) put_pad(width, len);
                break;
            }
            case 'x': {
                u64 val = va_arg(args, u64);
                int len = hex_len(val);
                if (!left_align) put_pad(width, len);
                putX(val);
                if (left_align) put_pad(width, len);
                break;
            }
            case 's': {
                char* str = va_arg(args, char*);
                if (!str) { putS("(null)"); break; }
                int len = str_len(str);
                if (!left_align) put_pad(width, len);
                putS(str);
                if (left_align) put_pad(width, len);
                break;
            }
            case 'c': {
                char ch = (char)va_arg(args, int);
                if (!left_align) put_pad(width, 1);
                putC(ch);
                if (left_align) put_pad(width, 1);
                break;
            }
            case '%':
                putC('%');
                break;
            default:
                putC('%'); putC(*fmt);
                break;
        }
        fmt++;
    }
}

void kernel_output::vlog(const char* prefix, const char* fmt, va_list args) {
    putS(prefix);
    vprintf(fmt, args);
    putC('\n');
}

void kernel_output::log(const char* prefix, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vlog(prefix, fmt, args);
    va_end(args);
}

void kernel_output::log_etc(const char* prefix, const char* fn,const char* file, s64 line, const char* fmt, ...) {
    putS(__MAGENTA); putC('[');
    putS(file); putC(':');
    putD(line); putC(']');
    putS(__END); putS(__BLUE); putC('[');
    putS(fn); putC(']'); putS(__END);

    va_list args;
    va_start(args, fmt);
    vlog(prefix, fmt, args);
    va_end(args);
}
