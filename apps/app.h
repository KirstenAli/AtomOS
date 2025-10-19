#ifndef APP_H
#define APP_H

typedef struct {
    const char *name;

    void (*run)(void);
} App;

#endif
