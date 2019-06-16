#ifndef WINDOW_H
#define WINDOW_H

#include <emscripten.h>
#include <stdlib.h>

typedef struct WindowStruct HTMLWindow;

struct WindowStruct
{
    int (*getInnerHeight)();
    int (*getInnerWidth)();
    int (*getOuterHeight)();
    int (*getOuterWidth)();
    void (*blur)();
};

HTMLWindow *Window();

void freeWindow(HTMLWindow *window);

#endif