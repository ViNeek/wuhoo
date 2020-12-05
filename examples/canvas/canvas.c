/* compile with
  -- Windows --
  cl /I../../ /O2 canvas.c /link /out:canvas.exe kernel32.lib user32.lib gdi32.lib shell32.lib
  clang -I../../ -O2 canvas.c -o canvas.exe -lkernel32 -luser32 -lgdi32 -lshell32
  gcc -I../../ -O2 canvas.c -o canvas.exe -lkernel32 -luser32 -lgdi32 -lshell32
  -- Linux --
  gcc -I../../ -O2 canvas.c -o canvas -lX11 -lm
  -- Mac OS X --
  gcc -I../../ -O2 canvas.c -o canvas -framework Cocoa -framework Quartz -framework Carbon
*/

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#define WUHOO_IMPLEMENTATION
#include "wuhoo.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef double scalar_t;
//typedef float scalar_t;

float gauss(float x) {

  return ((1.0f) / sqrtf((2.0f * 3.14f))) * expf(-0.5f * (x*x));
}
float minf(float x, float y) {
  return (x < y) ? x : y;
}
int clampi(int x, int minVal, int maxVal) {
  return (x < minVal) ? minVal : ((x > maxVal) ? maxVal : x);
}

void point_draw(WuhooRGBA* pixels, int width, int height, int x, int y, int brush_size) {
  if (x < 0 || x >= width || y < 0 || y >= height)
    return;

  int range_x = brush_size;
  int range_y = brush_size;
  int start_x = -(range_x / 2);
  int start_y = -(range_y / 2);
  int end_x = -start_x;
  int end_y = -start_y;

  int i = 0;
  int j = 0;
  for (i = start_x; i < end_x; i++) {
    for (j = start_y; j < end_y; j++) {
      if ((x+i) < 0 || (x+i) >= width || (y+j) < 0 || (y+j) >= height)
	continue;

      if (i * i + j * j > (end_x * end_x))
	continue;

      int pixel_index = (x + i) + (y + j) * width;

      float val_x = fabsf(gauss( (float)i / (float)(range_x * 0.5f) ) / gauss(0.0f));
      float val_y = fabsf(gauss( (float)j / (float)(range_y * 0.5f) ) / gauss(0.0f));
      float val_prev = (float)pixels[pixel_index].r / 255.0f;
      float val = minf(val_prev + (val_x + val_y) * 0.5f, 1.0f);
      WuhooByte valb = (WuhooByte)(val * 255.0f);

      pixels[pixel_index].r = valb;
      pixels[pixel_index].g = valb;
      pixels[pixel_index].b = valb;
      pixels[pixel_index].a = valb;
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
                    WUHOO_FLAG_RESIZEABLE    |
                    WUHOO_FLAG_CLOSEABLE, WuhooNull);
  WuhooWindowShow(&window);

  pixels = (WuhooRGBA*)malloc(width * height * sizeof(*pixels));
  memset(pixels, 0, width * height * sizeof(*pixels));

  int draw = 0;
  int brush_size = 10;
  while(running) {
    WuhooWindowEventNext(&window, &event);

    switch (event.type) {
    case WUHOO_EVT_WINDOW:
      switch (event.data.window.state) {
      case WUHOO_WSTATE_INVALIDATED:
	WuhooWindowBlit(&window, pixels, 0, 0, width, height, 0, 0, width, height);

	break;
      case WUHOO_WSTATE_CLOSED:
	running = 0;
        break;
      case WUHOO_WSTATE_RESIZED:
	WuhooWindowClientRegionGet(&window, &posx, &posy, &width, &height);
	pixels = (WuhooRGBA*)realloc(pixels, width * height * sizeof(*pixels));
	memset(pixels, 0, width * height * sizeof(*pixels));

	sprintf(title_buffer, "Window Size (%d, %d)", width, height);
	WuhooWindowSetTitle(&window, title_buffer);

	break;
      default:
        break;
      }
      break;
    case WUHOO_EVT_MOUSE_WHEEL:
      brush_size += (event.data.mouse_wheel.delta_y > 0) ? 1 : -1;
      brush_size  = clampi(brush_size, 5, 50);

      break;
    case WUHOO_EVT_MOUSE_PRESS:
      draw = (WUHOO_MSTATE_LPRESSED == event.data.mouse_press.state);
      break;
    case WUHOO_EVT_MOUSE_MOVE:
      if (0 == draw || WUHOO_MSTATE_LPRESSED != event.data.mouse_move.state )
	break;
      point_draw(pixels, width, height, event.data.mouse_move.x, event.data.mouse_move.y, brush_size);
      WuhooWindowBlit(&window, pixels, 0, 0, width, height, 0, 0, width, height);

      break;
    case WUHOO_EVT_KEY:
      switch(event.data.key.code) {
      case WUHOO_VKEY_ESCAPE:
	running = (event.data.key.state == WUHOO_KSTATE_UP);
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
