#include "calc.h"
#include "parser.h"
#include "../../drivers/console.h"
#include "../../lib/input.h"

#define LINE_MAX 128

void calc_run(void) {
    console_write("Simple Calculator: type expressions like 12+34 or 100 / 5\n");
    console_write("Supported ops: + - * /\n\n");

    char line[LINE_MAX];
    for (;;) {
        int n = input_read_line(line, LINE_MAX, "Calc> ");
        if (n <= 0) continue;
        if ((n == 4) && (line[0] == 'e' || line[0] == 'E') && (line[1] == 'x' || line[1] == 'X') &&
            (line[2] == 'i' || line[2] == 'I') && (line[3] == 't' || line[3] == 'T')) {
            console_write("Halting.\n");
            break; /* caller may halt */
        }
        int res = 0;
        if (eval_expr(line, &res)) {
            console_write("= ");
            console_write_dec(res);
            console_putc('\n');
        } else {
            console_write("Error: enter one expression like 12+34 (no parentheses). Division is integer.\n");
        }
    }
}
