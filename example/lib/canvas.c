/**
 * @file canvas.c
 * @author Alex Tyner
 * Facilitates interaction with HTML5 Canvas elements in a similar
 * manner to JavaScript, but from C compiled with Emscripten.
 */

#include <stdlib.h>
#include <string.h>
#include "canvas.h"
static Context *createContext(Canvas* canvas, char *contextType);

static int canvas_getWidth(Canvas *this)
{
    return EM_ASM_INT({
        return document.getElementById(UTF8ToString($0)).width;
    }, this->id);
}
static int canvas_getHeight(Canvas *this)
{
    return EM_ASM_INT({
        return document.getElementById(UTF8ToString($0)).height;
    }, this->id);
}
static void canvas_setWidth(Canvas *this, int width) {
    EM_ASM({
        document.getElementById(UTF8ToString($0)).width = $1;
    }, this->id, width);
}
static void canvas_setHeight(Canvas *this, int height) {
    EM_ASM({
        document.getElementById(UTF8ToString($0)).height = $1;
    }, this->id, height);
}
static Context *canvas_getContext(Canvas *this, char *contextType) {
    if (this->ctx == NULL) { // field hasn't been populated yet
        this->ctx = createContext(this, contextType);
        return this->ctx;
    } else {
        return this->ctx;
    }
}

Canvas *createCanvas(char *id)
{
    EM_ASM(
        {
            document.body.appendChild(document.createElement("canvas")).setAttribute("id", UTF8ToString($0));
        },
        id);
    Canvas *c = (Canvas *)malloc(sizeof(Canvas));

    c->id = (char *) malloc(strlen(id) + 1);
    strcpy(c->id, id);

    c->getWidth = canvas_getWidth;
    c->getHeight = canvas_getHeight;
    c->setHeight = canvas_setHeight;
    c->setWidth = canvas_setWidth;

    c->getContext = canvas_getContext;

    return c;
}

static Context *createContext(Canvas* canvas, char *contextType) {
    Context *ctx = (Context *) malloc(sizeof(Context));
    ctx->canvas = canvas;

    return ctx;
}

void freeCanvas(Canvas *canvas)
{
    free(canvas->id);
    free(canvas->ctx);
    free(canvas);
}