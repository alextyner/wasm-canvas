#include <stdio.h>
#include "canvas.c"
#include "window.c"

static void log(char *msg)
{
    EM_ASM({
        console.log(UTF8ToString($0));
    },
           msg);
}

static void assertEquals(char *testID, int expected, int actual)
{
    char *msg = (char *)malloc(5 + 1 + strlen(testID) + 1 + 8 + 1);
    strcpy(msg, "Test [");
    strcat(msg, testID);
    if (expected != actual)
    {
        strcat(msg, "] failed!");
    }
    else
    {
        strcat(msg, "] passed.");
    }
    log(msg);
    free(msg);
}

int main(void)
{
    log("Creating an HTMLCanvasElement 'canvas' with id='test'.");
    HTMLCanvasElement *canvas = createCanvas("test");

    // test HTMLCanvasElement.getHeight()
    assertEquals("HTMLCanvas.getHeight()", 150, canvas->getHeight(canvas)); // default: 150
    // test HTMLCanvasElement.getHeight()
    assertEquals("HTMLCanvas.getWidth()", 300, canvas->getWidth(canvas)); // default: 300

    // test HTMLCanvasElement.setHeight()
    canvas->setHeight(canvas, 500);
    assertEquals("HTMLCanvas.setHeight()", 500, canvas->getHeight(canvas));
    // test HTMLCanvasElement.setWidth()
    canvas->setWidth(canvas, 750);
    assertEquals("HTMLCanvas.setWidth()", 750, canvas->getWidth(canvas));

    char buf[32];
    // test Window.getInnerHeight()
    snprintf(buf, 32, "Window().getInnerHeight(): %d", Window()->getInnerHeight());
    log(buf);
    // test Window.getInnerWidth()
    snprintf(buf, 32, "Window().getInnerWidth(): %d", Window()->getInnerWidth());
    log(buf);

    log("Getting drawing context 'ctx' of type '2d' from canvas 'canvas'.");
    CanvasRenderingContext2D *ctx = canvas->getContext(canvas, "2d");

    // test CanvasRenderingContext2D.fillRect()
    ctx->fillRect(ctx, 0, 0, 50, 50);
    assertEquals("CanvasRenderingContext2D.fillRect()", 0, 0);
    // test CanvasRenderingContext2D.clearRect()
    ctx->clearRect(ctx, 0, 0, 25, 25);
    assertEquals("CanvasRenderingContext2D.clearRect()", 0, 0);
    // test CanvasRenderingContext2D.strokeRect()
    ctx->strokeRect(ctx, 10, 10, 75, 75);
    assertEquals("CanvasRenderingContext2D.strokeRect()", 0, 0);
    // test CanvasRenderingContext2D.fillText()
    ctx->fillText(ctx, "fillText()", 100, 24, -1);
    ctx->fillText(ctx, "fillText()", 100, 48, 16);
    assertEquals("CanvasRenderingContext2D.fillText()", 0, 0);
    // test CanvasRenderingContext2D.strokeText()
    ctx->fillText(ctx, "strokeText()", 200, 24, -1);
    ctx->fillText(ctx, "strokeText()", 200, 48, 16);
    assertEquals("CanvasRenderingContext2D.strokeText()", 0, 0);
    // test CanvasRenderingContext2D.getLineWidth()
    assertEquals("CanvasRenderingContext2D.getLineWidth()", 10, ctx->getLineWidth(ctx) * 10); // 1.0 default
    // test CanvasRenderingContext2D.setLineWidth()
    ctx->setLineWidth(ctx, 8.0);
    assertEquals("CanvasRenderingContext2D.setLineWidth()", 80, ctx->getLineWidth(ctx) * 10);
    // test CanvasRenderingContext2D.getLineCap()
    assertEquals("CanvasRenderingContext2D.getLineCap()", 0, ctx->getLineCap(ctx));
    // test CanvasRenderingContext2D.setLineCap()
    ctx->setLineCap(ctx, "round");
    assertEquals("CanvasRenderingContext2D.setLineCap()", 1, ctx->getLineCap(ctx));

    freeCanvas(canvas);
    freeWindow(Window());
    return 0;
}