/*
  -- Win32 --
  cl /I. /I../../ /O2 viewer.c /link /out:viewer.exe kernel32.lib user32.lib gdi32.lib shell32.lib
  clang -I. -I../../ -O2 viewer.c -o viewer.exe -lkernel32 -luser32 -lgdi32 -lshell32
  gcc -I. -I../../ -O2 viewer.c -o viewer.exe -lkernel32 -luser32 -lgdi32 -lshell32
  -- Linux --
  gcc -I. -I../../ -O2 viewer.c -o viewer -lX11 -lm
  -- Mac OS X --
  gcc -I. -I../../ viewer.c -o viewer -framework Cocoa -framework Quartz -framework Carbon
*/

#define WUHOO_IMPLEMENTATION
#define WUHOO_UNICODE
#include "wuhoo.h"

#define STBI_WINDOWS_UTF8
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION #include "stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

unsigned char
get_bg_color(int i, int j, int dim) {
  if ( ( (i / dim) % 2) == 1 && ( (j / dim) % 2) == 0 )
    return 64;
  else if ( ( (i / dim) % 2) == 0 && ( (j / dim) % 2) == 1 )
    return 64;
  else
    return 128;
}

void
blit_image(WuhooRGBA* dst, const WuhooRGBA* src, int width, int height) {
  int i, j;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      int index = j + i * width;
      float blend = 1.0f - (float)src[index].a / 255.0f;

      dst[index].r = (unsigned char)(get_bg_color(i, j, 10) * blend + src[index].r * (1.0f - blend));
      dst[index].g = (unsigned char)(get_bg_color(i, j, 10) * blend + src[index].g * (1.0f - blend));
      dst[index].b = (unsigned char)(get_bg_color(i, j, 10) * blend + src[index].b * (1.0f - blend));
    }
  }
}

int main(int argc, const char * argv[]) {
  WuhooUnused(argc);
  WuhooUnused(argv);
  
  const char * filename = WuhooNull;

  WuhooWindow window;
  WuhooEvent event;

  WuhooBoolean running = 1;
  WuhooSize width = 512;
  WuhooSize height = 512;

  int image_height = width;
  int image_width = height;
  int image_components = 1;
  WuhooRGBA* image_data = WuhooNull;
  if (WuhooNull != filename) {
      image_data = (WuhooRGBA*)stbi_load(filename, &image_width, &image_height, &image_components, 4);
  } else {
      image_data = (WuhooRGBA*)malloc(image_width * image_height * sizeof(*image_data));
      memset(image_data, 0, image_width * image_height * sizeof(*image_data));
  }
  WuhooRGBA* image_data_bck = image_data;

  if (WuhooNull == image_data) {
    if (WuhooNull != filename)
      printf("|Wuhoo Viewer| Failed to open file %s\n", filename);
    else
      printf("|Wuhoo Viewer| Failed to allcoate meory\n");
    return 1;
  }

  if (WuhooNull != filename)
      printf("|Wuhoo Viewer| Opening file %s\n", filename);

  width = image_width;
  height = image_height;
  WuhooRGBA* pixels = malloc(image_width * image_height * sizeof(*pixels));
  memcpy(pixels, image_data, image_width * image_height * sizeof(*pixels));

  WuhooWindowInit(&window);
  WuhooWindowCreate(&window, WuhooDefaultPosition, WuhooDefaultPosition, width, height, "Wuhoo Viewer",
		    WUHOO_FLAG_CANVAS        |
		    WUHOO_FLAG_TITLED        |
		    WUHOO_FLAG_MOUSE_CAPTURE |
		    WUHOO_FLAG_CLIENT_REGION |
		    WUHOO_FLAG_FILE_DROP     |
		    WUHOO_FLAG_RESIZEABLE    |
		    WUHOO_FLAG_CLOSEABLE, WuhooNull);
  WuhooWindowShow(&window);

  WuhooWindowSetTitle(&window, filename);

  blit_image(pixels, pixels, width, height);

  int posx, posy;
  char image_file[256];
  int index = 0;
  image_file[0] = 0;

  while(running) {
    WuhooWindowEventNext(&window, &event);

    switch (event.type) {
    case WUHOO_EVT_WINDOW: {
      switch (event.data.window.state) {
      case WUHOO_WSTATE_INVALIDATED:
	WuhooWindowBlit(&window, pixels, 0, 0, width, height, 0, 0, width, height);
	break;
      case WUHOO_WSTATE_CLOSED:
	running = 0;
	break;
      case WUHOO_WSTATE_RESIZED:
        WuhooWindowClientRegionGet(&window, &posx, &posy, &width, &height);

	width = event.data.window.data1;
	height = event.data.window.data2;

	pixels = realloc(pixels, width * height * sizeof(*pixels));
       	stbir_resize_uint8((unsigned char *)image_data, image_width, image_height, 0,
	  (unsigned char *)pixels, width, height, 0, 4);
	blit_image(pixels, pixels, width, height);

	WuhooWindowBlit(&window, pixels, 0, 0, width, height, 0, 0, width, height);

	break;
      default:
	break;
      }
    }break;
    case WUHOO_EVT_DROP: {
      WuhooWindowRegionGet(&window, &posx, &posy, &width, &height);
      printf("Dropped Files %d %d\n", event.data.drop.count, event.data.drop.size);

      char* files = (char*)malloc(event.data.drop.size);
      WuhooWindowDropContentsGet(&window, &event, files, event.data.drop.size);

      index = 0;
      while('\n' != files[index] ) {
		image_file[index] = files[index];
		index++;
      }
      image_file[index] = 0;

      free(files);
      image_data_bck = image_data;
      image_data = (WuhooRGBA*)stbi_load(image_file, &image_width, &image_height, &image_components, 4);

      if (WuhooNull == image_data) {
		printf("|Wuhoo Viewer| stbi_load failed to open file %s\n", image_file);
		continue;
      }

      WuhooWindowSetTitle(&window, image_file);
      free(image_data_bck);

	  pixels = realloc(pixels, image_width * image_height * sizeof(*pixels));

      blit_image(pixels, image_data, image_width, image_height);

      WuhooWindowClientRegionSet(&window, posx, posy, image_width, image_height);
    } break;
    case WUHOO_EVT_KEY: {
      switch(event.data.key.code) {
      case WUHOO_VKEY_ESCAPE:
	running = (event.data.key.state != WUHOO_KSTATE_UP);
	break;
      default:
	break;
      }
    } break;
    }

  }

  if (pixels) free(pixels);
  WuhooWindowDestroy(&window);

  return 0;
}
