#pragma once
#include "app.h"

/* Returns a pointer to a static array of registered apps and its count. */
const App *get_apps(int *count);
