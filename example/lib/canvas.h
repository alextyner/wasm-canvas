#ifndef CANVAS_H
#define CANVAS_H

#include <emscripten.h>

struct ContextStruct;
struct CanvasStruct;

typedef struct ContextStruct
{
    struct CanvasStruct *canvas;
} Context;

typedef struct CanvasStruct
{
    struct ContextStruct *ctx;
    char *id; // dynamically allocated
    int (*getHeight)(struct CanvasStruct *this);
    int (*getWidth)(struct CanvasStruct *this);
    void (*setHeight)(struct CanvasStruct *this, int height);
    void (*setWidth)(struct CanvasStruct *this, int width);
    struct ContextStruct *(*getContext)(struct CanvasStruct *this, char *contextType);

} Canvas;

Canvas *createCanvas(char *name);

void freeCanvas(Canvas *canvas);

#endif