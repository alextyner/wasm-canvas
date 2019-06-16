/**
 * @file canvas.c
 * @author Alex Tyner
 * Facilitates interaction with HTML5 Canvas elements in a similar
 * manner to JavaScript, but from C compiled with Emscripten.
 */

#include "canvas.h"

static CanvasRenderingContext2D *createContext(HTMLCanvasElement *canvas, char *contextType);

/* Begin: HTMLCanvasElement static methods */
static int canvas_getWidth(HTMLCanvasElement *this)
{
    return EM_ASM_INT({
        return document.getElementById(UTF8ToString($0)).width;
    },
                      this->private.id);
}
static int canvas_getHeight(HTMLCanvasElement *this)
{
    return EM_ASM_INT({
        return document.getElementById(UTF8ToString($0)).height;
    },
                      this->private.id);
}
static void canvas_setWidth(HTMLCanvasElement *this, int width)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).width = $1;
    },
           this->private.id, width);
}
static void canvas_setHeight(HTMLCanvasElement *this, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).height = $1;
    },
           this->private.id, height);
}
static CanvasRenderingContext2D *canvas_getContext(HTMLCanvasElement *this, char *contextType)
{
    if (this->private.ctx)
        return this->private.ctx;
    this->private.ctx = createContext(this, contextType);
    return this->private.ctx;
}
/* End: HTMLCanvasElement static methods */

HTMLCanvasElement *createCanvas(char *id)
{
    EM_ASM(
        {
            document.body.appendChild(document.createElement("canvas")).setAttribute("id", UTF8ToString($0));
        },
        id);
    HTMLCanvasElement *c = (HTMLCanvasElement *)malloc(sizeof(HTMLCanvasElement));

    /* Begin: set pseudo-private fields */
    c->private.id = (char *)malloc(strlen(id) + 1);
    strcpy(c->private.id, id);
    c->private.ctx = NULL; // we'll lazy-load the context when it's asked for
    /* End: set pseudo-private fields */
    c->getWidth = canvas_getWidth;
    c->getHeight = canvas_getHeight;
    c->setHeight = canvas_setHeight;
    c->setWidth = canvas_setWidth;
    c->getContext = canvas_getContext;

    return c;
}

/* Begin: CanvasRenderingContext2D static methods */
static void context2d_clearRect(CanvasRenderingContext2D *this, int x, int y, int width, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').clearRect($1, $2, $3, $4);
    },
           this->private.canvas->private.id, x, y, width, height);
}
static void context2d_fillRect(CanvasRenderingContext2D *this, int x, int y, int width, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').fillRect($1, $2, $3, $4);
    },
           this->private.canvas->private.id, x, y, width, height);
}
static void context2d_strokeRect(CanvasRenderingContext2D *this, int x, int y, int width, int height)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').strokeRect($1, $2, $3, $4);
    },
           this->private.canvas->private.id, x, y, width, height);
}
static void context2d_fillText(CanvasRenderingContext2D *this, char *text, int x, int y, int maxWidth)
{
    if (maxWidth == -1)
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').fillText(UTF8ToString($1), $2, $3);
        },
               this->private.canvas->private.id, text, x, y);
    }
    else
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').fillText(UTF8ToString($1), $2, $3, $4);
        },
               this->private.canvas->private.id, text, x, y, maxWidth);
    }
}
static void context2d_strokeText(CanvasRenderingContext2D *this, char *text, int x, int y, int maxWidth)
{
    if (maxWidth == -1)
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').strokeText(UTF8ToString($1), $2, $3);
        },
               this->private.canvas->private.id, text, x, y);
    }
    else
    {
        EM_ASM({
            document.getElementById(UTF8ToString($0)).getContext('2d').strokeText(UTF8ToString($1), $2, $3, $4);
        },
               this->private.canvas->private.id, text, x, y, maxWidth);
    }
}
static void context2d_setLineWidth(CanvasRenderingContext2D *this, double value)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').lineWidth = ($1);
    },
           this->private.canvas->private.id, value);
}
static double context2d_getLineWidth(CanvasRenderingContext2D *this)
{
    return EM_ASM_DOUBLE({
        return document.getElementById(UTF8ToString($0)).getContext('2d').lineWidth;
    },
                         this->private.canvas->private.id);
}
static void context2d_setLineCap(CanvasRenderingContext2D *this, char *type)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').lineCap = UTF8ToString($1);
    },
           this->private.canvas->private.id, type);
}
static char *context2d_getLineCap(CanvasRenderingContext2D *this)
{
    if (this->private.lineCap)
        free(this->private.lineCap);
    this->private.lineCap = (char *)EM_ASM_INT({
        var string = document.getElementById(UTF8ToString($0)).getContext('2d').lineCap;
        var strlen = lengthBytesUTF8(string) + 1;
        var strptr = _malloc(strlen);
        stringToUTF8(string, strptr, strlen);
        return strptr;
    },
                                               this->private.canvas->private.id);
    return this->private.lineCap;
}
static void context2d_setLineJoin(CanvasRenderingContext2D *this, char *type)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').lineJoin = UTF8ToString($1);
    },
           this->private.canvas->private.id, type);
}
static char *context2d_getLineJoin(CanvasRenderingContext2D *this)
{
    if (this->private.lineJoin)
        free(this->private.lineJoin);
    this->private.lineJoin = (char *)EM_ASM_INT({
        var string = document.getElementById(UTF8ToString($0)).getContext('2d').lineJoin;
        var strlen = lengthBytesUTF8(string) + 1;
        var strptr = _malloc(strlen);
        stringToUTF8(string, strptr, strlen);
        return strptr;
    },
                                                this->private.canvas->private.id);
    return this->private.lineJoin;
}
static char *context2d_getFont(CanvasRenderingContext2D *this)
{
    if (this->private.font)
        free(this->private.font); // this field could be reused, but we won't just in case it changes from the JS side
    this->private.font = (char *)EM_ASM_INT({
        var string = document.getElementById(UTF8ToString($0)).getContext('2d').font;
        var strlen = lengthBytesUTF8(string) + 1;
        var strptr = _malloc(strlen);
        stringToUTF8(string, strptr, strlen);
        return strptr;
    },
                                            this->private.canvas->private.id);
    return this->private.font;
}
static void context2d_setFont(CanvasRenderingContext2D *this, char *value)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').font = UTF8ToString($1);
    },
           this->private.canvas->private.id, value);
}
static char *context2d_getTextAlign(CanvasRenderingContext2D *this)
{
    if (this->private.textAlign)
        free(this->private.textAlign);
    this->private.textAlign = (char *)EM_ASM_INT({
        var string = document.getElementById(UTF8ToString($0)).getContext('2d').textAlign;
        var strlen = lengthBytesUTF8(string) + 1;
        var strptr = _malloc(strlen);
        stringToUTF8(string, strptr, strlen);
        return strptr;
    },
                                                 this->private.canvas->private.id);
    return this->private.textAlign;
}
static void context2d_setTextAlign(CanvasRenderingContext2D *this, char *value)
{
    EM_ASM({
        document.getElementById(UTF8ToString($0)).getContext('2d').textAlign = UTF8ToString($1);
    },
           this->private.canvas->private.id, value);
}
/* End: CanvasRenderingContext2D static methods */

static CanvasRenderingContext2D *createContext(HTMLCanvasElement *canvas, char *contextType)
{
    if (strcmp(contextType, "2d") != 0)
        return NULL; // not a valid context type; 2d is all I can be bothered with

    CanvasRenderingContext2D *context2d = (CanvasRenderingContext2D *)malloc(sizeof(CanvasRenderingContext2D));

    /* Begin: set pseudo-private fields */
    context2d->private.canvas = canvas;
    strcpy(context2d->private.contextType, contextType); // string field is a static length, no need to allocate
    context2d->private.font = NULL;
    context2d->private.textAlign = NULL;
    context2d->private.fillStyle = NULL;
    context2d->private.strokeStyle = NULL;
    context2d->private.lineCap = NULL;
    context2d->private.lineJoin = NULL;
    /* End: set pseudo-private fields */
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
        free(canvas->private.id);
        if (canvas->private.ctx)
        {
            if (canvas->private.ctx->private.font)
                free(canvas->private.ctx->private.font);
            if (canvas->private.ctx->private.textAlign)
                free(canvas->private.ctx->private.textAlign);
            if (canvas->private.ctx->private.fillStyle)
                free(canvas->private.ctx->private.fillStyle);
            if (canvas->private.ctx->private.strokeStyle)
                free(canvas->private.ctx->private.strokeStyle);
            if (canvas->private.ctx->private.lineCap)
                free(canvas->private.ctx->private.lineCap);
            if (canvas->private.ctx->private.lineJoin)
                free(canvas->private.ctx->private.lineJoin);
            free(canvas->private.ctx);
        }
        free(canvas);
    }
}