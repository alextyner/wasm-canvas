#ifndef WINDOW_H
#define WINDOW_H

#include <emscripten.h>
#include <stdlib.h>

typedef struct WindowStruct HTMLWindow;

/** The active HTMLWindow. Field facilitates the Singleton design pattern. */
static HTMLWindow *current;

struct WindowStruct
{
    int (*getInnerHeight)();
    int (*getInnerWidth)();
    int (*getOuterHeight)();
    int (*getOuterWidth)();
    void (*blur)();
};

/**
 * Retrieves the current HTML Window.
 * Behaves like a singleton -- that is, an HTMLWindow is defined with static
 * linkage and only one HTMLWindow should ever be allocated.
 * 
 * Don't forget to call freeWindow() when you're done with the Window.
 * (ex: freeWindow(Window());)
 */
HTMLWindow *Window();

void freeWindow(HTMLWindow *window);

#endif