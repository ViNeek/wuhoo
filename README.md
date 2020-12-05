# WUHOO

Wuhoo loosely stands for **W** indows **U** sing **H** eaders **O** nly. It is an attempt to create a single-header library (in the spirit of STB [1]) for graphics related window management, compatible with both C and C++. 

The elephant in the room here is of course Mac OS X which exposes all Cocoa APIs mainly in Obj-C and lately in Swift. Obj-C being just a thin overlay over regular C calls, it is possible to do everything in pure C using the objective C runtime. Full dislaimer here, I am completely aware that this is not recommended by any of Apple' s guides and there is no guarantee that interactions with the Obj-C runtime will remain stable in the long run, but, that being said there is nothing stopping us from trying.

## Mandelbrot Set

Renderings of the Mandlebrot Set on all 3 major systems using window system buffers

<img src="images/win32_mandelbrot.png" alt="Win32" width="256"/><img src="images/x11_mandelbrot.png" alt="drawing" width="256"/>

<img src="examples/mandelbrot/mandelbrot_win32.png" alt="Win32" width="256"/> <img src="examples/mandelbrot/mandelbrot_cocoa.png" alt="drawing" width="259
"/>

## Mandelbrot Set GL

Renderings of the Mandlebrot Set on all 3 major systems using OpenGL backed buffers.

## Ray Tracing In a Weekend

A very minor port of the Ray Tracing in a Weekend book using **wuhoo** using C++ and system buffers.

## Features
- Simple to include
- Simple to ship
- Supports several backends under a simple, lean and common API

## Usage
If you plan to use the OpenGL backend, it is expected that you include your own OpenGL headers before wuhoo itself.

[1] https://github.com/nothings/stb

