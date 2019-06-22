/**
 * Interfaces with the browser window in which the program is running, 
 * typically exposed to JavaScript code.
 * @file window.c
 * @author Alex Tyner
 */

#include "window.h"

/* Begin: HTMLWindow static methods */
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
/* End: HTMLWindow static methods */

HTMLWindow *Window()
{
    if (!current)
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