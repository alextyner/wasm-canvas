#ifndef WINDOW_H
#define WINDOW_H

#include <emscripten.h>
#include <stdlib.h>

struct WindowStruct;

typedef struct WindowStruct
{
    int (*getInnerHeight)();
    int (*getInnerWidth)();
    int (*getOuterHeight)();
    int (*getOuterWidth)();
    void (*blur)();
} HTMLWindow;

HTMLWindow *Window();

void freeWindow(HTMLWindow *window);

#endif