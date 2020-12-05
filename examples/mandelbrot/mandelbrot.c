/* compile with
  -- Windows --
  cl /I../../ /O2 mandelbrot.c /link /out:mandelbrot.exe kernel32.lib user32.lib gdi32.lib shell32.lib
  clang -I../../ -O2 mandelbrot.c -o mandelbrot.exe -lkernel32 -luser32 -lgdi32 -lshell32
  gcc -I../../ -O2 mandelbrot.c -o mandelbrot.exe -lkernel32 -luser32 -lgdi32 -lshell32
  -- Linux -- 
  gcc -I../../ -O2 mandelbrot.c -o mandelbrot -lX11 -lm
  -- Mac OS X --
  gcc -I../../ -O2 mandelbrot.c -o mandelbrot -framework Cocoa -framework Quartz -framework Carbon
*/

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#define WUHOO_IMPLEMENTATION
#include "wuhoo.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef double scalar_t;
//typedef float scalar_t;

void mandelbrot_draw(WuhooRGBA* pixels, int width, int height) {
  scalar_t factor_x = -2.5;
  scalar_t factor_y = -2;
  scalar_t zoom = 4.0;

  scalar_t Cr;
  scalar_t Ci;
  scalar_t pixel_x;
  scalar_t pixel_y;
  int iter = 20;
  int x, y;

  for (x = 0; x < width; ++x) {
    for (y = 0; y < height; ++y) {
      pixel_x = ((scalar_t)x - (scalar_t)0.5) / (scalar_t)width;
      pixel_y = ((scalar_t)y - (scalar_t)0.5) / (scalar_t)height;

      pixel_x = pixel_x * zoom + factor_x;
      pixel_y = pixel_y * zoom + factor_y;

      Cr = pixel_x;
      Ci = pixel_y;

      int i;

      scalar_t Zr = Cr;
      scalar_t Zi = Ci;
      for (i = 0; i < iter; i++) {
	scalar_t px = (Zr * Zr - Zi * Zi) + Cr;
	scalar_t py = (Zi * Zr + Zr * Zi) + Ci;

	Zr = px;
	Zi = py;

	if ((px * px + py * py) > 20.0) break;
      }

      size_t pixel_index = x + y * width;

      scalar_t col = (scalar_t)i + 1 - log(log(sqrt(Zr*Zr + Zi * Zi))) / log(2.0);
      //     col = (float)i / (float)iter;
      col = col / (scalar_t)(iter);
      unsigned char out = (i == iter) ? 255 : (unsigned char)((col) * (scalar_t)255.0);

      pixels[pixel_index].r = out;
      pixels[pixel_index].g = out;
      pixels[pixel_index].b = out;
      pixels[pixel_index].a = 1;
    }
  }
}

int main(int argc, const char * argv[]) {
  WuhooWindow window;
  WuhooEvent event;
  WuhooRGBA* pixels;

  const char * title = "Mandelbrot Set (" WUHOO_PLATFORM_API_STRING ")";
  WuhooBoolean running = 1;
  char title_buffer[128] = {0};
  int posx = 300;
  int posy = 300;
  WuhooSize width = 512;
  WuhooSize height = 512;

  WuhooWindowInit(&window);
  WuhooWindowCreate(&window, WuhooDefaultPosition, WuhooDefaultPosition, width, height, title,
                    WUHOO_FLAG_CANVAS        |
                    WUHOO_FLAG_TITLED        |
                    WUHOO_FLAG_MOUSE_CAPTURE |
                    WUHOO_FLAG_RESIZEABLE    |
   					WUHOO_FLAG_CLIENT_REGION |
                    WUHOO_FLAG_CLOSEABLE, WuhooNull);
  WuhooWindowShow(&window);

  pixels = (WuhooRGBA*)malloc(width * height * sizeof(*pixels));
  memset(pixels, 0, width * height * sizeof(*pixels));

  while(running) {
    WuhooWindowEventNext(&window, &event);

    switch (event.type) {
    case WUHOO_EVT_WINDOW:
      switch (event.data.window.state) {
      case WUHOO_WSTATE_INVALIDATED:
        mandelbrot_draw(pixels, width, height);

	WuhooWindowBlit(&window, pixels, 0, 0, width, height, 0, 0, width, height);

	break;
      case WUHOO_WSTATE_CLOSED:
	running = 0;
        break;
      case WUHOO_WSTATE_RESIZED:
	WuhooWindowRegionGet(&window, &posx, &posy, &width, &height);
	printf("|Mandelbrot| Resize Event Window Area Size [%d %d] x [%d %d].\n", posx, posy, width, height);
	WuhooWindowClientRegionGet(&window, &posx, &posy, &width, &height);
	printf("|Mandelbrot| Resize Event Window Client Area Size [%d %d] x [%d %d].\n", posx, posy, width, height);
	pixels = (WuhooRGBA*)realloc(pixels, width * height * sizeof(*pixels));
	memset(pixels, 0, width * height * sizeof(*pixels));

	sprintf(title_buffer, "Window Size (%d, %d)", width, height);
	//WuhooWindowSetTitle(&window, title_buffer);

	WuhooWindowBlit(&window, pixels, 0, 0, width, height, 0, 0, width, height);
	break;
      default:
        break;
      }
    case WUHOO_EVT_KEY:
      switch(event.data.key.code) {
      case WUHOO_VKEY_ESCAPE:
	running = (event.data.key.state != WUHOO_KSTATE_UP);
        break;
      default:
        break;
      }
    default:
      break;
    }
  }

  if (WuhooNull == pixels)
    free(pixels);

  WuhooWindowDestroy(&window);

  return 0;
}
