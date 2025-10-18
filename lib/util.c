#include "util.h"

void itoa_dec(int value, char *buf, size_t buflen) {
    if (buflen == 0) return;
    size_t i = 0;
    if (value == 0) {
        if (buflen > 1) { buf[i++] = '0'; }
        buf[i] = 0;
        return;
    }
    int v = value;
    int neg = v < 0;
    if (neg) v = -v;
    char tmp[16];
    int t = 0;
    while (v && t < (int) sizeof(tmp)) {
        tmp[t++] = (char) ('0' + (v % 10));
        v /= 10;
    }
    if (neg && i < buflen - 1) buf[i++] = '-';
    while (t && i < buflen - 1) buf[i++] = tmp[--t];
    buf[i] = 0;
}

int is_space(char c) { return c == ' ' || c == '\t' || c == '\r'; }
int is_digit(char c) { return c >= '0' && c <= '9'; }
