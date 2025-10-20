#pragma once

typedef struct {
    const char *name;

    void (*run)(void);
} App;
