/**
 * @file window.c
 * @author Alex Tyner
 * Interfaces with the window in which the program is running, 
 * typically exposed to JavaScript code.
 */

#include "window.h"

static HTMLWindow *current;

// -- HTMLWindow static methods

static int window_getInnerHeight()
{
    return EM_ASM_INT({
        return window.innerHeight;
    });
}
static int window_getInnerWidth()
{
    return EM_ASM_INT({
        return window.innerWidth;
    });
}
static int window_getOuterHeight()
{
    return EM_ASM_INT({
        return window.outerHeight;
    });
}
static int window_getOuterWidth()
{
    return EM_ASM_INT({
        return window.outerWidth;
    });
}
static void window_blur()
{
    EM_ASM({
        window.blur();
    });
}

// -- end HTMLWindow static methods

/**
 * Retrieves the current HTML Window.
 * Behaves like a singleton -- that is, an HTMLWindow is defined with static linkage and only HTMLWindow one should ever be allocated.
 * Don't forget to call freeWindow() when you're done with the Window. (ex: freeWindow(Window());)
 */
HTMLWindow *Window()
{
    if (!current) // field not yet populated
    {
        current = (HTMLWindow *)malloc(sizeof(HTMLWindow));
        current->getInnerHeight = window_getInnerHeight;
        current->getInnerWidth = window_getInnerWidth;
        current->getOuterHeight = window_getOuterHeight;
        current->getOuterWidth = window_getOuterWidth;
        current->blur = window_blur;
    }
    return current;
}

void freeWindow(HTMLWindow *window)
{
    free(window);
}