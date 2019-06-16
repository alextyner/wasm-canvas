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
    if (expected == actual)
    {
        strcat(msg, "] passed.");
    }
    else
    {
        strcat(msg, "] failed!");
    }
    log(msg);
    free(msg);
}

static void assertStringEquals(char *testID, char *expected, char *actual)
{
    char *msg = (char *)malloc(5 + 1 + strlen(testID) + 1 + 8 + 1);
    strcpy(msg, "Test [");
    strcat(msg, testID);
    if (strcmp(expected, actual) == 0)
    {
        strcat(msg, "] passed.");
    }
    else
    {
        strcat(msg, "] failed!");
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

    char buf[128];
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
    // test CanvasRenderingContext2D.getLineJoin()
    assertEquals("CanvasRenderingContext2D.getLineJoin()", 2, ctx->getLineJoin(ctx));
    // test CanvasRenderingContext2D.setLineJoin()
    ctx->setLineJoin(ctx, "bevel");
    assertEquals("CanvasRenderingContext2D.setLineJoin()", 1, ctx->getLineJoin(ctx));
    // test CanvasRenderingContext2D.getFont()
    assertStringEquals("CanvasRenderingContext2D.getFont()", "10px sans-serif", ctx->getFont(ctx));
    // test CanvasRenderingContext2D.setFont()
    ctx->setFont(ctx, "bold 48px serif");
    assertStringEquals("CanvasRenderingContext2D.setFont()", "bold 48px serif", ctx->getFont(ctx));
    // test CanvasRenderingContext2D.getTextAlign()
    assertEquals("CanvasRenderingContext2D.getTextAlign()", 0, ctx->getTextAlign(ctx));
    // test CanvasRenderingContext2D.setTextAlign()
    ctx->setTextAlign(ctx, "left");
    assertEquals("CanvasRenderingContext2D.setTextAlign()", 2, ctx->getTextAlign(ctx));

    freeCanvas(canvas);
    freeWindow(Window());
    return 0;
}