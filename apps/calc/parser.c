#include <stdbool.h>
#include "parser.h"
#include "../../lib/util.h"

static bool parse_int(const char *s, int *i, int *out) {
    int sign = 1, val = 0, idx = *i;
    while (is_space(s[idx])) idx++;
    if (s[idx] == '+') { idx++; } else if (s[idx] == '-') {
        sign = -1;
        idx++;
    }
    if (!is_digit(s[idx])) return false;
    while (is_digit(s[idx])) {
        val = val * 10 + (s[idx] - '0');
        idx++;
    }
    *out = sign * val;
    *i = idx;
    return true;
}

bool eval_expr(const char *s, int *result) {
    int i = 0, a = 0, b = 0;
    while (is_space(s[i])) i++;
    if (!parse_int(s, &i, &a)) return false;
    while (is_space(s[i])) i++;
    char op = s[i++];
    while (is_space(s[i])) i++;
    if (!(op == '+' || op == '-' || op == '*' || op == '/')) return false;
    if (!parse_int(s, &i, &b)) return false;
    while (is_space(s[i])) i++;
    if (s[i] != '\0') return false;

    if (op == '+') *result = a + b;
    else if (op == '-') *result = a - b;
    else if (op == '*') *result = a * b;
    else {
        if (b == 0) return false;
        *result = a / b;
    }
    return true;
}
