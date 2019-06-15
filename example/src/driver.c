#include <stdio.h>
#include "canvas.c"

static void log(char *msg) {
    EM_ASM({
        console.log(UTF8ToString($0));
    }, msg);
}

int main(void) {
    Canvas *c = createCanvas("test");

    // test getHeight()
    int height = c->getHeight(c);

    char buf1[8];
    sprintf(buf1, "%d", height);
    log(buf1);

    c->setHeight(c, 500);

    // test setHeight()
    int newHeight = c->getHeight(c);
    sprintf(buf1, "%d", newHeight);
    log(buf1);

    freeCanvas(c);
    return 0;
}