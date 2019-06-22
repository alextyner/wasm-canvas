/**
 * Facilitates interaction with HTML5 Canvas elements in a similar
 * manner to JavaScript via the DOM, but from C to be compiled with Emscripten.
 * @brief HTMLCanvasElement and CanvasRenderingContext2D C-DOM-JS-interaction
 * @file canvas.h
 * @author Alex Tyner
 */
#ifndef CANVAS_H
#define CANVAS_H

#include <emscripten.h>
#include <string.h>
#include <stdlib.h>

typedef struct HTMLCanvasElement HTMLCanvasElement;
typedef struct CanvasRenderingContext2D CanvasRenderingContext2D;

/**
 * Struct containing state and OO-like behavior of a CanvasRenderingContext2D structured similarly
 * to how it would be exposed in JavaScript. This struct should not be instantiated, but rather 
 * obtained from an HTMLCanvas struct by calling its getContext() function pointer.
 * 
 * Function pointers in this struct can be called in an almost identical manner to their JavaScript
 * equivalents, with a few idiomatic-C quirks. Firstly, every function takes as its first parameter
 * a pointer to the struct itself. It's hard to access the struct's state within the function otherwise
 * since we are just simulating OO. Secondly, some function parameters differ slightly from the JS
 * implementations because we don't have overloading in C. For example, the fillText() function
 * always expects the optional 'maxWidth' property. That parameter will be ignored if you provide a
 * negative value, and there are comments written below with that and similar information.
 * 
 * You might notice that a lot of functions expect double parameters. That's because most of the
 * equivalent JavaScript functions will accept doubles. Don't worry, providing int parameters will
 * work just fine. (int) -> (double) is an implicit conversion in C; no cast required.
 * 
 * To summarize, a typical use of this struct might look like the following:
 * 
 *     HTMLCanvas *canvas = createCanvas("myCanvas");
 *     CanvasRenderingContext2D *ctx = canvas->getContext(canvas, "2d"); // only 2d is supported currently
 *     ctx->setFillStyle(ctx, "#FF0000");
 *     printf("I set the fill style to %s\n", ctx->getFillStyle(ctx));
 *     ctx->fillRect(ctx, 50, 75, 100, 200);
 *     freeCanvas(canvas);
 * 
 * Some state is pseudo-encapsulated in the 'private' member struct, such as pointers to dynamically
 * allocated strings that will need to be freed when the HTMLCanvas is freed. Typically these
 * are from JavaScript calls, allocated to return them to the user. Alternatively, functions
 * with canonical string return types could be pigeon-holed into returning enum types, or
 * we could make the user responsible for buffer allocation and expect an additional by-reference
 * parameter to copy the string into. The in-JavaScript allocated string would need to be
 * freed after returning its contents to the user, and the user would not know how large the buffer
 * should be. So, when a string is exposed to the user, this struct keeps track of the pointers in
 * order to free them when the HTMLCanvas parent struct is freed.
 */
struct CanvasRenderingContext2D
{
    /**
     * This anonymous struct encapsulates fields of the CanvasRenderingContext2D struct
     * intended to be private. These are primarily pointers to memory allocated from
     * JavaScript calls so that they can be freed when the canvas is no longer in use.
     */
    struct
    {
        HTMLCanvasElement *canvas;
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
    /** @param maxWidth optional parameter. provide a value < 0.0 to ignore this parameter. */
    void (*fillText)(CanvasRenderingContext2D *this, char *text, double x, double y, double maxWidth);
    /** @param maxWidth optional parameter. provide a value < 0.0 to ignore this parameter. */
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

/**
 * Struct containing state and OO-like behavior of an HTML canvas structured similarly
 * to how it would be exposed in JavaScript. This struct should be instantiated using
 * the createCanvas() function, and, when you're done using it, should be freed using the
 * freeCanvas() function.
 * 
 * After freeing the canvas struct, the DOM element will still be present and active in
 * HTML. In the future, it may be possible to reacquire the same canvas as a struct by calling
 * createCanvas() with the same element id.
 * 
 * The real meat of this struct comes with the getContext() function pointer, which creates
 * a canvas rendering context with drawing capabilities.
 * 
 * A typical use of this struct might look like the following:
 * 
 *     HTMLCanvas *canvas = createCanvas("myCanvas");
 *     canvas->setHeight(canvas, 1080);
 *     canvas->setWidth(canvas, 1920);
 *     CanvasRenderingContext2D *ctx = canvas->getContext(canvas, "2d"); // only 2d is supported currently
 *     ctx->fillRect(ctx, 50, 75, 100, 200);
 *     freeCanvas(canvas);
 */
struct HTMLCanvasElement
{
    struct
    {
        CanvasRenderingContext2D *ctx;
        char *id;
    } private;
    /** 
     * Returns a positive integer reflecting the height HTML attribute of the <canvas> element
     * interpreted in CSS pixels. The canvas height defaults to 150. 
     */
    int (*getHeight)(HTMLCanvasElement *this);
    /** 
     * Returns a positive integer reflecting the width HTML attribute of the <canvas> element
     * interpreted in CSS pirxels. The canvas width defaults to 300. 
     */
    int (*getWidth)(HTMLCanvasElement *this);
    /**
     * Sets the height HTML attribute of the <canvas> element. If an invalid value is specified,
     * the default value of 150 is used. 
     */
    void (*setHeight)(HTMLCanvasElement *this, int height);
    /**
     * Sets the width HTML attribute of the <canvas> element. If an invalid value is specified,
     * the default value of 300 is used. 
     */
    void (*setWidth)(HTMLCanvasElement *this, int width);
    /** 
     * Returns a drawing context for the canvas, or null if the context type is not supported.
     * Use type "2d" (only this type is currently supported) to retrieve a CanvasRenderingContext2D.
     * 
     * The field retrieved by this getter function behaves like a singleton. 
     */
    CanvasRenderingContext2D *(*getContext)(HTMLCanvasElement *this, char *contextType);
};

/**
 * Creates a struct containing state and OO-like behavior of an HTML canvas structured
 * similarly to how it would be exposed in JavaScript. This struct should be instantiated using
 * the createCanvas() function, and, when you're done using it, should be freed using the
 * freeCanvas() function.
 * 
 * After freeing the canvas struct, the DOM element will still be present and active in
 * HTML. It is possible to acquire an existing HTML canvas or reacquire a previously freed
 * canvas by calling createCanvas() with its matching element id.
 * 
 * A typical use of this function might look like the following:
 * 
 *     HTMLCanvas *canvas = createCanvas("myCanvas");
 *     canvas->setHeight(canvas, 1080);
 *     canvas->setWidth(canvas, 1920);
 *     CanvasRenderingContext2D *ctx = canvas->getContext(canvas, "2d"); // only 2d is supported currently
 *     ctx->fillRect(ctx, 50, 75, 100, 200);
 *     freeCanvas(canvas);
 *     // I've decided I want that canvas again
 *     HTMLCanvas *sameOldCanvas = createCanvas("myCanvas");
 *     int width = sameOldCanvas->getWidth(sameOldCanvas);
 *     freeCanvas(sameOldCanvas);
 */
HTMLCanvasElement *createCanvas(char *name);

/**
 * Frees the dynamically allocated HTMLCanvasElement and any dynamically allocated
 * state as necessary. The DOM canvas element will still exist in HTML after freeing
 * the struct.
 */
void freeCanvas(HTMLCanvasElement *canvas);

#endif