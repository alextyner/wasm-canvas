#ifndef CANVAS_H
#define CANVAS_H

#include <emscripten.h>

struct ContextStruct;
struct CanvasStruct;

typedef struct ContextStruct
{
    struct CanvasStruct *canvas;
    char contextType[19];
    void (*clearRect)(struct ContextStruct *this, int x, int y, int width, int height);
    void (*fillRect)(struct ContextStruct *this, int x, int y, int width, int height);
    void (*strokeRect)(struct ContextStruct *this, int x, int y, int width, int height);
    // maxWidth = -1 to ignore
    void (*fillText)(struct ContextStruct *this, char *text, int x, int y, int maxWidth);
    // maxWidth = -1 to ignore
    void (*strokeText)(struct ContextStruct *this, char *text, int x, int y, int maxWidth);
    /* TextMetrics *(*measureText)(char *text); */
    void (*setLineWidth)(struct ContextStruct *this, double value);
    double (*getLineWidth)(struct ContextStruct *this);
    void (*setLineCap)(struct ContextStruct *this, char *type);
    char *(*getLineCap)(struct ContextStruct *this);
    
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