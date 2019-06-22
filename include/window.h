/**
 * Interfaces with the browser window in which the program is running, 
 * typically exposed to JavaScript code.
 * @brief HTMLWindow (Window) C-DOM-JS-interaction
 * @file window.h
 * @author Alex Tyner
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <emscripten.h>
#include <stdlib.h>

typedef struct HTMLWindow HTMLWindow;

/** The active HTMLWindow. This field facilitates the Singleton design pattern. */
static HTMLWindow *current;

/**
 * Struct containing state and OO-like behavior similar to that of the globally available
 * 'window' DOM object in JavaScript. Functions do not require a first parameter identifying
 * the HTMLWindow itself because it is assumed that this code is executing in only a single
 * window, and we'll just use that one.
 * 
 * This struct should not be instantiated, but rather created and accessed (as a Singleton)
 * via the Window() function.
 * 
 * I find this struct most useful in conjunction with the canvas for expanding the canvas
 * dimensions to be as large as the entire window.
 * 
 * For example:
 * 
 *     HTMLCanvasElement *canvas = createCanvas("bigCanvas"); // not big yet
 *     canvas->setHeight(canvas, Window()->getInnerHeight());
 *     canvas->setWidth(canvas, Window()->getInnerWidth());
 *     freeCanvas(canvas);
 *     freeWindow(Window());
 */
struct HTMLWindow
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
 * If you've called this function to get the HTMLWindow at any point in your
 * program, don't forget to call freeWindow() when you're done with it.
 * For example:
 * freeWindow(Window());
 */
HTMLWindow *Window();

void freeWindow(HTMLWindow *window);

#endif