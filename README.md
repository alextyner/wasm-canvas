# wasm-canvas

wasm-canvas is a **C99-compliant** layer of abstraction for interacting with the **HTML Canvas API**. 

This library is intended for use in projects compiled with [Emscripten](https://emscripten.org/) targeting [WebAssembly](https://webassembly.org/).

## Purpose

#### Familiarity

If you've worked with the Canvas API from JavaScript, the syntax for drawing is simple and friendly, as JavaScript tends to be. 

Although JavaScript excels in readability, it often lacks in optimizability. Web applications with high-performance requirements may turn to WebAssembly compiled from C.

For applications with visual components, interacting with the Canvas API from C feels unfriendly and unfamiliar. This library provides an interface for doing so which closely resembles the syntax used in JavaScript.

#### "Object-Oriented"

This library is written in C, not an object-oriented programming language. However,the design is patterned less like idiomatic C and more like a JavaScript programmer might expect.

Some C idioms still shine through. With no garbage collector or constructors, `create...` and `free...` functions are provided to allocate, set up, and free the object-like structs. The structs are populated primarily by function pointers to make calls as similar to JavaScript as possible. However, nearly all member functions require a pointer to their parent struct as the first parameter as there is no implicit `this` present in C.

#### Why not C++?



## Using the Library

#### Include the Headers

Currently, this is not a header-only library. Be sure that for each header included at compile time you introduce the corresponding source file at link time. See *Hello World* below for an example

For the Canvas API and drawing context functionality:

```C
#include canvas.h
```

For access to the DOM Window object:

```C
#include window.h
```

#### Creating a New Canvas

Use the `createCanvas()` function to insert a new canvas element into the HTML.

```C
HTMLCanvasElement *myCanvas = createCanvas("testCanvas");
```

A new Canvas element has dimensions 300px x 150px by default.

#### Using an Existing Canvas

If your HTML already has a canvas element you'd like to bind to...

```HTML
<canvas id="someCanvas"></canvas>
```

... use `createCanvas()` with the existing element's id.

```C
HTMLCanvasElement *myCanvas = createCanvas("someCanvas");
```

#### Window()

`#include window.h`

The DOM Window object, accessible via the global `window` in JavaScript, provides some useful functionality when used in conjunction with a canvas.

For example, a canvas can be expanded in size to fill the current window.

```C
myCanvas->setHeight(myCanvas, Window()->getInnerHeight());
myCanvas->setWidth(myCanvas, Window()->getInnerWidth());
```

Note that window functions do not require a pointer to the struct as the first parameter. It is assumed that there is only one window, and you are referring to that one.

#### Cleaning Up

Some memory is dynamically allocated for each HTMLCanvasElement created. Memory is only allocated for the HTMLWindow if it is used at least once in your program.

Free the memory for each canvas using `freeCanvas()`.

```C
freeCanvas(myCanvas);
```

And, if you've used the `Window()` function at least once, free it using `freeWindow()`.

```C
freeWindow(Window());
```

## Documentation

#### wasm-canvas

[View the Doxygen](https://alextyner.github.io/wasm-canvas/documentation/)

#### Emscripten

[Installation Instructions](https://emscripten.org/docs/getting_started/downloads.html)

[Emscripten API](https://emscripten.org/docs/api_reference/)

## Examples

#### Hello World

This is how you might draw something simple, like the text "Hello World" on a new canvas.

Although not required, I recommend giving Emscripten at least a basic HTML template to clearly see your canvas. If you choose not to provide a template, the default template does include a canvas element that you can bind to (see *Using the Library* above).

**Directory Listing**

- build/
- canvas.c [wasm-canvas]
- canvas.h [wasm-canvas]
- template.html (optional)
- hello.c

file: **template.html**

```HTML
<!DOCTYPE html>
<html>
    <body>
        {{{ SCRIPT }}}
    </body>
</html>
```

file: **hello.c**

```C
#include "canvas.h"

int main(void) {
	HTMLCanvasElement *canvas = createCanvas("myCanvas");
    CanvasRenderingContext2D *ctx = canvas->getContext(canvas, "2d");
    ctx->setFont(ctx, "48px serif");
    ctx->fillText(ctx, "Hello World", 0, 150, -1);
    freeCanvas(canvas);
}
```

**Compiling & Linking**

```bash
emcc -Wall hello.c canvas.c -o hello.o
emcc --shell-file template.html hello.o -o build/index.html
```

Or, more verbosely:

```bash
emcc -Wall canvas.c -o canvas.o
emcc -Wall hello.c -o hello.o
emcc --shell-file template.html hello.o canvas.o -o build/index.html
```

Or, less verbosely:

```bash
emcc --shell-file template.html hello.c canvas.c -o build/index.html
```

