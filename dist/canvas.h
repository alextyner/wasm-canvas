#ifndef CANVAS_H
#define CANVAS_H

#include <stdlib.h>
#include <string.h>
#include <emscripten.h>

typedef struct CanvasStruct HTMLCanvasElement;
typedef struct ContextStruct CanvasRenderingContext2D;

struct ContextStruct
{
    struct
    {
        struct CanvasStruct *canvas;
        char contextType[19];
        char *font;
        char *textAlign;
        char *fillStyle;
        char *strokeStyle;
        char *lineCap;
        char *lineJoin;
        char *globalCompositeOperation;
    } private;
    void (*clearRect)(CanvasRenderingContext2D *this, double x, double y, double width, double height);
    void (*fillRect)(CanvasRenderingContext2D *this, double x, double y, double width, double height);
    void (*strokeRect)(CanvasRenderingContext2D *this, double x, double y, double width, double height);
    // maxWidth < 0.0 to ignore parameter
    void (*fillText)(CanvasRenderingContext2D *this, char *text, double x, double y, double maxWidth);
    // maxWidth < 0.0 to ignore parameter
    void (*strokeText)(CanvasRenderingContext2D *this, char *text, double x, double y, double maxWidth);
    /* TextMetrics *(*measureText)(CanvasRenderingContext2D *this, char *text); */ // that's a whole can of worms
    void (*setLineWidth)(CanvasRenderingContext2D *this, double value);
    double (*getLineWidth)(CanvasRenderingContext2D *this);
    void (*setLineCap)(CanvasRenderingContext2D *this, char *type);
    char *(*getLineCap)(CanvasRenderingContext2D *this);
    void (*setLineJoin)(CanvasRenderingContext2D *this, char *type);
    char *(*getLineJoin)(CanvasRenderingContext2D *this);
    char *(*getFont)(CanvasRenderingContext2D *this);
    void (*setFont)(CanvasRenderingContext2D *this, char *value);
    void (*setTextAlign)(CanvasRenderingContext2D *this, char *value);
    char *(*getTextAlign)(CanvasRenderingContext2D *this);
    void (*setFillStyle)(CanvasRenderingContext2D *this, char *value);
    char *(*getFillStyle)(CanvasRenderingContext2D *this);
    void (*setStrokeStyle)(CanvasRenderingContext2D *this, char *value);
    char *(*getStrokeStyle)(CanvasRenderingContext2D *this);
    void (*beginPath)(CanvasRenderingContext2D *this);
    void (*closePath)(CanvasRenderingContext2D *this);
    void (*moveTo)(CanvasRenderingContext2D *this, double x, double y);
    void (*lineTo)(CanvasRenderingContext2D *this, double x, double y);
    void (*bezierCurveTo)(CanvasRenderingContext2D *this, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
    void (*quadraticCurveTo)(CanvasRenderingContext2D *this, double cpx, double cpy, double x, double y);
    void (*arc)(CanvasRenderingContext2D *this, double x, double y, double radius, double startAngle, double endAngle);
    void (*arcTo)(CanvasRenderingContext2D *this, double x1, double y1, double x2, double y2, double radius);
    void (*ellipse)(CanvasRenderingContext2D *this, double x, double y, double radiusX, double radiusY, double rotation, double startAngle, double endAngle);
    void (*rect)(CanvasRenderingContext2D *this, double x, double y, double width, double height);
    void (*fill)(CanvasRenderingContext2D *this);
    void (*stroke)(CanvasRenderingContext2D *this);
    void (*clip)(CanvasRenderingContext2D *this);
    int (*isPointInPath)(CanvasRenderingContext2D *this, double x, double y);
    int (*isPointInStroke)(CanvasRenderingContext2D *this, double x, double y);
    void (*rotate)(CanvasRenderingContext2D *this, double angle);
    void (*scale)(CanvasRenderingContext2D *this, double x, double y);
    void (*translate)(CanvasRenderingContext2D *this, double x, double y);
    void (*transform)(CanvasRenderingContext2D *this, double a, double b, double c, double d, double e, double f);
    void (*setTransform)(CanvasRenderingContext2D *this, double a, double b, double c, double d, double e, double f);
    void (*resetTransform)(CanvasRenderingContext2D *this);
    void (*setGlobalAlpha)(CanvasRenderingContext2D *this, double value);
    double (*getGlobalAlpha)(CanvasRenderingContext2D *this);
    void (*setGlobalCompositeOperation)(CanvasRenderingContext2D *this, char *value);
    char *(*getGlobalCompositeOperation)(CanvasRenderingContext2D *this);
    void (*save)(CanvasRenderingContext2D *this);
    void (*restore)(CanvasRenderingContext2D *this);
    HTMLCanvasElement *(*getCanvas)(CanvasRenderingContext2D *this);
};

struct CanvasStruct
{
    struct
    {
        struct ContextStruct *ctx;
        char *id; // dynamically allocated
    } private;
    int (*getHeight)(HTMLCanvasElement *this);
    int (*getWidth)(HTMLCanvasElement *this);
    void (*setHeight)(HTMLCanvasElement *this, int height);
    void (*setWidth)(HTMLCanvasElement *this, int width);
    // only CanvasRenderingContext2D (labelled '2d') is currently supported
    // behaves like a singleton
    CanvasRenderingContext2D *(*getContext)(HTMLCanvasElement *this, char *contextType);
};

HTMLCanvasElement *createCanvas(char *name);

void freeCanvas(HTMLCanvasElement *canvas);

#endif