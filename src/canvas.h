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
    /* TextMetrics *(*measureText)(struct ContextStruct *this, char *text); */ // that's a whole can of worms
    void (*setLineWidth)(struct ContextStruct *this, double value);
    double (*getLineWidth)(struct ContextStruct *this);
    void (*setLineCap)(struct ContextStruct *this, char *type);
    // 0 - BUTT, 1 - ROUND, 2 - SQUARE
    int (*getLineCap)(struct ContextStruct *this);

} CanvasRenderingContext2D;

typedef struct CanvasStruct
{
    struct ContextStruct *ctx;
    char *id; // dynamically allocated
    int (*getHeight)(struct CanvasStruct *this);
    int (*getWidth)(struct CanvasStruct *this);
    void (*setHeight)(struct CanvasStruct *this, int height);
    void (*setWidth)(struct CanvasStruct *this, int width);
    // only CanvasRenderingContext2D (labelled '2d') is currently supported
    struct ContextStruct *(*getContext)(struct CanvasStruct *this, char *contextType);

} HTMLCanvasElement;

HTMLCanvasElement *createCanvas(char *name);

void freeCanvas(HTMLCanvasElement *canvas);

#endif