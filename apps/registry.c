#include "registry.h"
#include "calc/calc.h"

/* Register apps here (order = display order) */
static const App APPS[] = {
    {"Calculator", &calc_run},
};

const App *get_apps(int *count) {
    if (count) *count = (int) (sizeof(APPS) / sizeof(APPS[0]));
    return APPS;
}
