/**
 * @file canvas.c
 * @author Alex Tyner
 * Facilitates interaction with HTML5 Canvas elements in a similar
 * manner to JavaScript, but from C compiled with Emscripten.
 */

#include <stdlib.h>
#include <string.h>
#include "canvas.h"

static CanvasRenderingContext2D *createContext(HTMLCanvasElement *canvas, char *contextType);

// -- HTMLCanvasElement static methods

static int canvas_getWidth(HTMLCanvasElement *this)
{
    return EM_ASM_INT({
        return document.getElementById(UTF8ToString($0)).width;
    },
                      this->id);
}
static int canvas_getHeight(HTMLCanvasElement *this)
{
    return EM_ASM_INT({
        return document.getElementById(UTF8ToString($0)).height;
    },
                      this->id);
}
static void canvas_setWidth(HTMLCanvasElement *this, int width)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).width = $1;
    },
           this->id, width);
}
static void canvas_setHeight(HTMLCanvasElement *this, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).height = $1;
    },
           this->id, height);
}
static CanvasRenderingContext2D *canvas_getContext(HTMLCanvasElement *this, char *contextType)
{
    if (this->ctx == NULL)
    { // field hasn't been populated yet (so perform the lazy-load operation)
        this->ctx = createContext(this, contextType);
        return this->ctx;
    }
    else
    {
        return this->ctx;
    }
}

// -- end HTMLCanvasElement static methods

HTMLCanvasElement *createCanvas(char *id)
{
    EM_ASM(
        {
            document.body.appendChild(document.createElement("canvas")).setAttribute("id", UTF8ToString($0));
        },
        id);
    HTMLCanvasElement *c = (HTMLCanvasElement *)malloc(sizeof(HTMLCanvasElement));

    c->id = (char *)malloc(strlen(id) + 1);
    strcpy(c->id, id);
    c->ctx = NULL; // we'll lazy-load the context when it's asked for
    c->getWidth = canvas_getWidth;
    c->getHeight = canvas_getHeight;
    c->setHeight = canvas_setHeight;
    c->setWidth = canvas_setWidth;
    c->getContext = canvas_getContext;

    return c;
}

// -- CanvasRenderingContext2D static methods

static void context2d_clearRect(CanvasRenderingContext2D *this, int x, int y, int width, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').clearRect($1, $2, $3, $4);
    },
           this->canvas->id, x, y, width, height);
}
static void context2d_fillRect(CanvasRenderingContext2D *this, int x, int y, int width, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').fillRect($1, $2, $3, $4);
    },
           this->canvas->id, x, y, width, height);
}
static void context2d_strokeRect(CanvasRenderingContext2D *this, int x, int y, int width, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').strokeRect($1, $2, $3, $4);
    },
           this->canvas->id, x, y, width, height);
}
static void context2d_fillText(CanvasRenderingContext2D *this, char *text, int x, int y, int maxWidth)
{
    if (maxWidth == -1)
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').fillText(UTF8ToString($1), $2, $3);
        },
               this->canvas->id, text, x, y);
    }
    else
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').fillText(UTF8ToString($1), $2, $3, $4);
        },
               this->canvas->id, text, x, y, maxWidth);
    }
}
static void context2d_strokeText(CanvasRenderingContext2D *this, char *text, int x, int y, int maxWidth)
{
    if (maxWidth == -1)
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').strokeText(UTF8ToString($1), $2, $3);
        },
               this->canvas->id, text, x, y);
    }
    else
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').strokeText(UTF8ToString($1), $2, $3, $4);
        },
               this->canvas->id, text, x, y, maxWidth);
    }
}
static void context2d_setLineWidth(CanvasRenderingContext2D *this, double value)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').lineWidth = ($1);
    },
           this->canvas->id, value);
}
static double context2d_getLineWidth(CanvasRenderingContext2D *this)
{
    return EM_ASM_DOUBLE({
        return document.getElementById(UTF8ToString($0)).getContext('2d').lineWidth;
    },
                         this->canvas->id);
}
static void context2d_setLineCap(CanvasRenderingContext2D *this, char *type)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').lineCap = UTF8ToString($1);
    },
           this->canvas->id, type);
}
static int context2d_getLineCap(CanvasRenderingContext2D *this)
{
    return EM_ASM_INT({
        var lineCapType = document.getElementById(UTF8ToString($0)).getContext('2d').lineCap;
        if (lineCapType == 'butt')
            return 0;
        else if (lineCapType == 'round')
            return 1;
        else // 'square'
            return 2;
    },
                      this->canvas->id);
}
static void context2d_setLineJoin(CanvasRenderingContext2D *this, char *type)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').lineJoin = UTF8ToString($1);
    },
           this->canvas->id, type);
}
static int context2d_getLineJoin(CanvasRenderingContext2D *this)
{
    return EM_ASM_INT({
        var lineJoinType = document.getElementById(UTF8ToString($0)).getContext('2d').lineJoin;
        if (lineJoinType == 'round')
            return 0;
        else if (lineJoinType == 'bevel')
            return 1;
        else // 'miter'
            return 2;
    },
                      this->canvas->id);
}
static char *context2d_getFont(CanvasRenderingContext2D *this)
{
    if (this->font)
        free(this->font); // this field could be reused, but we won't just in case it changes from the JS side
    this->font = (char *)EM_ASM_INT({
        var string = document.getElementById(UTF8ToString($0)).getContext('2d').font;
        var strlen = lengthBytesUTF8(string) + 1;
        var strptr = _malloc(strlen);
        stringToUTF8(string, strptr, strlen);
        return strptr;
    },
                                    this->canvas->id);
    return this->font;
}
static void context2d_setFont(CanvasRenderingContext2D *this, char *value)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').font = UTF8ToString($1);
    },
           this->canvas->id, value);
}
static int context2d_getTextAlign(CanvasRenderingContext2D *this)
{
    return EM_ASM_INT({
        var textAlignType = document.getElementById(UTF8ToString($0)).getContext('2d').textAlign;
        if (textAlignType == 'start')
            return 0;
        else if (textAlignType == 'end')
            return 1;
        else if (textAlignType == 'left')
            return 2;
        else if (textAlignType == 'right')
            return 3;
        else // 'center'
            return 4;
    },
                      this->canvas->id);
}
static void context2d_setTextAlign(CanvasRenderingContext2D *this, char *value)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').textAlign = UTF8ToString($1);
    },
           this->canvas->id, value);
}

// -- end CanvasRenderingContext2D static methods

static CanvasRenderingContext2D *createContext(HTMLCanvasElement *canvas, char *contextType)
{
    if (strcmp(contextType, "2d") != 0) // && strcmp(contextType, "webgl") != 0 && strcmp(contextType, "experimental-webgl") != 0 && strcmp(contextType, "webgl2") != 0 && strcmp(contextType, "bitmaprendered") != 0)
    {
        // not a valid context type
        return NULL;
    }
    CanvasRenderingContext2D *context2d = (CanvasRenderingContext2D *)malloc(sizeof(CanvasRenderingContext2D));
    context2d->canvas = canvas;
    strcpy(context2d->contextType, contextType); // string field is a static length, no need to allocate
    context2d->font = NULL;
    context2d->fillStyle = NULL;
    context2d->clearRect = context2d_clearRect;
    context2d->fillRect = context2d_fillRect;
    context2d->strokeRect = context2d_strokeRect;
    context2d->fillText = context2d_fillText;
    context2d->strokeText = context2d_strokeText;
    context2d->setLineWidth = context2d_setLineWidth;
    context2d->getLineWidth = context2d_getLineWidth;
    context2d->setLineCap = context2d_setLineCap;
    context2d->getLineCap = context2d_getLineCap;
    context2d->setLineJoin = context2d_setLineJoin;
    context2d->getLineJoin = context2d_getLineJoin;
    context2d->setFont = context2d_setFont;
    context2d->getFont = context2d_getFont;
    context2d->setTextAlign = context2d_setTextAlign;
    context2d->getTextAlign = context2d_getTextAlign;

    return context2d;
}

void freeCanvas(HTMLCanvasElement *canvas)
{
    if (canvas)
    {
        free(canvas->id);
        if (canvas->ctx)
        {
            if (canvas->ctx->font)
            {
                free(canvas->ctx->font);
            }
            if (canvas->ctx->fillStyle)
            {
                free(canvas->ctx->fillStyle);
            }
            free(canvas->ctx);
        }
        free(canvas);
    }
}